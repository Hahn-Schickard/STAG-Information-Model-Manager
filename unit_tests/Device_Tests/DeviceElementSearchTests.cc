#include "DeviceBuilder.hpp"

#include "HaSLL/LoggerManager.hpp"

#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace std;
using namespace Information_Model;
using namespace Information_Model_Manager;
using namespace HaSLL;

class DeviceElementSearchTests : public ::testing::Test {
public:
  DeviceElementSearchTests() = default;

  void SetUp() override {
    auto builder = DeviceBuilder([](const exception_ptr&) {},
        LoggerManager::registerLogger("DeviceElementSearchTestsLogger"));
    builder.buildDeviceBase("Simple Readable Device", "1234", "Lorem Ipsum");
    readable_metric_1_id = builder.addReadableMetric("Readable",
        "This is a readable BOOLEAN metric",
        DataType::BOOLEAN,
        nullptr);
    builder.addReadableMetric("Readable",
        "This is a readable BOOLEAN metric",
        DataType::BOOLEAN,
        nullptr);
    auto subgroup_1_id =
        builder.addDeviceElementGroup("Group 1", "Just some group.");
    writable_metric_1_id = builder.addWritableMetric(subgroup_1_id,
        "Writable",
        "This is a writable INTEGER metric",
        DataType::INTEGER,
        nullptr,
        nullptr);
    auto subgroup_2_id = builder.addDeviceElementGroup(
        subgroup_1_id, "Group 2", "Just some other group");
    readable_metric_2_id = builder.addReadableMetric(subgroup_2_id,
        "Readable",
        "This is a readable FLOAT metric",
        DataType::DOUBLE,
        nullptr);
    builder.addWritableMetric(subgroup_2_id,
        "Writable",
        "This is a writable INTEGER metric",
        DataType::INTEGER,
        nullptr,
        nullptr);
    builder.addReadableMetric("Readable",
        "This is a readable STRING metric",
        DataType::STRING,
        nullptr);
    device = builder.getResult();
  }

  shared_ptr<Device> device;
  string readable_metric_1_id;
  string readable_metric_2_id;
  string writable_metric_1_id;
};

// NOLINTNEXTLINE
TEST_F(DeviceElementSearchTests, findsRootReadbleMetric) {
  auto metric = device->getDeviceElement(readable_metric_1_id);

  ASSERT_NE(metric.base(), nullptr);

  string tested_element = metric->getElementId();
  string expected_result = readable_metric_1_id;
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

// NOLINTNEXTLINE
TEST_F(DeviceElementSearchTests, findsGroup1WritableMetric) {
  auto metric = device->getDeviceElement(writable_metric_1_id);

  ASSERT_NE(metric.base(), nullptr);

  string tested_element = metric->getElementId();
  string expected_result = writable_metric_1_id;
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

// NOLINTNEXTLINE
TEST_F(DeviceElementSearchTests, findsGroup2ReadableMetric) {
  auto metric = device->getDeviceElement(readable_metric_2_id);

  ASSERT_NE(metric.base(), nullptr);

  string tested_element = metric->getElementId();
  string expected_result = readable_metric_2_id;
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

// NOLINTNEXTLINE
TEST_F(DeviceElementSearchTests, throwsForNonExistantElement) {
  EXPECT_THROW(device->getDeviceElement("SomeBadID"), DeviceElementNotFound);
}
