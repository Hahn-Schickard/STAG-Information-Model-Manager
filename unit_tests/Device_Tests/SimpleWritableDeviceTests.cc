#include "DeviceImplementationBuilder.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace std;
using namespace Information_Model;
using namespace Information_Model_Manager;

class SimpleWritableDeviceTests : public ::testing::Test {
  struct ReadFunctionMock {
    MOCK_METHOD0(BracketsOperator, DataVariant(void));
    DataVariant operator()(void) { return BracketsOperator(); }
  };

  struct WriteFunctionMock {
    MOCK_METHOD1(BracketsOperator, void(DataVariant value));
    virtual void operator()(DataVariant value) {
      return BracketsOperator(move(value));
    }
  };

public:
  SimpleWritableDeviceTests() {}

  void SetUp() {
    DeviceImplementationBuilder builder("1234", "Simple Writable Device",
                                        "Lorem Ipsum");
    metric_id = builder.addWritableMetric(
        "Writable", "This is a writable INTEGER metric", DataType::INTEGER,
        bind(&ReadFunctionMock::operator(), &readCallback),
        bind(&WriteFunctionMock::operator(), &writeCallback, placeholders::_1));
    device = builder.getResult();
  }

  ReadFunctionMock readCallback;
  WriteFunctionMock writeCallback;
  shared_ptr<Device> device;
  string metric_id;
};

TEST_F(SimpleWritableDeviceTests, returnsCorrectDeviceID) {
  string tested_element = device->getElementId();
  string expected_result = "1234";
  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}
TEST_F(SimpleWritableDeviceTests, executesReadCallback) {
  EXPECT_CALL(readCallback, BracketsOperator());
  auto metric = static_pointer_cast<Metric>(
      device->getDeviceElementGroup()->getSubelement(metric_id));
  ASSERT_NO_THROW(metric->getMetricValue());
}

TEST_F(SimpleWritableDeviceTests, executesWriteCallback) {
  EXPECT_CALL(writeCallback, BracketsOperator((DataVariant)(int64_t)19));
  auto metric = static_pointer_cast<WritableMetric>(
      device->getDeviceElementGroup()->getSubelement(metric_id));
  ASSERT_NO_THROW(metric->setMetricValue((int64_t)19));
}
