#include "Device.hpp"
#include "DeviceBuilder.hpp"
#include "InformationModelExceptions.hpp"
//#include "MakeUnique.hpp" //bearbeitet
#include "gtest/gtest.h"
#include <string>

using namespace std;
using namespace Model_Factory;
using namespace Information_Model;

TEST(DeviceBuilder, Create_NameRefIdAndDescription_ReturnsCorrectElementName) {
  // Arrange

  // Act
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // //bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  // Assert
  ASSERT_EQ("TestDevice", device->getElementName());
}

TEST(DeviceBuilder, Create_NameRefIdAndDescription_ReturnsCorrectElementRefId) {
  // Arrange

  // Act
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // //bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  // Assert
  ASSERT_EQ("123", device->getElementRefId());
}

TEST(DeviceBuilder,
     Create_NameRefIdAndDescription_ReturnsCorrectElementDescription) {
  // Arrange

  // Act
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  // Assert

  ASSERT_EQ("A device for testing only", device->getElementDescription());
}

TEST(DeviceBuilder, AddDeviceElementGroup_ReturnsCorrectGroupName) {
  // Arrange

  // Act
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;
  auto group = device->getDeviceElementGroup();

  // Assert
  ASSERT_EQ("Root Group TestDevice", group->getElementName());
}

TEST(DeviceBuilder, AddDeviceElementGroup_ReturnsCorrectGroupDescription) {
  // Arrange

  // Act
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;
  auto group = device->getDeviceElementGroup();

  // Assert
  ASSERT_EQ("This is a Root Group Element", group->getElementDescription());
}

TEST(DeviceBuilder, AddDeviceElementGroup_ReturnsCorrectGroupRefId) {
  // Arrange

  // Act
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;
  auto group = device->getDeviceElementGroup();

  // Assert
  ASSERT_EQ("123:", group->getElementRefId());
}

TEST(DeviceBuilder, AddSubGroup_ReturnsCorrectGroupRefId) {
  // Arrange
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  builder->addDeviceElement("Subgroup1", "A Subgroup", ElementType::Group);

  // Assert
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto group = device->getDeviceElementGroup();

  auto subElements = group->getSubelements();

  std::shared_ptr<DeviceElementGroup> subgroup;

  for (auto el : subElements) {
    if (el->getElementType() == ElementType::Group) {
      subgroup = static_pointer_cast<DeviceElementGroup>(el);
    }
  }

  ASSERT_EQ(1, subElements.size());
  ASSERT_NE(nullptr, subgroup);
  ASSERT_EQ("123:0", subgroup->getElementRefId());
}

TEST(DeviceBuilder, AaddDeviceElement_GROUP_CorrectGroupRefId) {
  // Arrange
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  builder->addDeviceElement("Subgroup1", "A Subgroup", ElementType::Group);

  // Assert
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;
  auto group = device->getDeviceElementGroup();
  auto subElements = group->getSubelements();

  std::shared_ptr<DeviceElementGroup> subgroup;

  for (auto el : subElements) {
    if (el->getElementType() == ElementType::Group) {
      subgroup = static_pointer_cast<DeviceElementGroup>(el);
    }
  }

  ASSERT_EQ(1, subElements.size());
  ASSERT_NE(nullptr, subgroup);
  // Assert
  ASSERT_EQ("123:0", subgroup->getElementRefId());
}

TEST(DeviceBuilder, AddDeviceElement_GROUP_ElementTypeIsGroup) {
  // Arrange
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  auto refId =
      builder->addDeviceElement("Subgroup1", "A Subgroup", ElementType::Group);

  // Assert
  // std::unique_ptr<Information_Model::Device> aDevice = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> aDevice = builder->getDevice();
  delete builder;
  auto aGroup = aDevice->getDeviceElementGroup();
  ASSERT_EQ(ElementType::Group, aGroup->getElementType());

  auto aSubelements = aGroup->getSubelements();
  ASSERT_EQ(1, aSubelements.size());

  auto aSubgroup = aSubelements[0];
  EXPECT_EQ(ElementType::Group, aSubgroup->getElementType());
}

