#include "BuildingAndRegirtrationFacade.hpp"

using namespace std;
using namespace Information_Access_Manager;
using namespace Model_Factory;
using namespace Model_Manager;
using namespace Information_Model;

BuildingAndRegirtrationFacade::BuildingAndRegirtrationFacade() {
  manager_ = manager_->getInstance();
}

void BuildingAndRegirtrationFacade::buildDeviceBase(const string& unique_Id,
    const string& name,
    const string& desc) {
  builder_ = new DeviceBuilder(name, unique_Id, desc);
}

string BuildingAndRegirtrationFacade::buildDeviceElement(const string& name,
    const string& desc,
    ElementType type) {
  return builder_->addDeviceElement(name, desc, type);
}

string BuildingAndRegirtrationFacade::buildDeviceElement(const string& group_Id,
    const string& name,
    const string& desc,
    ElementType type) {
  return builder_->addDeviceElement(group_Id, name, desc, type);
}

shared_ptr<Device> BuildingAndRegirtrationFacade::getDevice() {
  shared_ptr<Device> device = builder_->getDevice();
  delete builder_;
  return move(device);
}

bool BuildingAndRegirtrationFacade::registerDevice(shared_ptr<Device> device) {
  return manager_->registerDevice(move(device));
}

bool BuildingAndRegirtrationFacade::deregisterDevice(const string& device_id) {
  return manager_->deregisterDevice(device_id);
}