#include "Device.hpp"
#include "DeviceBuilder.hpp"
#include "DeviceElementBuilder.hpp"
#include "DeviceElementGroupImpl.hpp"
#include "DeviceImpl.hpp"

#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace Model_Factory;
using namespace Information_Model;

TEST(DeviceElementTest, DeviceElementTypeUndefIsCorrect) {
  // Arrange
  DeviceElement* element = new DeviceElementBuilder("1234",
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
  DeviceElement* element = new DeviceElementBuilder("1234",
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
  DeviceElement* element = new DeviceElementBuilder(
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
  DeviceElement* element = new DeviceElementBuilder(
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
  DeviceElement* element = new DeviceElementBuilder(
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
  DeviceElement* element = new DeviceElementBuilder(
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
  DeviceElement* element = new DeviceElementBuilder("1234",
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
  DeviceElement* element = new DeviceElementBuilder("1234",
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
  DeviceElement* element = new DeviceElementBuilder(
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
  DeviceElement* element = new DeviceElementBuilder(
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
  DeviceElement* element = new DeviceElementBuilder(
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
  DeviceElement* element = new DeviceElementBuilder(
      "1234", "TestDevice", "A hardcoded deviceelement", ElementType::FUNCTION);
  // Act
  ElementType tested_element = element->getElementType();
  // Assert
  ElementType expected_result = ElementType::UNDEFINED;
  EXPECT_NE(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}