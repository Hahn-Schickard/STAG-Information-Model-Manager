#include "DeviceBuilder.hpp"
#include "DeviceElementBuilder.hpp"
#include "InformationModelExceptions.hpp"
#include <iostream>

using namespace std;
using namespace Model_Factory;
using namespace Information_Model;

DeviceBuilder::DeviceBuilder(const std::string NAME, const std::string REF_ID,
                             const std::string DESC) {
  auto device_ptr = new DeviceImpl(REF_ID, NAME, DESC);

  device_ptr->addDeviceElementGroup(
      "Root Group " + NAME, "This is a Root Group Element"); // bearbeitet
  // device = unique_ptr<Device>(dynamic_cast<Device *>(device_ptr));//
  // bearbeitet
  device = shared_ptr<Device>(dynamic_cast<Device *>(device_ptr));
}

string DeviceBuilder::addDeviceElement(const std::string NAME,
                                       const std::string DESC,
                                       ElementType type) {
  auto device_element_group = static_pointer_cast<DeviceElementGroupImpl>(
      device->getDeviceElementGroup());
  const string REF_ID =
      device_element_group->addDeviceElement(NAME, DESC, type);
  return REF_ID;
}

string DeviceBuilder::addDeviceElement(const std::string GROUP_REFID,
                                       const std::string NAME,
                                       const std::string DESC,
                                       ElementType type) {
  auto device_element_group = getDeviceElementGroup();
  auto refId = device_element_group->getElementRefId();

  // string refId = nullptr;
  if (device_element_group == nullptr) {
    return nullptr;
  }

  if (device_element_group->getElementRefId() != GROUP_REFID) {
    refId = addDeviceElementToSubgroup(device_element_group, GROUP_REFID, NAME,
                                       DESC, type);
  } else {
    refId = device_element_group->addDeviceElement(NAME, DESC, type);
  }

  return refId;
}

std::shared_ptr<DeviceElementGroupImpl> DeviceBuilder::getDeviceElementGroup() {
  auto group = static_pointer_cast<DeviceElementGroupImpl>(
      device->getDeviceElementGroup());

  // shared_ptr<DeviceElementGroupImpl> device_element_group(group);
  return group;
}

string DeviceBuilder::addDeviceElementToSubgroup(
    std::shared_ptr<DeviceElementGroupImpl> parentGroup,
    const string GROUP_REFID, const string NAME, const string DESC,
    ElementType type) {
  auto subelementGroup = getSubelementGroup(parentGroup, GROUP_REFID);
  if (subelementGroup == nullptr) {
    subelementGroup = findElementGroup(GROUP_REFID, parentGroup);
  }
  if (subelementGroup != nullptr) {

    auto elementRefId = subelementGroup->addDeviceElement(NAME, DESC, type);
    return elementRefId;
  }

  return nullptr;
}

std::shared_ptr<DeviceElementGroupImpl> DeviceBuilder::getSubelementGroup(
    std::shared_ptr<DeviceElementGroupImpl> deviceElementGroup, string REFID) {
  std::shared_ptr<Information_Model::DeviceElement> el =
      deviceElementGroup->getSubelement(REFID);
  if (el.get() != nullptr && el.get()->getElementRefId() == REFID) {
    if (el->getElementType() == ElementType::Group) {
      auto elementGroup = static_pointer_cast<DeviceElementGroupImpl>(el);
      return elementGroup;
    }
  }
  return nullptr;
}

std::shared_ptr<DeviceElementGroupImpl> DeviceBuilder::findElementGroup(
    string RefId,
    std::shared_ptr<Model_Factory::DeviceElementGroupImpl> deviceElementGroup) {
  auto subElements = deviceElementGroup->getSubelements();

  for (auto element : subElements) {
    if ((element->getElementType() == ElementType::Group) &&
        (element->getElementRefId() == RefId)) {
      return static_pointer_cast<DeviceElementGroupImpl>(element);
    }
  }
  return nullptr;
}

/*unique_ptr<Information_Model::Device> DeviceBuilder::getDevice() {
  return move(device);
}*/

shared_ptr<Information_Model::Device> DeviceBuilder::getDevice() {
  return move(device);
}