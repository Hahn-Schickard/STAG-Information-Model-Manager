#include "ObservableImpl.hpp"

#include <Event_Model/ThreadPool.hpp>
#include <Variant_Visitor/Visitor.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Information_Model_Manager::testing {
using namespace std;
using namespace ::testing;
using namespace Information_Model;

// NOLINTNEXTLINE(readability-identifier-naming)
MATCHER_P(ExceptionPointee, exception_type, "") {
  try {
    rethrow_exception(arg);
    return false;
  } catch (const exception& ex) {
    return typeid(ex) == typeid(exception_type) &&
        ex.what() == exception_type.what();
  }
}

DataVariant otherThan(const DataVariant& input) {
  return Variant_Visitor::match(
      input, // NOLINTBEGIN(readability-magic-numbers)
      [](bool) -> DataVariant {
        return std::vector<uint8_t>{0x00, 0x01, 0xAB};
      },
      [](intmax_t) -> DataVariant {
        return Timestamp{2025, 9, 10, 13, 01, 24, 32};
      },
      [](uintmax_t) -> DataVariant { return std::string("A new value"); },
      [](double) -> DataVariant { return uintmax_t{9789121}; },
      [](Timestamp) -> DataVariant { return intmax_t{-698872}; },
      [](const std::vector<uint8_t>&) -> DataVariant { return true; },
      [](const std::string&) -> DataVariant {
        return 20.3512;
      }); // NOLINTEND(readability-magic-numbers)
}

struct ObservableTests : public TestWithParam<DataVariant> {
  ObservableTests() : expected(GetParam()) {
    Simple_Thread_Pool::Manager::initialise();
    tested = make_shared<ObservableImpl>(toDataType(expected),
        mock_readable.AsStdFunction(),
        mock_enable_observation.AsStdFunction());
    ON_CALL(mock_readable, Call()).WillByDefault(Return(expected));
  }

  ~ObservableTests() override { Simple_Thread_Pool::Manager::terminate(); }

  DataVariant expected;
  MockFunction<DataVariant(void)> mock_readable;
  MockFunction<void(bool)> mock_enable_observation;
  ObservableImplPtr tested;
};

TEST_P(ObservableTests, returnsDataType) {
  EXPECT_EQ(tested->dataType(), toDataType(expected));
}
TEST_P(ObservableTests, canRead) {
  EXPECT_CALL(mock_readable, Call()).Times(Exactly(1));

  EXPECT_EQ(tested->read(), expected);
}

TEST_P(ObservableTests, canReadTwice) {
  EXPECT_CALL(mock_readable, Call()).Times(Exactly(2));

  EXPECT_EQ(tested->read(), expected);
  EXPECT_EQ(tested->read(), expected);
}

TEST_P(ObservableTests, throwsOnEmptyCallback) {
  MockFunction<void(const shared_ptr<DataVariant>&)> mock_observer_cb;
  MockFunction<void(const exception_ptr&)> mock_exception_handler;

  EXPECT_CALL(mock_enable_observation, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_observer_cb, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_exception_handler, Call(_)).Times(Exactly(0));

  auto throws_on_both_args = [this]() {
    auto connection = tested->subscribe(nullptr, nullptr);
  };
  EXPECT_THAT(throws_on_both_args,
      ThrowsMessage<invalid_argument>(
          HasSubstr("ObserveCallback can not be empty")));

  auto throws_on_first_arg = [this, &mock_exception_handler]() {
    auto connection =
        tested->subscribe(nullptr, mock_exception_handler.AsStdFunction());
  };
  EXPECT_THAT(throws_on_first_arg,
      ThrowsMessage<invalid_argument>(
          HasSubstr("ObserveCallback can not be empty")));

  auto throws_on_second_arg = [this, &mock_observer_cb]() {
    auto connection =
        tested->subscribe(mock_observer_cb.AsStdFunction(), nullptr);
  };
  EXPECT_THAT(throws_on_second_arg,
      ThrowsMessage<invalid_argument>(
          HasSubstr("ExceptionHandler can not be empty")));
}

