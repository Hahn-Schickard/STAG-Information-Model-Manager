#include "DeviceBuilder.hpp"

#include "DeviceElementBuilder.hpp"
#include "LoggerRepository.hpp"

using namespace std;
using namespace HaSLL;
using namespace Model_Factory;
using namespace Information_Model;

DeviceBuilder::DeviceBuilder(const string& name,
    const string& ref_Id,
    const string& desc)
    : logger_(LoggerRepository::getInstance().registerTypedLoger(this)) {
  auto device_ptr = new DeviceImpl(ref_Id, name, desc);

  device_ptr->addDeviceElementGroup(
      "Root Group " + name, "This is a Root Group Element");
  device = shared_ptr<Device>(dynamic_cast<Device*>(device_ptr));
}

string DeviceBuilder::addDeviceElement(const string& name,
    const string& desc,
    ElementType type) {
  auto device_element_group = static_pointer_cast<DeviceElementGroupImpl>(
      device->getDeviceElementGroup());
  const string REF_ID
      = device_element_group->addDeviceElement(name, desc, type);
  return REF_ID;
}

string DeviceBuilder::addDeviceElement(const string& group_ref_id,
    const string& name,
    const string& desc,
    ElementType type) {
  auto device_element_group = getDeviceElementGroup();
  auto ref_id               = device_element_group->getElementRefId();

  if(device_element_group == nullptr) {
    return nullptr;
  }

  if(device_element_group->getElementRefId() != group_ref_id) {
    ref_id = addDeviceElementToSubgroup(
        device_element_group, group_ref_id, name, desc, type);
  } else {
    ref_id = device_element_group->addDeviceElement(name, desc, type);
  }

  return ref_id;
}

shared_ptr<DeviceElementGroupImpl> DeviceBuilder::getDeviceElementGroup() {
  auto group = static_pointer_cast<DeviceElementGroupImpl>(
      device->getDeviceElementGroup());

  return group;
}

string DeviceBuilder::addFunction(const string& name, const string& desc) {
  logger_->log(SeverityLevel::ERROR, "Function build is not implemented!");
  return nullptr;
}

//NOLINTNEXTLINE
string DeviceBuilder::addDeviceElementToSubgroup(
    shared_ptr<DeviceElementGroupImpl> parent_group,
    const string& group_ref_id,
    const string& name,
    const string& desc,
    ElementType type) {
  auto subelement_group = getSubelementGroup(parent_group, group_ref_id);
  if(subelement_group == nullptr) {
    subelement_group = findElementGroup(group_ref_id, parent_group);
  }
  if(subelement_group != nullptr) {
    auto element_ref_id = subelement_group->addDeviceElement(name, desc, type);
    return element_ref_id;
  }

  return nullptr;
}

//NOLINTNEXTLINE
shared_ptr<DeviceElementGroupImpl> DeviceBuilder::getSubelementGroup(
    shared_ptr<DeviceElementGroupImpl> device_element_group,
    const string& ref_id) {
  shared_ptr<Information_Model::DeviceElement> el
      = device_element_group->getSubelement(ref_id);
  if(el.get() != nullptr && el.get()->getElementRefId() == ref_id) {
    if(el->getElementType() == ElementType::GROUP) {
      auto element_group = static_pointer_cast<DeviceElementGroupImpl>(el);
      return element_group;
    }
  }
  return nullptr;
}

//NOLINTNEXTLINE
shared_ptr<DeviceElementGroupImpl> DeviceBuilder::findElementGroup(
    const string& ref_id,
    shared_ptr<Model_Factory::DeviceElementGroupImpl> device_element_group) {
  auto sub_elements = device_element_group->getSubelements();

  //NOLINTNEXTLINE
  for(auto element : sub_elements) {
    if((element->getElementType() == ElementType::GROUP)
        && (element->getElementRefId() == ref_id)) {
      return static_pointer_cast<DeviceElementGroupImpl>(element);
    }
  }
  return nullptr;
}

shared_ptr<Information_Model::Device> DeviceBuilder::getDevice() {
  return move(device);
}