#include "Device.hpp"
#include "DeviceElementBuilder.hpp"
#include "DeviceElementGroupImpl.hpp"
#include "DeviceImpl.hpp"

#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace Model_Factory;
using namespace Information_Model;

TEST(ElementDescriptionTests, DeviceDescriptionIsCorrect) {
  // Arrange
  Device* element
      = new DeviceImpl("1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementDescription();
  // Assert
  string expected_result = "A hardcoded deviceelement";
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(ElementDescriptionTests, DeviceDescriptionIsNotCorrect) {
  // Arrange
  Device* element
      = new DeviceImpl("1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementDescription();
  // Assert
  string expected_result = "A new hardcoded deviceelement";
  EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(ElementDescriptionTests, DeviceElementDescriptionIsCorrect) {
  // Arrange
  DeviceElement* element = new DeviceElementBuilder(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::GROUP);

  // Act
  string tested_element = element->getElementDescription();
  // Assert
  string expected_result = "A hardcoded deviceelement";
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(ElementDescriptionTests, DeviceElementDescriptionIsNotCorrect) {
  // Arrange
  DeviceElement* element = new DeviceElementBuilder(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::GROUP);

  // Act
  string tested_element = element->getElementDescription();
  // Assert
  string expected_result = "A new hardcoded deviceelement";
  EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(ElementDescriptionTests, DeviceElementGroupDescriptionIsCorrect) {
  // Arrange
  DeviceElementGroup* element = new DeviceElementGroupImpl(
      "1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementDescription();
  // Assert
  string expected_result = "A hardcoded deviceelement";
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(ElementDescriptionTests, DeviceElementGroupDescriptionIsNotCorrect) {
  // Arrange
  DeviceElementGroup* element = new DeviceElementGroupImpl(
      "1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementDescription();
  // Assert
  string expected_result = "A new hardcoded deviceelement";
  EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}