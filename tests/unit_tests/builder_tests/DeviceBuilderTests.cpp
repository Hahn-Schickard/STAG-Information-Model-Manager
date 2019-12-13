#include "Device.hpp"
#include "DeviceBuilder.hpp"

#include "gtest/gtest.h"
#include <string>

using namespace std;
using namespace Model_Factory;
using namespace Information_Model;

TEST(DeviceBuilder, Create_NameRefIdAndDescription_ReturnsCorrectElementName) {
  // Act
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  // Assert
  ASSERT_EQ("TestDevice", device->getElementName());
}

TEST(DeviceBuilder, Create_NameRefIdAndDescription_ReturnsCorrectElementRefId) {
  // Arrange

  // Act
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  // Assert
  ASSERT_EQ("123", device->getElementRefId());
}

TEST(DeviceBuilder,
    Create_NameRefIdAndDescription_ReturnsCorrectElementDescription) {
  // Arrange

  // Act
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  // Assert

  ASSERT_EQ("A device for testing only", device->getElementDescription());
}

TEST(DeviceBuilder, AddDeviceElementGroup_ReturnsCorrectGroupName) {
  // Arrange

  // Act
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;
  auto group = device->getDeviceElementGroup();

  // Assert
  ASSERT_EQ("Root Group TestDevice", group->getElementName());
}

TEST(DeviceBuilder, AddDeviceElementGroup_ReturnsCorrectGroupDescription) {
  // Arrange

  // Act
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;
  auto group = device->getDeviceElementGroup();

  // Assert
  ASSERT_EQ("This is a Root Group Element", group->getElementDescription());
}

TEST(DeviceBuilder, AddDeviceElementGroup_ReturnsCorrectGroupRefId) {
  // Arrange

  // Act
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;
  auto group = device->getDeviceElementGroup();

  // Assert
  ASSERT_EQ("123:", group->getElementRefId());
}

TEST(DeviceBuilder, AddSubGroup_ReturnsCorrectGroupRefId) {
  // Arrange
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  builder->addDeviceElement("Subgroup1", "A Subgroup", ElementType::GROUP);

  // Assert
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto group = device->getDeviceElementGroup();

  auto subelements = group->getSubelements();

  shared_ptr<DeviceElementGroup> subgroup;

  // NOLINTNEXTLINE
  for(auto elelement : subelements) {
    if(elelement->getElementType() == ElementType::GROUP) {
      subgroup = static_pointer_cast<DeviceElementGroup>(elelement);
    }
  }

  ASSERT_EQ(1, subelements.size());
  ASSERT_NE(nullptr, subgroup);
  ASSERT_EQ("123:0", subgroup->getElementRefId());
}

TEST(DeviceBuilder, AaddDeviceElement_GROUP_CorrectGroupRefId) {
  // Arrange
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  builder->addDeviceElement("Subgroup1", "A Subgroup", ElementType::GROUP);

  // Assert
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;
  auto group       = device->getDeviceElementGroup();
  auto subelements = group->getSubelements();

  shared_ptr<DeviceElementGroup> subgroup;

  // NOLINTNEXTLINE
  for(auto elelement : subelements) {
    if(elelement->getElementType() == ElementType::GROUP) {
      subgroup = static_pointer_cast<DeviceElementGroup>(elelement);
    }
  }

  ASSERT_EQ(1, subelements.size());
  ASSERT_NE(nullptr, subgroup);
  // Assert
  ASSERT_EQ("123:0", subgroup->getElementRefId());
}

TEST(DeviceBuilder, AddDeviceElement_GROUP_ElementTypeIsGroup) {
  // Arrange
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  auto ref_id = builder->addDeviceElement(
      "Subgroup1", "A Subgroup", ElementType::GROUP);

  // Assert
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;
  auto group = device->getDeviceElementGroup();
  ASSERT_EQ(ElementType::GROUP, group->getElementType());

  auto subelements = group->getSubelements();
  ASSERT_EQ(1, subelements.size());

  auto subgroup = subelements[0];
  EXPECT_EQ(ElementType::GROUP, subgroup->getElementType());
}