TEST_P(ObservableTests, canSubAndUnsub) {
  MockFunction<void(const shared_ptr<DataVariant>&)> mock_observer_cb;
  MockFunction<void(const exception_ptr&)> mock_exception_handler;

  EXPECT_CALL(mock_enable_observation, Call(false)).Times(Exactly(1));
  EXPECT_CALL(mock_enable_observation, Call(true)).Times(Exactly(1));
  EXPECT_CALL(mock_observer_cb, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_exception_handler, Call(_)).Times(Exactly(0));

  EXPECT_NO_THROW({
    auto connection = tested->subscribe(mock_observer_cb.AsStdFunction(),
        mock_exception_handler.AsStdFunction());

    connection.reset();

    // we must dispatch a notification for the mock to cleanup connections
    tested->notify(true);
  });
}

TEST_P(ObservableTests, canNotifyOne) {
  MockFunction<void(const shared_ptr<DataVariant>&)> mock_observer_cb;
  MockFunction<void(const exception_ptr&)> mock_exception_handler;

  EXPECT_CALL(mock_enable_observation, Call(false)).Times(Exactly(1));
  EXPECT_CALL(mock_enable_observation, Call(true)).Times(Exactly(1));
  EXPECT_CALL(mock_observer_cb, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_observer_cb, Call(Pointee(otherThan(expected))))
      .Times(Exactly(1));
  EXPECT_CALL(mock_observer_cb, Call(Pointee(expected))).Times(Exactly(1));
  EXPECT_CALL(mock_exception_handler, Call(_)).Times(Exactly(0));

  EXPECT_NO_THROW({
    auto connection = tested->subscribe(mock_observer_cb.AsStdFunction(),
        mock_exception_handler.AsStdFunction());

    tested->notify(expected);
    tested->notify(otherThan(expected));
  });
}

TEST_P(ObservableTests, canNotifyTwo) {
  MockFunction<void(const shared_ptr<DataVariant>&)> mock_observer_1_cb;
  MockFunction<void(const shared_ptr<DataVariant>&)> mock_observer_2_cb;
  MockFunction<void(const exception_ptr&)> mock_exception_handler;

  EXPECT_CALL(mock_enable_observation, Call(false)).Times(Exactly(1));
  EXPECT_CALL(mock_enable_observation, Call(true)).Times(Exactly(1));
  EXPECT_CALL(mock_observer_1_cb, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_observer_1_cb, Call(Pointee(otherThan(expected))))
      .Times(Exactly(1));
  EXPECT_CALL(mock_observer_1_cb, Call(Pointee(expected))).Times(Exactly(2));
  EXPECT_CALL(mock_observer_2_cb, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_observer_2_cb, Call(Pointee(otherThan(expected))))
      .Times(Exactly(1));
  EXPECT_CALL(mock_observer_2_cb, Call(Pointee(expected))).Times(Exactly(1));
  EXPECT_CALL(mock_exception_handler, Call(_)).Times(Exactly(0));

  EXPECT_NO_THROW({
    auto connection_1 = tested->subscribe(mock_observer_1_cb.AsStdFunction(),
        mock_exception_handler.AsStdFunction());
    auto connection_2 = tested->subscribe(mock_observer_2_cb.AsStdFunction(),
        mock_exception_handler.AsStdFunction());

    tested->notify(expected);
    tested->notify(otherThan(expected));

    connection_2.reset();

    tested->notify(expected);
  });
}

