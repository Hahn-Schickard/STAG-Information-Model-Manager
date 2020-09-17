#include "DeviceBuilderTestSuite.hpp"

class SingleReadableElementDeviceTest : public ::testing::Test {
 public:
  shared_ptr<Device> device;

  SingleReadableElementDeviceTest() {}

  void SetUp() {
    DeviceBuilder* builder
        = new DeviceBuilder("TestDevice", "123", "A device for testing only");
    builder->addDeviceElement(
        "First Element", "The first and only element.", ElementType::READABLE);
    shared_ptr<Information_Model::Device> device = builder->getDevice();
    delete builder;
  }
};

TEST_F(SingleReadableElementDeviceTest, ReturnsCorrectDeviceID) {
  string expected_result = "123";
  string tested_element  = device->getElementRefId();

  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST_F(SingleReadableElementDeviceTest, ReturnsCorrectDeviceName) {
  string expected_result = "TestDevice";
  string tested_element  = device->getElementName();

  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST_F(SingleReadableElementDeviceTest, ReturnsCorrectDeviceDescription) {
  string expected_result = "A device for testing only";
  string tested_element  = device->getElementDescription();

  EXPECT_STREQ(expected_result.c_str(), tested_element.c_str())
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST_F(SingleReadableElementDeviceTest, ContainsAGroup) {
  ElementType expected_result = ElementType::GROUP;
  ElementType tested_element
      = device->getDeviceElementGroup()->getElementType();

  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST_F(SingleReadableElementDeviceTest, ContainsOnlyOneElement) {
  size_t expected_result = 1;
  size_t tested_element
      = device->getDeviceElementGroup()->getSubelements().size();

  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}

TEST_F(SingleReadableElementDeviceTest, ContainsReadableElement) {
  ElementType expected_result = ElementType::READABLE;

  ElementType tested_element = ElementType::GROUP;

  EXPECT_EQ(expected_result, tested_element)
      << "expected: " << expected_result << endl
      << "provided: " << tested_element << endl;
}