TEST(DeviceBuilder,
    AddDeviceElement_SubgroupRefId_Observable_ReturnsCorrectMetricRefId) {
  // Arrange
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");
  builder->addDeviceElement(
      "BaseGroup", "This is BaseGroup", ElementType::GROUP);

  auto subgroup_ref_id = builder->addDeviceElement(
      "Subgroup1", "A Subgroup", ElementType::GROUP);

  // Act
  auto metric_ref_id = builder->addDeviceElement(subgroup_ref_id,
      "Metric2",
      "An observable Metric added to a subgroup",
      ElementType::OBSERVABLE);

  // Assert
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto actual_ref_id = static_pointer_cast<DeviceElementGroup>(
      device->getDeviceElementGroup()->getSubelements()[0])
                           ->getSubelements()[0]
                           ->getElementRefId();
  EXPECT_EQ("123:1.0", actual_ref_id);
}

TEST(DeviceBuilder, Adding_Metric_To_Two_Subgroups_ReturnsCorrectRefIds) {
  // Arrange
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");
  // Act
  auto subgroup_ref_id = builder->addDeviceElement(
      "Subgroup1", "A Subgroup", ElementType::GROUP);
  auto added_observable_ref_id = builder->addDeviceElement(subgroup_ref_id,
      "Observable Metric",
      "An observable Metric added to a subgroup",
      ElementType::OBSERVABLE);
  EXPECT_EQ("123:0.0", added_observable_ref_id);

  auto another_subgroup_ref_id = builder->addDeviceElement(
      "Subgroup2", "Another Subgroup", ElementType::GROUP);
  auto added_writable_ref_id
      = builder->addDeviceElement(another_subgroup_ref_id,
          "Writable Metric",
          "An writable Metric added to a subgroup",
          ElementType::WRITABLE);
  EXPECT_EQ("123:1.0", added_writable_ref_id);

  // Assert
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto observable_ref_id = device->getDeviceElementGroup()
                               ->getSubelement("123:0.0")
                               ->getElementRefId();
  auto writeable_ref_id = device->getDeviceElementGroup()
                              ->getSubelement("123:1.0")
                              ->getElementRefId();
  EXPECT_EQ("123:0.0", observable_ref_id);
  EXPECT_EQ("123:1.0", writeable_ref_id);
}

TEST(DeviceBuilder, Adding_Two_Metrics_To_One_Subgroup_ReturnsCorrectRefIds) {
  // Arrange
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  auto subgroup_ref_id = builder->addDeviceElement(
      "Subgroup1", "A Subgroup", ElementType::GROUP);
  builder->addDeviceElement(subgroup_ref_id,
      "Observable Metric",
      "An observable Metric added to a subgroup",
      ElementType::OBSERVABLE);
  builder->addDeviceElement(subgroup_ref_id,
      "Writable Metric",
      "An writable Metric added to a subgroup",
      ElementType::WRITABLE);

  auto another_subgroup_ref_id = builder->addDeviceElement(
      "Subgroup2", "Another Subgroup", ElementType::GROUP);
  builder->addDeviceElement(another_subgroup_ref_id,
      "Observable Metric",
      "An observable Metric added to a subgroup",
      ElementType::OBSERVABLE);
  builder->addDeviceElement(another_subgroup_ref_id,
      "Writable Metric",
      "An writable Metric added to a subgroup",
      ElementType::WRITABLE);

  // Assert
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto observable_ref_id1 = device->getDeviceElementGroup()
                                ->getSubelement("123:0.0")
                                ->getElementRefId();
  auto writeable_ref_id1 = device->getDeviceElementGroup()
                               ->getSubelement("123:0.1")
                               ->getElementRefId();
  auto observable_ref_id2 = device->getDeviceElementGroup()
                                ->getSubelement("123:1.0")
                                ->getElementRefId();
  auto writeable_ref_id2 = device->getDeviceElementGroup()
                               ->getSubelement("123:1.1")
                               ->getElementRefId();

  EXPECT_EQ("123:0.0", observable_ref_id1);
  EXPECT_EQ("123:0.1", writeable_ref_id1);
  EXPECT_EQ("123:1.0", observable_ref_id2);
  EXPECT_EQ("123:1.1", writeable_ref_id2);
}

