#include "ModelImplementantionTestSuite.hpp"

TEST(RefIdTests, DeviceRefIdIsCorrect) {
  // Arrange
  shared_ptr<Device> element = make_shared<DeviceImpl>(
      "1234", "TestDevice", "A hardcoded deviceelement");

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
  shared_ptr<Device> element = make_shared<DeviceImpl>(
      "1234", "TestDevice", "A hardcoded deviceelement");

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
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
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
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
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
  shared_ptr<DeviceElementGroup> element = make_shared<DeviceElementGroupImpl>(
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
  shared_ptr<DeviceElementGroup> element = make_shared<DeviceElementGroupImpl>(
      "1234", "TestDevice", "A hardcoded deviceelement");

  // Act
  string tested_element = element->getElementRefId();
  // Assert
  string expected_result = "1235";
  EXPECT_NE(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}