#include "DeviceImplementation.hpp"

using namespace std;
using namespace Information_Model;
using namespace Infromation_Model_Manager;

DeviceImplementation::DeviceImplementation(const string &ref_id,
                                           const string &name,
                                           const string &desc)
    : Device(ref_id, name, desc) {
  base_group_ =
      make_shared<DeviceElementGroupImplementation>(ref_id + ":", name, desc);
};

shared_ptr<DeviceElementGroup> DeviceImplementation::getDeviceElementGroup() {
  return base_group_;
}

shared_ptr<DeviceElement>
DeviceImplementation::getDeviceElement(const string &ref_id) {
  // Check if a given element could exists in this device
  if (ref_id.find(getElementId()) != string::npos) {
    return base_group_->getSubelement(ref_id);
  } else {
    return shared_ptr<DeviceElement>();
  }
}