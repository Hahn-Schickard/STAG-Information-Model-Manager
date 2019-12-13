#include "Device.hpp"
#include "DeviceElementBuilder.hpp"
#include "DeviceElementGroupImpl.hpp"
#include "DeviceImpl.hpp"

#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace Model_Factory;
using namespace Information_Model;

TEST(ElementNameTests, DeviceNameIsCorrect) {
  // Arrange
  Device* element
      = new DeviceImpl("1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementName();
  // Assert
  string expected_result = "TestDevice";
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(ElementNameTests, DeviceNameIsNotCorrect) {
  // Arrange
  Device* element
      = new DeviceImpl("1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementName();
  // Assert
  string expected_result = "TestDevice2";
  EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(ElementNameTests, DeviceElementNameIsCorrect) {
  // Arrange
  DeviceElement* element = new DeviceElementBuilder(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::GROUP);

  // Act
  string tested_element = element->getElementName();
  // Assert
  string expected_result = "TestDevice";
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(ElementNameTests, DeviceElementNameIsNotCorrect) {
  // Arrange
  DeviceElement* element = new DeviceElementBuilder(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::GROUP);

  // Act
  string tested_element = element->getElementName();
  // Assert
  string expected_result = "TestDevice2";
  EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(ElementNameTests, DeviceElementGroupNameIsCorrect) {
  // Arrange
  DeviceElementGroup* element = new DeviceElementGroupImpl(
      "1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementName();
  // Assert
  string expected_result = "TestDevice";
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(ElementNameTests, DeviceElementGroupNameIsNotCorrect) {
  // Arrange
  DeviceElementGroup* element = new DeviceElementGroupImpl(
      "1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementName();
  // Assert
  string expected_result = "TestDevice2";
  EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}