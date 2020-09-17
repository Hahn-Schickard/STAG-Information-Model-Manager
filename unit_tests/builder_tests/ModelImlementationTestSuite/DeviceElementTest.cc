#include "DeviceBuilder.hpp"
#include "ModelImplementantionTestSuite.hpp"

TEST(DeviceElementTest, DeviceElementTypeUndefIsCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>("1234",
      "TestDevice",
      "A hardcoded deviceelement",
      ElementType::UNDEFINED);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::UNDEFINED;
  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(DeviceElementTest, DeviceElementTypeUndefIsNotCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>("1234",
      "TestDevice",
      "A hardcoded deviceelement",
      ElementType::UNDEFINED);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::GROUP;
  EXPECT_NE(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(DeviceElementTest, DeviceElementTypeGroupIsCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::GROUP);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::GROUP;
  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(DeviceElementTest, DeviceElementTypeGroupIsNotCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::GROUP);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::UNDEFINED;
  EXPECT_NE(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(DeviceElementTest, DeviceElementTypeReadOnlyIsCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::READABLE);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::READABLE;
  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(DeviceElementTest, DeviceElementTypeReadOnlyIsNotCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::READABLE);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::UNDEFINED;
  EXPECT_NE(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(DeviceElementTest, DeviceElementTypeObservableIsCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>("1234",
      "TestDevice",
      "A hardcoded deviceelement",
      ElementType::OBSERVABLE);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::OBSERVABLE;
  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(DeviceElementTest, DeviceElementTypeObservableIsNotCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>("1234",
      "TestDevice",
      "A hardcoded deviceelement",
      ElementType::OBSERVABLE);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::UNDEFINED;
  EXPECT_NE(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(DeviceElementTest, DeviceElementTypeWritableIsCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::WRITABLE);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::WRITABLE;
  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(DeviceElementTest, DeviceElementTypeWritableIsNotCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::WRITABLE);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::UNDEFINED;
  EXPECT_NE(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(DeviceElementTest, DeviceElementTypeFunctionIsCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::FUNCTION);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::FUNCTION;
  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST(DeviceElementTest, DeviceElementTypeFunctionIsNotCorrect) {
  // Arrange
  shared_ptr<DeviceElement> element = make_shared<DeviceElementBuilder>(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::FUNCTION);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::UNDEFINED;
  EXPECT_NE(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}