TEST(DeviceBuilder,
     AddDeviceElement_SubgroupRefId_Observable_ReturnsCorrectMetricRefId) {
  // Arrange
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");
  builder->addDeviceElement("BaseGroup", "This is BaseGroup",
                            ElementType::Group);

  auto subgroupRefId =
      builder->addDeviceElement("Subgroup1", "A Subgroup", ElementType::Group);

  // Act
  auto metricRefId = builder->addDeviceElement(
      subgroupRefId, "Metric2", "An observable Metric added to a subgroup",
      ElementType::Observable);

  // Assert
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto actualRefId = static_pointer_cast<DeviceElementGroup>(
                         device->getDeviceElementGroup()->getSubelements()[0])
                         ->getSubelements()[0]
                         ->getElementRefId();
  EXPECT_EQ("123:1.0", actualRefId);
}

TEST(DeviceBuilder, Adding_Metric_To_Two_Subgroups_ReturnsCorrectRefIds) {
  // Arrange
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");
  // builder->addDeviceElement("BaseGroup", "This is BaseGroup",
  //                          ElementType::Group);
  // Act
  auto subgroupRefId =
      builder->addDeviceElement("Subgroup1", "A Subgroup", ElementType::Group);
  auto addedObservableRefId = builder->addDeviceElement(
      subgroupRefId, "Observable Metric",
      "An observable Metric added to a subgroup", ElementType::Observable);
  EXPECT_EQ("123:0.0", addedObservableRefId);

  auto anotherSubgroupRefId = builder->addDeviceElement(
      "Subgroup2", "Another Subgroup", ElementType::Group);
  auto addedWritableRefId = builder->addDeviceElement(
      anotherSubgroupRefId, "Writable Metric",
      "An writable Metric added to a subgroup", ElementType::Writable);
  EXPECT_EQ("123:1.0", addedWritableRefId);

  // Assert
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto observableRefId = device->getDeviceElementGroup()
                             ->getSubelement("123:0.0")
                             ->getElementRefId();
  auto writeableRefId = device->getDeviceElementGroup()
                            ->getSubelement("123:1.0")
                            ->getElementRefId();
  EXPECT_EQ("123:0.0", observableRefId);
  EXPECT_EQ("123:1.0", writeableRefId);
}

TEST(DeviceBuilder, Adding_Two_Metrics_To_One_Subgroup_ReturnsCorrectRefIds) {
  // Arrange
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  auto subgroupRefId =
      builder->addDeviceElement("Subgroup1", "A Subgroup", ElementType::Group);
  builder->addDeviceElement(subgroupRefId, "Observable Metric",
                            "An observable Metric added to a subgroup",
                            ElementType::Observable);
  builder->addDeviceElement(subgroupRefId, "Writable Metric",
                            "An writable Metric added to a subgroup",
                            ElementType::Writable);

  auto anotherSubgroupRefId = builder->addDeviceElement(
      "Subgroup2", "Another Subgroup", ElementType::Group);
  builder->addDeviceElement(anotherSubgroupRefId, "Observable Metric",
                            "An observable Metric added to a subgroup",
                            ElementType::Observable);
  builder->addDeviceElement(anotherSubgroupRefId, "Writable Metric",
                            "An writable Metric added to a subgroup",
                            ElementType::Writable);

  // Assert
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto observableRefId1 = device->getDeviceElementGroup()
                              ->getSubelement("123:0.0")
                              ->getElementRefId();
  auto writeableRefId1 = device->getDeviceElementGroup()
                             ->getSubelement("123:0.1")
                             ->getElementRefId();
  auto observableRefId2 = device->getDeviceElementGroup()
                              ->getSubelement("123:1.0")
                              ->getElementRefId();
  auto writeableRefId2 = device->getDeviceElementGroup()
                             ->getSubelement("123:1.1")
                             ->getElementRefId();

  EXPECT_EQ("123:0.0", observableRefId1);
  EXPECT_EQ("123:0.1", writeableRefId1);
  EXPECT_EQ("123:1.0", observableRefId2);
  EXPECT_EQ("123:1.1", writeableRefId2);
}