TEST(DeviceBuilder,
    Adding_Two_Metrics_And_One_Group_To_One_Subgroup_ReturnsCorrectRefIds) {
  // Arrange
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  auto subgroup_ref_id = builder->addDeviceElement(
      "Subgroup1", "A Subgroup", ElementType::GROUP);
  builder->addDeviceElement(subgroup_ref_id,
      "Observable Metric 1",
      "An observable Metric added to a subgroup",
      ElementType::OBSERVABLE);
  builder->addDeviceElement(subgroup_ref_id,
      "Writable Metric 1",
      "An writable Metric added to a subgroup",
      ElementType::WRITABLE);
  builder->addDeviceElement(subgroup_ref_id,
      "Subgroup1a",
      "A subgroup withing a subgroup",
      ElementType::GROUP);

  auto another_subgroup_ref_id = builder->addDeviceElement(
      "Subgroup2", "Another Subgroup", ElementType::GROUP);
  builder->addDeviceElement(another_subgroup_ref_id,
      "Observable Metric 2",
      "An observable Metric added to a subgroup",
      ElementType::OBSERVABLE);
  builder->addDeviceElement(another_subgroup_ref_id,
      "Writable Metric 2",
      "An writable Metric added to a subgroup",
      ElementType::WRITABLE);
  builder->addDeviceElement(another_subgroup_ref_id,
      "Subgroup2a",
      "A subgroup withing a subgroup",
      ElementType::GROUP);

  // Assert
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto observable_ref_id1 = device->getDeviceElementGroup()
                                ->getSubelement("123:0.0")
                                ->getElementRefId();
  auto writeable_ref_id1 = device->getDeviceElementGroup()
                               ->getSubelement("123:0.1")
                               ->getElementRefId();
  auto subgroup_ref_id1 = device->getDeviceElementGroup()
                              ->getSubelement("123:0.2")
                              ->getElementRefId();
  auto observable_ref_id2 = device->getDeviceElementGroup()
                                ->getSubelement("123:1.0")
                                ->getElementRefId();
  auto writeable_ref_id2 = device->getDeviceElementGroup()
                               ->getSubelement("123:1.1")
                               ->getElementRefId();
  auto subgroup_ref_id2 = device->getDeviceElementGroup()
                              ->getSubelement("123:1.2")
                              ->getElementRefId();

  EXPECT_EQ("123:0.0", observable_ref_id1);
  EXPECT_EQ("123:0.1", writeable_ref_id1);
  EXPECT_EQ("123:0.2", subgroup_ref_id1);
  EXPECT_EQ("123:1.0", observable_ref_id2);
  EXPECT_EQ("123:1.1", writeable_ref_id2);
  EXPECT_EQ("123:1.2", subgroup_ref_id2);
}

