#include "DeviceElementGroupImpl.hpp"
#include "ModelImplementantionTestSuite.hpp"

TEST(ElementDescriptionTests, DeviceDescriptionIsCorrect) {
  // Arrange
  shared_ptr<Device> element = make_shared<DeviceImpl>(
      "1234", "TestDevice", "A hardcoded deviceelement");

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
  shared_ptr<Device> element = make_shared<DeviceImpl>(
      "1234", "TestDevice", "A hardcoded deviceelement");

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
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
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
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
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
  shared_ptr<DeviceElementGroup> element = make_shared<DeviceElementGroupImpl>(
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
  shared_ptr<DeviceElementGroup> element = make_shared<DeviceElementGroupImpl>(
      "1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementDescription();
  // Assert
  string expected_result = "A new hardcoded deviceelement";
  EXPECT_STRNE(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}