TEST(DeviceBuilder,
     Adding_Two_Metrics_And_One_Group_To_One_Subgroup_ReturnsCorrectRefIds) {
  // Arrange
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  auto subgroupRefId =
      builder->addDeviceElement("Subgroup1", "A Subgroup", ElementType::Group);
  builder->addDeviceElement(subgroupRefId, "Observable Metric 1",
                            "An observable Metric added to a subgroup",
                            ElementType::Observable);
  builder->addDeviceElement(subgroupRefId, "Writable Metric 1",
                            "An writable Metric added to a subgroup",
                            ElementType::Writable);
  builder->addDeviceElement(subgroupRefId, "Subgroup1a",
                            "A subgroup withing a subgroup",
                            ElementType::Group);

  auto anotherSubgroupRefId = builder->addDeviceElement(
      "Subgroup2", "Another Subgroup", ElementType::Group);
  builder->addDeviceElement(anotherSubgroupRefId, "Observable Metric 2",
                            "An observable Metric added to a subgroup",
                            ElementType::Observable);
  builder->addDeviceElement(anotherSubgroupRefId, "Writable Metric 2",
                            "An writable Metric added to a subgroup",
                            ElementType::Writable);
  builder->addDeviceElement(anotherSubgroupRefId, "Subgroup2a",
                            "A subgroup withing a subgroup",
                            ElementType::Group);

  // Assert
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto observableRefId1 = device->getDeviceElementGroup()
                              ->getSubelement("123:0.0")
                              ->getElementRefId();
  auto writeableRefId1 = device->getDeviceElementGroup()
                             ->getSubelement("123:0.1")
                             ->getElementRefId();
  auto subgroupRefId1 = device->getDeviceElementGroup()
                            ->getSubelement("123:0.2")
                            ->getElementRefId();
  auto observableRefId2 = device->getDeviceElementGroup()
                              ->getSubelement("123:1.0")
                              ->getElementRefId();
  auto writeableRefId2 = device->getDeviceElementGroup()
                             ->getSubelement("123:1.1")
                             ->getElementRefId();
  auto subgroupRefId2 = device->getDeviceElementGroup()
                            ->getSubelement("123:1.2")
                            ->getElementRefId();

  EXPECT_EQ("123:0.0", observableRefId1);
  EXPECT_EQ("123:0.1", writeableRefId1);
  EXPECT_EQ("123:0.2", subgroupRefId1);
  EXPECT_EQ("123:1.0", observableRefId2);
  EXPECT_EQ("123:1.1", writeableRefId2);
  EXPECT_EQ("123:1.2", subgroupRefId2);
}

