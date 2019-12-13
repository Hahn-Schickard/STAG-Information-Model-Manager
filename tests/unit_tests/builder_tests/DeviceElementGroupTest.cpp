#include "Device.hpp"
#include "DeviceElementBuilder.hpp"
#include "DeviceElementGroupImpl.hpp"
#include "DeviceImpl.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace Model_Factory;
using namespace Information_Model;

class DeviceElementGroupTest : public ::testing::Test {
 public:
  Device* device;
  shared_ptr<Information_Model::DeviceElementGroup> group;
  vector<shared_ptr<DeviceElement>> elements;

  DeviceElementGroupTest() {}

  void SetUp() {
    device = new DeviceImpl("1234", "TestDevice", "A hardcoded deviceelement");
    DeviceImpl* tmp_device = dynamic_cast<DeviceImpl*>(device);
    tmp_device->addDeviceElementGroup(
        "TestGroup", "This is a synthetic test for device element group.");
    group          = device->getDeviceElementGroup();
    auto tmp_group = static_pointer_cast<DeviceElementGroupImpl>(group);
    tmp_group->addDeviceElement(
        "SubTestDevice", "This is the first Subelement", ElementType::READABLE);
    elements = group->getSubelements();
  }

  void TearDown() {
    delete device;
  }
};

TEST_F(DeviceElementGroupTest, DeviceElementGroupSubelementIDIsCorrect) {
  // Act
  // NOLINTNEXTLINE
  for(auto element : elements) {
    string tested_element = element->getElementRefId();
    // Assert
    string expected_result = "1234:0";
    EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
        << "expected: " << expected_result << endl
        << "provided: " << tested_element << endl;
  }
}

TEST_F(DeviceElementGroupTest, DeviceElementGroupSubelementIDIsNotCorrect) {
  // Act
  // NOLINTNEXTLINE
  for(auto element : elements) {
    string tested_element = element->getElementRefId();
    // Assert
    string expected_result = "1234:1";
    EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
        << "expected: " << expected_result << endl
        << "provided: " << tested_element << endl;
  }
}

TEST_F(DeviceElementGroupTest, DeviceElementGroupSubelementNameIsCorrect) {
  // Act
  // NOLINTNEXTLINE
  for(auto element : elements) {
    string tested_element = element->getElementName();
    // Assert
    string expected_result = "SubTestDevice";
    EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
        << "expected: " << expected_result << endl
        << "provided: " << tested_element << endl;
  }
}

TEST_F(DeviceElementGroupTest, DeviceElementGroupSubelementNameIsNotCorrect) {
  // Act
  // NOLINTNEXTLINE
  for(auto element : elements) {
    string tested_element = element->getElementName();
    // Assert
    string expected_result = "SubTestDevice2";
    EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
        << "expected: " << expected_result << endl
        << "provided: " << tested_element << endl;
  }
}

TEST_F(DeviceElementGroupTest,
    DeviceElementGroupSubelementDescriptionIsCorrect) {
  // Act
  // NOLINTNEXTLINE
  for(auto element : elements) {
    string tested_element = element->getElementDescription();
    // Assert
    string expected_result = "This is the first Subelement";
    EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
        << "expected: " << expected_result << endl
        << "provided: " << tested_element << endl;
  }
}

TEST_F(DeviceElementGroupTest,
    DeviceElementGroupSubelementDescriptionIsNotCorrect) {
  // Act
  // NOLINTNEXTLINE
  for(auto element : elements) {
    string tested_element = element->getElementDescription();
    // Assert
    string expected_result = "This is not the first Subelement";
    EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
        << "expected: " << expected_result << endl
        << "provided: " << tested_element << endl;
  }
}