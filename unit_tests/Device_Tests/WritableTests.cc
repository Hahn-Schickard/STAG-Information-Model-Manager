#include "WritableImpl.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>

namespace Information_Model_Manager::testing {
using namespace std;
using namespace ::testing;
using namespace Information_Model;

// optional value access is always checked via WritableTestParam::isWriteOnly()
// NOLINTBEGIN(bugprone-unchecked-optional-access)
struct WritableTestParam {
  explicit WritableTestParam(DataType test_type) : type(test_type) {}

  explicit WritableTestParam(const DataVariant& test_value)
      : type(toDataType(test_value)), value(test_value) {}

  bool isWriteOnly() const { return !value.has_value(); }

  // NOLINTNEXTLINE(readability-identifier-naming)
  friend void PrintTo(const WritableTestParam& param, std::ostream* os) {
    *os << "(write_only: " << param.isWriteOnly()
        << (param.isWriteOnly() ? ""
                                : ", value: " + toString(param.value.value()))
        << ", type: " << toString(param.type) << ")";
  }

  DataType type;
  optional<DataVariant> value = nullopt;
};

struct WritableTests : public TestWithParam<WritableTestParam> {
  WritableTests() : expected(GetParam()) {
    if (!expected.isWriteOnly()) {
      tested = make_shared<WritableImpl>(expected.type,
          mock_readable.AsStdFunction(),
          mock_writable.AsStdFunction());
      ON_CALL(mock_readable, Call())
          .WillByDefault(Return(expected.value.value()));
    } else {
      tested = make_shared<WritableImpl>(
          expected.type, mock_writable.AsStdFunction());
    }
  }

  WritableTestParam expected;
  MockFunction<DataVariant(void)> mock_readable;
  MockFunction<void(const DataVariant&)> mock_writable;
  WritableImplPtr tested;
};

TEST_P(WritableTests, returnsDataType) {
  EXPECT_EQ(tested->dataType(), expected.type);
}

TEST_P(WritableTests, canRead) {
  if (tested->isWriteOnly()) {
    EXPECT_CALL(mock_readable, Call()).Times(Exactly(0));
    EXPECT_THROW(tested->read(), NonReadable);
  } else {
    EXPECT_CALL(mock_readable, Call()).Times(Exactly(1));
    EXPECT_EQ(tested->read(), expected.value.value());
  }
}

TEST_P(WritableTests, canReadTwice) {
  if (tested->isWriteOnly()) {
    EXPECT_CALL(mock_readable, Call()).Times(Exactly(0));
    EXPECT_THROW(tested->read(), NonReadable);
    EXPECT_THROW(tested->read(), NonReadable);
  } else {
    EXPECT_CALL(mock_readable, Call()).Times(Exactly(2));
    EXPECT_EQ(tested->read(), expected.value.value());
    EXPECT_EQ(tested->read(), expected.value.value());
  }
}

// NOLINTBEGIN(readability-magic-numbers)
INSTANTIATE_TEST_SUITE_P(WritableTestsValues,
    WritableTests,
    Values( // clang-format off
        WritableTestParam{DataType::Boolean},
        WritableTestParam{DataType::Integer},
        WritableTestParam{DataType::Unsigned_Integer},
        WritableTestParam{DataType::Double},
        WritableTestParam{DataType::Timestamp},
        WritableTestParam{DataType::Opaque},
        WritableTestParam{DataType::String},
        WritableTestParam{DataVariant(true)},
        WritableTestParam{DataVariant(intmax_t{15})},
        WritableTestParam{DataVariant(intmax_t{-20})},
        WritableTestParam{DataVariant(uintmax_t{69})},
        WritableTestParam{DataVariant(3.14)},
        WritableTestParam{DataVariant(-45.33333333)},
        WritableTestParam{DataVariant(Timestamp{2025, 9, 11, 10, 01, 24, 32})},
        WritableTestParam{DataVariant(vector<uint8_t>{0x11,0x22,0x31})},
        WritableTestParam{DataVariant(string("Hello World"))}
    ), // clang-format on
    [](const TestParamInfo<WritableTests::ParamType>& info) {
      string name;
      if (info.param.isWriteOnly()) {
        name = "writes" + toSanitizedString(info.param.type);
      } else {
        name += "reads" + toSanitizedString(info.param.value.value());
      }
      return name;
    });
// NOLINTEND(readability-magic-numbers)
// NOLINTEND(bugprone-unchecked-optional-access)

} // namespace Information_Model_Manager::testing