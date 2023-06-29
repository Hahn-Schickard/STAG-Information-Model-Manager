#include "DeviceBuilder.hpp"

#include "HaSLL/LoggerManager.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace std;
using namespace Information_Model;
using namespace Information_Model_Manager;
using namespace HaSLI;

class SimpleWritableDeviceTests : public ::testing::Test {
  struct ReadFunctionMock {
    MOCK_METHOD(DataVariant, BracketsOperator, ());
    virtual DataVariant operator()() { return BracketsOperator(); }
  };

  struct WriteFunctionMock {
    MOCK_METHOD(void, BracketsOperator, (DataVariant /*value*/));
    virtual void operator()(DataVariant value) {
      return BracketsOperator(move(value));
    }
  };

public:
  SimpleWritableDeviceTests() = default;

  void SetUp() override {
    auto builder = DeviceBuilder(
        LoggerManager::registerLogger("SimpleWritableDeviceTestsLogger"));
    builder.buildDeviceBase("1234", "Simple Writable Device", "Lorem Ipsum");
    metric_id = builder.addWritableMetric("Writable",
        "This is a writable INTEGER metric",
        DataType::INTEGER,
        bind(&WriteFunctionMock::operator(), &write_callback, placeholders::_1),
        bind(&ReadFunctionMock::operator(), &read_callback));
    device = builder.getResult();
  }

  ReadFunctionMock read_callback;
  WriteFunctionMock write_callback;
  shared_ptr<Device> device;
  string metric_id;
};

// NOLINTNEXTLINE
TEST_F(SimpleWritableDeviceTests, returnsCorrectDeviceID) {
  string tested_element = device->getElementId();
  string expected_result = "1234";
  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

// NOLINTNEXTLINE
TEST_F(SimpleWritableDeviceTests, executesReadCallback) {
  EXPECT_CALL(read_callback, BracketsOperator());
  auto metric = std::get<NonemptyWritableMetricPtr>(
      device->getDeviceElementGroup()->getSubelement(metric_id)->functionality);
  ASSERT_NO_THROW(metric->getMetricValue());
}

// NOLINTNEXTLINE
TEST_F(SimpleWritableDeviceTests, executesWriteCallback) {
  EXPECT_CALL(write_callback, BracketsOperator((DataVariant)(int64_t)19));
  auto metric = std::get<NonemptyWritableMetricPtr>(
      device->getDeviceElementGroup()->getSubelement(metric_id)->functionality);
  ASSERT_NO_THROW(metric->setMetricValue((int64_t)19));
}
