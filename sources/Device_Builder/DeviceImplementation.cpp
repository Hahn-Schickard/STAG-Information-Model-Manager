#include "DeviceImplementation.hpp"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
DeviceImplementation::DeviceImplementation(
    const string& ref_id, const string& name, const string& desc)
    : Device(ref_id, name, desc),
      base_group_(
          NonemptyPointer::make_shared<DeviceElementGroupImplementation>(
              ref_id + ":")) {}

NonemptyDeviceElementGroupPtr
DeviceImplementation::getDeviceElementGroup() const {
  return base_group_;
}

DeviceImplementation::DeviceGroupImplementation
DeviceImplementation::getGroupImplementation() {
  return base_group_;
}

NonemptyDeviceElementPtr DeviceImplementation::getDeviceElement(
    const string& ref_id) const {
  // Check if a given element could exists in this device
  if (ref_id.find(getElementId()) != string::npos) {
    return base_group_->getSubelement(ref_id);
  }
  throw DeviceElementNotFound(ref_id);
}
} // namespace Information_Model_Manager