TEST(DeviceBuilder,
    Adding_Two_Metrics_And_One_Group_To_One_Subgroup_ReturnsCorrectNames) {
  // Arrange
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");

  // Act
  auto subgroup_ref_id = builder->addDeviceElement(
      "Subgroup1", "A Subgroup", ElementType::GROUP);
  builder->addDeviceElement(subgroup_ref_id,
      "Observable Metric 1",
      "An observable Metric added to a subgroup",
      ElementType::OBSERVABLE);
  builder->addDeviceElement(subgroup_ref_id,
      "Writable Metric 1",
      "An writable Metric added to a subgroup",
      ElementType::WRITABLE);
  builder->addDeviceElement(subgroup_ref_id,
      "Subgroup1a",
      "A subgroup withing a subgroup",
      ElementType::GROUP);

  auto another_subgroup_ref_id = builder->addDeviceElement(
      "Subgroup2", "Another Subgroup", ElementType::GROUP);
  builder->addDeviceElement(another_subgroup_ref_id,
      "Observable Metric 2",
      "An observable Metric added to a subgroup",
      ElementType::OBSERVABLE);
  builder->addDeviceElement(another_subgroup_ref_id,
      "Writable Metric 2",
      "An writable Metric added to a subgroup",
      ElementType::WRITABLE);
  builder->addDeviceElement(another_subgroup_ref_id,
      "Subgroup2a",
      "A subgroup withing a subgroup",
      ElementType::GROUP);

  // Assert
  shared_ptr<Information_Model::Device> device = builder->getDevice();
  delete builder;

  auto observable_ref_id1 = device->getDeviceElementGroup()
                                ->getSubelement("123:0.0")
                                ->getElementName();
  auto writeable_ref_id1 = device->getDeviceElementGroup()
                               ->getSubelement("123:0.1")
                               ->getElementName();
  auto subgroup_ref_id1 = device->getDeviceElementGroup()
                              ->getSubelement("123:0.2")
                              ->getElementName();
  auto observable_ref_id2 = device->getDeviceElementGroup()
                                ->getSubelement("123:1.0")
                                ->getElementName();
  auto writeable_ref_id2 = device->getDeviceElementGroup()
                               ->getSubelement("123:1.1")
                               ->getElementName();
  auto subgroup_ref_id2 = device->getDeviceElementGroup()
                              ->getSubelement("123:1.2")
                              ->getElementName();

  EXPECT_EQ("TestDevice", device->getElementName());
  EXPECT_EQ("Root Group TestDevice",
      device->getDeviceElementGroup()->getElementName());
  EXPECT_EQ("Subgroup1",
      device->getDeviceElementGroup()
          ->getSubelement(subgroup_ref_id)
          ->getElementName());
  EXPECT_EQ("Observable Metric 1", observable_ref_id1);
  EXPECT_EQ("Writable Metric 1", writeable_ref_id1);
  EXPECT_EQ("Subgroup1a", subgroup_ref_id1);

  EXPECT_EQ("Subgroup2",
      device->getDeviceElementGroup()
          ->getSubelement(another_subgroup_ref_id)
          ->getElementName());
  EXPECT_EQ("Observable Metric 2", observable_ref_id2);
  EXPECT_EQ("Writable Metric 2", writeable_ref_id2);
  EXPECT_EQ("Subgroup2a", subgroup_ref_id2);
}

TEST(DeviceBuilder, CallingRecursiveSubgroupReturnsCorrectRefID) {
  // Arrange
  auto builder
      = new DeviceBuilder("TestDevice", "123", "A device for testing only");
  builder->addDeviceElement(
      "BaseGroup", "This is BaseGroup", ElementType::GROUP);
  string first_level_ref_id = builder->addDeviceElement(
      "FirstSubGroup", "First Level Subgroup", ElementType::GROUP);
  string second_level_ref_id = builder->addDeviceElement(first_level_ref_id,
      "SecondSubGroup",
      "Second Level Subgroup",
      ElementType::GROUP);
  string second_level_item_ref_id
      = builder->addDeviceElement(second_level_ref_id,
          "second_level_item_ref_id",
          "Item within Second Level Subgroup",
          ElementType::OBSERVABLE);

  auto device = builder->getDevice();

  // Act
  auto group = device->getDeviceElementGroup()->getSubelements();

  // NOLINTNEXTLINE
  for(auto firstelement : group) {
    if(firstelement->getElementType() == ElementType::GROUP) {
      auto subgroup = static_pointer_cast<DeviceElementGroup>(firstelement);
      // NOLINTNEXTLINE
      for(auto secondelement : subgroup->getSubelements()) {
	auto second_level_subgroup
	    = static_pointer_cast<DeviceElementGroup>(secondelement);
	// NOLINTNEXTLINE
	for(auto thirdelement : second_level_subgroup->getSubelements()) {
	  EXPECT_EQ(second_level_item_ref_id, thirdelement->getElementRefId());
	}
      }
    }
  }
}
