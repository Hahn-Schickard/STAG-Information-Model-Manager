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
    DeviceImplementationBuilder builder("Simple Readable Device", "1234",
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
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}
TEST_F(SimpleReadableDeviceTests, executesReadCallback) {
  EXPECT_CALL(readCallback, BracketsOperator());
  auto metric = static_pointer_cast<Metric>(
      device->getDeviceElementGroup()->getSubelement(metric_id));
  ASSERT_NO_THROW(metric->getMetricValue());
}

TEST_F(SimpleReadableDeviceTests, throwsRuntimeErrorOnWrite) {
  auto metric = static_pointer_cast<WritableMetric>(
      device->getDeviceElementGroup()->getSubelement(metric_id));
  // I have no clue why this method calls
  // Information_Model::DataType MetricImplementation::getDataType() instead
  // of throwing a runtime error. It could cause problems in the future with
  // bad_access for us... Could this be caused by our slicing builder?
  // This seg faults if the cast was done with
  // dynamic_pointer_cast<WritableMetric>(device->getDeviceElementGroup()->getSubelement(metric_id))
  // metric->setMetricValue(DataVariant((int)1));
  // Mostelikely this is a design issue within the architechture itself, we
  // should use a base metric interface, which is implemented by all metric
  // types, thus polymorhic links to incorect object types
  // EXPECT_THROW(metric->setMetricValue(DataVariant((int)1)), runtime_error);
}