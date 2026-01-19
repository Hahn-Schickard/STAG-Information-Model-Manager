#include "CallableImpl.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Information_Model_Manager::testing {
using namespace std;
using namespace ::testing;
using namespace Information_Model;

// optional value access is always checked CallableTestParam::supportsResult()
// NOLINTBEGIN(bugprone-unchecked-optional-access)
struct CallableTestParam {
  explicit CallableTestParam(const string& test_name,
      const ParameterTypes& supported_args = {},
      const Parameters& supported_arg_values = {})
      : name(test_name), args(supported_args),
        arg_values(supported_arg_values) {}

  CallableTestParam(const string& test_name,
      DataType result_type,
      const DataVariant& value,
      const ParameterTypes& supported_args = {},
      const Parameters& supported_arg_values = {})
      : name(test_name), type(result_type), result(value), args(supported_args),
        arg_values(supported_arg_values) {}

  bool supportsResult() const { return result.has_value(); }

  // NOLINTNEXTLINE(readability-identifier-naming)
  friend void PrintTo(const CallableTestParam& param, std::ostream* os) {
    if (param.supportsResult()) {
      *os << "Calls " << toString(param.type) << "(" << toString(param.args)
          << ") callable that returns" << toString(param.result.value());
    } else {
      *os << "Executes (" << toString(param.args) << ") callable";
    }
  }

  string name;
  DataType type = DataType::None;
  optional<DataVariant> result = nullopt;
  ParameterTypes args;
  Parameters arg_values;
};

struct CallableTests : public TestWithParam<CallableTestParam> {
  CallableTests() : expected(GetParam()) {
    if (expected.supportsResult()) {
      tested = make_shared<CallableImpl>(expected.type,
          expected.args,
          mock_execute.AsStdFunction(),
          mock_async.AsStdFunction(),
          mock_cancel.AsStdFunction());
      ON_CALL(mock_async, Call(_))
          .WillByDefault([&promised = expected.result](const Parameters&) {
            promise<DataVariant> promised_result;
            auto result_future = ResultFuture(
                make_shared<uintmax_t>(0), promised_result.get_future());
            promised_result.set_value(promised.value());
            return result_future;
          });
    } else {
      tested = make_shared<CallableImpl>(
          expected.args, mock_execute.AsStdFunction());
    }
  }

  MockFunction<void(const Parameters&)> mock_execute;
  MockFunction<ResultFuture(const Parameters&)> mock_async;
  MockFunction<void(uintmax_t)> mock_cancel;
  CallableTestParam expected;
  CallableImplPtr tested;
};

TEST_P(CallableTests, returnsResultType) {
  if (expected.supportsResult()) {
    EXPECT_EQ(tested->resultType(), expected.type);
  } else {
    EXPECT_EQ(tested->resultType(), DataType::None);
  }
}

TEST_P(CallableTests, returnsParameterTypes) {
  EXPECT_THAT(tested->parameterTypes(), ContainerEq(expected.args));
}

TEST_P(CallableTests, canExecute) {
  EXPECT_CALL(mock_execute, Call(expected.arg_values)).Times(Exactly(1));

  EXPECT_NO_THROW(tested->execute(expected.arg_values));
}

TEST_P(CallableTests, canCall) {
  if (expected.supportsResult()) {
    EXPECT_CALL(mock_async, Call(_)).Times(Exactly(1));
    EXPECT_EQ(tested->call(200), expected.result.value());

    EXPECT_CALL(mock_async, Call(expected.arg_values)).Times(Exactly(1));
    EXPECT_EQ(tested->call(expected.arg_values, 200), expected.result.value());
  } else {
    EXPECT_THROW(tested->call(200), ResultReturningNotSupported);

    EXPECT_THROW(
        tested->call(expected.arg_values, 200), ResultReturningNotSupported);
  }
}

TEST_P(CallableTests, canAsyncCall) {
  if (expected.supportsResult()) {
    EXPECT_CALL(mock_async, Call(expected.arg_values)).Times(Exactly(1));
    auto result_future = tested->asyncCall(expected.arg_values);
    EXPECT_EQ(result_future.get(), expected.result.value());
  } else {
    EXPECT_THROW(
        tested->asyncCall(expected.arg_values), ResultReturningNotSupported);
  }
}

TEST_P(CallableTests, canTimeout) {
  if (expected.supportsResult()) {
    promise<DataVariant> promised_result;
    EXPECT_CALL(mock_async, Call(expected.arg_values))
        .Times(Exactly(2))
        .WillOnce([&promised_result](const Parameters&) {
          // Cause a timeout
          auto result_future = ResultFuture(
              make_shared<uintmax_t>(0), promised_result.get_future());
          return result_future;
        });

    EXPECT_THROW(tested->call(expected.arg_values, 200), CallTimedout);
    promised_result.set_value(true); // avoid broken future exception

    EXPECT_EQ(tested->call(expected.arg_values, 200), expected.result.value());
  } else {
    EXPECT_THROW(
        tested->call(expected.arg_values, 200), ResultReturningNotSupported);
  }
}

TEST_P(CallableTests, canCancelCall) {
  if (expected.supportsResult()) {
    promise<DataVariant> promised_result;
    EXPECT_CALL(mock_async, Call(expected.arg_values))
        .Times(Exactly(1))
        .WillOnce([&promised_result](const Parameters&) {
          auto result_future = ResultFuture(
              make_shared<uintmax_t>(0), promised_result.get_future());
          return result_future;
        });
    EXPECT_CALL(mock_cancel, Call(_))
        .Times(Exactly(1))
        .WillOnce([&promised_result](uintmax_t id) {
          promised_result.set_exception(
              make_exception_ptr(CallCanceled(id, "Callable")));
        });
    auto result_future = tested->asyncCall(expected.arg_values);

    EXPECT_NO_THROW(tested->cancelAsyncCall(result_future.id()););

    EXPECT_THROW(result_future.get(), CallCanceled);
  } else {
    EXPECT_THROW(
        tested->asyncCall(expected.arg_values), ResultReturningNotSupported);
  }
}

// NOLINTBEGIN(readability-magic-numbers)
INSTANTIATE_TEST_SUITE_P(CallableTestsValues,
    CallableTests,
    Values( // clang-format off
        CallableTestParam{
          "NoResultAndNoParameters"
        },
        CallableTestParam{
          "BoolResultWithoutParameters",
          DataType::Boolean, 
          true,
        },
        CallableTestParam{
          "IntegerResultWithoutParameters",
          DataType::Integer, 
          (intmax_t)-11
        },
        CallableTestParam{
          "UIntegerResultWithoutParameters",
          DataType::Unsigned_Integer, 
          (uintmax_t)25
        },
        CallableTestParam{
          "DoubleResultWithoutParameters",
          DataType::Double, 
          30.2
        },
        CallableTestParam{
          "TimeResultWithoutParameters",
          DataType::Timestamp,
          Timestamp{2025, 9, 11, 10, 01, 24, 32}
        },
        CallableTestParam{
          "OpaqueResultWithoutParameters",
          DataType::Opaque,
          vector<uint8_t>{0x00,0x01,0x02}
        },
        CallableTestParam{
          "StringResultWithoutParameters",
          DataType::String,
          "hello world"
        }
    ), // clang-format on
    [](const TestParamInfo<CallableTests::ParamType>& info) {
      return info.param.name;
    });
// NOLINTEND(readability-magic-numbers)

// NOLINTEND(bugprone-unchecked-optional-access)
} // namespace Information_Model_Manager::testing