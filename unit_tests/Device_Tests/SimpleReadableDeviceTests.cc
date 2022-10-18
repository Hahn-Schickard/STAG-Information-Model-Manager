#include "DeviceImplementationBuilder.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace std;
using namespace Information_Model;
using namespace Information_Model_Manager;

class SimpleReadableDeviceTests : public ::testing::Test {
  struct ReadFunctionMock {
    MOCK_METHOD0(BracketsOperator, DataVariant(void));
    DataVariant operator()(void) { return BracketsOperator(); }
  };

public:
  SimpleReadableDeviceTests() {}

  void SetUp() {
    DeviceImplementationBuilder builder("1234", "Simple Readable Device",
                                        "Lorem Ipsum");
    metric_id = builder.addReadableMetric(
        "Readble", "This is a readable BOOLEAN metric", DataType::BOOLEAN,
        bind(&ReadFunctionMock::operator(), &readCallback));
    if (metric_id.empty()) {
      throw runtime_error("Failed to build readable metric!");
    } else {
      device = builder.getResult();
    }
  }

  ReadFunctionMock readCallback;
  shared_ptr<Device> device;
  string metric_id;
};

TEST_F(SimpleReadableDeviceTests, returnsCorrectDeviceID) {
  string tested_element = device->getElementId();
  string expected_result = "1234";
  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}
TEST_F(SimpleReadableDeviceTests, executesReadCallback) {
  EXPECT_CALL(readCallback, BracketsOperator());
  auto metric = static_pointer_cast<Metric>(
      device->getDeviceElementGroup()->getSubelement(metric_id));
  ASSERT_NO_THROW(metric->getMetricValue());
}
