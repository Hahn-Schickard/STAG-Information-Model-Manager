#include "Device.hpp"
#include "DeviceElementBuilder.hpp"
#include "DeviceElementGroupImpl.hpp"
#include "DeviceImpl.hpp"

#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace Model_Factory;
using namespace Information_Model;

TEST(RefIdTests, DeviceRefIdIsCorrect) {
  // Arrange
  Device* element
      = new DeviceImpl("1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementRefId();

  // Assert
  string expected_result = "1234";
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(RefIdTests, DeviceRefIdIsNotCorrect) {
  // Arrange
  Device* element
      = new DeviceImpl("1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementRefId();
  // Assert
  string expected_result = "1235";
  EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(RefIdTests, DeviceElementRefIdIsCorrect) {
  // Arrange
  DeviceElement* element = new DeviceElementBuilder(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::GROUP);

  // Act
  string tested_element = element->getElementRefId();
  // Assert
  string expected_result = "1234";
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(RefIdTests, DeviceElementRefIdIsNotCorrect) {
  // Arrange
  DeviceElement* element = new DeviceElementBuilder(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::GROUP);

  // Act
  string tested_element = element->getElementRefId();
  // Assert
  string expected_result = "1235";
  EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(RefIdTests, DeviceElementGroupRefIdIsCorrect) {
  // Arrange
  DeviceElementGroup* element = new DeviceElementGroupImpl(
      "1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementRefId();
  // Assert
  string expected_result = "1234";
  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(RefIdTests, DeviceElementGroupRefIdIsNotCorrect) {
  // Arrange
  DeviceElementGroup* element = new DeviceElementGroupImpl(
      "1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementRefId();
  // Assert
  string expected_result = "1235";
  EXPECT_NE(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}