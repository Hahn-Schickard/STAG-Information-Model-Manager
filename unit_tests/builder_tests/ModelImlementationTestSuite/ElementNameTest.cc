#include "ModelImplementantionTestSuite.hpp"

TEST(ElementNameTests, DeviceNameIsCorrect) {
  // Arrange
  shared_ptr<Device> element = make_shared<DeviceImpl>(
      "1234", "TestDevice", "A hardcoded deviceelement");

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
  shared_ptr<Device> element = make_shared<DeviceImpl>(
      "1234", "TestDevice", "A hardcoded deviceelement");

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
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
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
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
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
  shared_ptr<DeviceElementGroup> element = make_shared<DeviceElementGroupImpl>(
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