TEST_P(ObservableTests, canHandleSharedExceptions) {
  MockFunction<void(const shared_ptr<DataVariant>&)> mock_observer_cb;
  MockFunction<void(const exception_ptr&)> mock_exception_handler;
  runtime_error test_exception{"Test thrown exceptions in shared handler"};

  EXPECT_CALL(mock_enable_observation, Call(false)).Times(Exactly(1));
  EXPECT_CALL(mock_enable_observation, Call(true)).Times(Exactly(1));
  EXPECT_CALL(mock_observer_cb, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_observer_cb, Call(Pointee(otherThan(expected))))
      .Times(Exactly(1));
  EXPECT_CALL(mock_observer_cb, Call(Pointee(expected)))
      .Times(Exactly(1))
      .WillOnce(Throw(test_exception));
  EXPECT_CALL(mock_exception_handler, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_exception_handler, Call(ExceptionPointee(test_exception)))
      .Times(Exactly(1));

  EXPECT_NO_THROW({
    auto connection = tested->subscribe(mock_observer_cb.AsStdFunction(),
        mock_exception_handler.AsStdFunction());

    tested->notify(expected);
    tested->notify(otherThan(expected));
  });
}

TEST_P(ObservableTests, canHandleSeparateExceptions) {
  MockFunction<void(const shared_ptr<DataVariant>&)> mock_observer_1_cb;
  MockFunction<void(const shared_ptr<DataVariant>&)> mock_observer_2_cb;
  MockFunction<void(const exception_ptr&)> mock_exception_handler_1;
  MockFunction<void(const exception_ptr&)> mock_exception_handler_2;
  runtime_error test_exception{"Test thrown exceptions in separate handler"};

  EXPECT_CALL(mock_enable_observation, Call(false)).Times(Exactly(1));
  EXPECT_CALL(mock_enable_observation, Call(true)).Times(Exactly(1));
  EXPECT_CALL(mock_observer_1_cb, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_observer_1_cb, Call(Pointee(otherThan(expected))))
      .Times(Exactly(1));
  EXPECT_CALL(mock_observer_1_cb, Call(Pointee(expected))).Times(Exactly(2));
  EXPECT_CALL(mock_observer_2_cb, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_observer_2_cb, Call(Pointee(otherThan(expected))))
      .Times(Exactly(1));
  EXPECT_CALL(mock_observer_2_cb, Call(Pointee(expected)))
      .Times(Exactly(1))
      .WillOnce(Throw(test_exception));
  EXPECT_CALL(mock_exception_handler_1, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_exception_handler_2, Call(_)).Times(Exactly(0));
  EXPECT_CALL(mock_exception_handler_2, Call(ExceptionPointee(test_exception)))
      .Times(Exactly(1));

  EXPECT_NO_THROW({
    auto connection_1 = tested->subscribe(mock_observer_1_cb.AsStdFunction(),
        mock_exception_handler_1.AsStdFunction());
    auto connection_2 = tested->subscribe(mock_observer_2_cb.AsStdFunction(),
        mock_exception_handler_2.AsStdFunction());

    tested->notify(expected);
    tested->notify(otherThan(expected));

    connection_2.reset();

    tested->notify(expected);
  });
}

// NOLINTBEGIN(readability-magic-numbers)
INSTANTIATE_TEST_SUITE_P(ObservableTestsValues,
    ObservableTests,
    Values( // clang-format off
        DataVariant(true),
        DataVariant(false),
        DataVariant(intmax_t{15}),
        DataVariant(intmax_t{-20}),
        DataVariant(uintmax_t{69}),
        DataVariant(3.14),
        DataVariant(-45.33333333),
        DataVariant(Timestamp{2025, 9, 11, 10, 01, 24, 32}),
        DataVariant(vector<uint8_t>{}),
        DataVariant(vector<uint8_t>{0x11,0x22,0x31}),
        DataVariant(string()),
        DataVariant(string("Hello World"))
    ), // clang-format on
    [](const TestParamInfo<ObservableTests::ParamType>& info) {
      return "observes" + toSanitizedString(info.param);
    });
// NOLINTEND(readability-magic-numbers)
} // namespace Information_Model_Manager::testing