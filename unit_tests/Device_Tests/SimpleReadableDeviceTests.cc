#include "DeviceBuilder.hpp"

#include "HaSLL/LoggerManager.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace std;
using namespace Information_Model;
using namespace Information_Model_Manager;
using namespace HaSLL;

class SimpleReadableDeviceTests : public ::testing::Test {
  struct ReadFunctionMock {
    MOCK_METHOD0(BracketsOperator, DataVariant());
    DataVariant operator()() { return BracketsOperator(); }
  };

public:
  SimpleReadableDeviceTests() = default;

  void SetUp() override {
    auto builder = DeviceBuilder(
        LoggerManager::registerLogger("SimpleReadableDeviceTestsLogger"));
    builder.buildDeviceBase("1234", "Simple Readable Device", "Lorem Ipsum");
    metric_id = builder.addReadableMetric("Readable",
        "This is a readable BOOLEAN metric",
        DataType::BOOLEAN,
        bind(&ReadFunctionMock::operator(), &read_callback));
    if (metric_id.empty()) {
      throw runtime_error("Failed to build readable metric!");
    } else {
      device = builder.getResult();
    }
  }

  ReadFunctionMock read_callback;
  shared_ptr<Device> device;
  string metric_id;
};

// NOLINTNEXTLINE
TEST_F(SimpleReadableDeviceTests, returnsCorrectDeviceID) {
  string tested_element = device->getElementId();
  string expected_result = "1234";
  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}
// NOLINTNEXTLINE
TEST_F(SimpleReadableDeviceTests, executesReadCallback) {
  EXPECT_CALL(read_callback, BracketsOperator());
  auto metric = std::get<NonemptyMetricPtr>(
      device->getDeviceElementGroup()->getSubelement(metric_id)->functionality);
  ASSERT_NO_THROW(metric->getMetricValue());
}
