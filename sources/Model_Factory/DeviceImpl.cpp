#include "DeviceImpl.hpp"
#include "InformationModelExceptions.hpp"
#include <memory>

using namespace std;
using namespace Model_Factory;
using namespace Information_Model;

string DeviceImpl::addDeviceElementGroup(const string &NAME,
                                         const string &DESC) {
  const string REF_ID = this->getElementRefId() + ":";
  shared_ptr<DeviceElementGroupImpl> group_ptr(
      new DeviceElementGroupImpl(REF_ID, NAME, DESC));
  device_element_group =
      static_pointer_cast<Information_Model::DeviceElementGroup>(group_ptr);

  return REF_ID;
}

shared_ptr<Information_Model::DeviceElementGroup>
DeviceImpl::getDeviceElementGroup() {
  if (device_element_group.get() == nullptr)
    throw GroupElementDoesNotExistException("Device has no Element Group");
  return device_element_group;
}