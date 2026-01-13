#include "ReadableImpl.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Information_Model_Manager::testing {
using namespace std;
using namespace ::testing;
using namespace Information_Model;

struct ReadableTests : public TestWithParam<DataVariant> {
  ReadableTests() : expected(GetParam()) {
    tested = make_shared<ReadableImpl>(
        toDataType(expected), mock_callback.AsStdFunction());
    ON_CALL(mock_callback, Call()).WillByDefault(Return(expected));
  }

  DataVariant expected;
  MockFunction<DataVariant(void)> mock_callback;
  ReadableImplPtr tested;
};

TEST_P(ReadableTests, returnsDataType) {
  EXPECT_EQ(tested->dataType(), toDataType(expected));
}

TEST_P(ReadableTests, canRead) {
  EXPECT_CALL(mock_callback, Call()).Times(Exactly(1));

  EXPECT_EQ(tested->read(), expected);
}

TEST_P(ReadableTests, canReadTwice) {
  EXPECT_CALL(mock_callback, Call()).Times(Exactly(2));

  EXPECT_EQ(tested->read(), expected);
  EXPECT_EQ(tested->read(), expected);
}

// NOLINTBEGIN(readability-magic-numbers)
INSTANTIATE_TEST_SUITE_P(ReadableTestsValues,
    ReadableTests,
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
    [](const TestParamInfo<ReadableTests::ParamType>& info) {
      return "reads" + toSanitizedString(info.param);
    });
// NOLINTEND(readability-magic-numbers)
} // namespace Information_Model_Manager::testing