TEST(DeviceBuilder,
     Adding_Two_Metrics_And_One_Group_To_One_Subgroup_ReturnsCorrectNames) {
  // Arrange
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  auto subgroupRefId =
      builder->addDeviceElement("Subgroup1", "A Subgroup", ElementType::Group);
  builder->addDeviceElement(subgroupRefId, "Observable Metric 1",
                            "An observable Metric added to a subgroup",
                            ElementType::Observable);
  builder->addDeviceElement(subgroupRefId, "Writable Metric 1",
                            "An writable Metric added to a subgroup",
                            ElementType::Writable);
  builder->addDeviceElement(subgroupRefId, "Subgroup1a",
                            "A subgroup withing a subgroup",
                            ElementType::Group);

  auto anotherSubgroupRefId = builder->addDeviceElement(
      "Subgroup2", "Another Subgroup", ElementType::Group);
  builder->addDeviceElement(anotherSubgroupRefId, "Observable Metric 2",
                            "An observable Metric added to a subgroup",
                            ElementType::Observable);
  builder->addDeviceElement(anotherSubgroupRefId, "Writable Metric 2",
                            "An writable Metric added to a subgroup",
                            ElementType::Writable);
  builder->addDeviceElement(anotherSubgroupRefId, "Subgroup2a",
                            "A subgroup withing a subgroup",
                            ElementType::Group);

  // Assert
  // std::unique_ptr<Information_Model::Device> device = builder->getDevice();
  // // bearbeitet
  std::shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto observableRefId1 = device->getDeviceElementGroup()
                              ->getSubelement("123:0.0")
                              ->getElementName();
  auto writeableRefId1 = device->getDeviceElementGroup()
                             ->getSubelement("123:0.1")
                             ->getElementName();
  auto subgroupRefId1 = device->getDeviceElementGroup()
                            ->getSubelement("123:0.2")
                            ->getElementName();
  auto observableRefId2 = device->getDeviceElementGroup()
                              ->getSubelement("123:1.0")
                              ->getElementName();
  auto writeableRefId2 = device->getDeviceElementGroup()
                             ->getSubelement("123:1.1")
                             ->getElementName();
  auto subgroupRefId2 = device->getDeviceElementGroup()
                            ->getSubelement("123:1.2")
                            ->getElementName();

  EXPECT_EQ("TestDevice", device->getElementName());
  EXPECT_EQ("Root Group TestDevice",
            device->getDeviceElementGroup()->getElementName());
  EXPECT_EQ("Subgroup1", device->getDeviceElementGroup()
                             ->getSubelement(subgroupRefId)
                             ->getElementName());
  EXPECT_EQ("Observable Metric 1", observableRefId1);
  EXPECT_EQ("Writable Metric 1", writeableRefId1);
  EXPECT_EQ("Subgroup1a", subgroupRefId1);

  EXPECT_EQ("Subgroup2", device->getDeviceElementGroup()
                             ->getSubelement(anotherSubgroupRefId)
                             ->getElementName());
  EXPECT_EQ("Observable Metric 2", observableRefId2);
  EXPECT_EQ("Writable Metric 2", writeableRefId2);
  EXPECT_EQ("Subgroup2a", subgroupRefId2);
}

TEST(DeviceBuilder, CallingRecursiveSubgroupReturnsCorrectRefID) {
  // Arrange
  auto builder =
      new DeviceBuilder("TestDevice", "123", "A device for testing only");
  builder->addDeviceElement("BaseGroup", "This is BaseGroup",
                            ElementType::Group);
  string FirstLevelREFID = builder->addDeviceElement(
      "FirstSubGroup", "First Level Subgroup", ElementType::Group);
  string SecondLevelREFID =
      builder->addDeviceElement(FirstLevelREFID, "SecondSubGroup",
                                "Second Level Subgroup", ElementType::Group);
  string SecondLevelItemREFID = builder->addDeviceElement(
      SecondLevelREFID, "SecondLevelItemREFID",
      "Item within Second Level Subgroup", ElementType::Observable);

  auto device = builder->getDevice();

  // Act
  auto group = device->getDeviceElementGroup()->getSubelements();

  for (auto firstelement : group) {
    if (firstelement->getElementType() == ElementType::Group) {
      auto subgroup = static_pointer_cast<DeviceElementGroup>(firstelement);
      for (auto secondelement : subgroup->getSubelements()) {
        auto SecondLevelSubgroup =
            static_pointer_cast<DeviceElementGroup>(secondelement);
        for (auto thirdelement : SecondLevelSubgroup->getSubelements()) {
          EXPECT_EQ(SecondLevelItemREFID, thirdelement->getElementRefId());
        }
      }
    }
  }
}
