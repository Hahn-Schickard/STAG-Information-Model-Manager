#include "BuildingAndRegirtrationFacade.hpp"

using namespace std;
using namespace Information_Access_Manager;
using namespace Model_Factory;
using namespace Model_Manager;
using namespace Information_Model;

BuildingAndRegirtrationFacade::BuildingAndRegirtrationFacade() {
  manager_ = make_shared<ModelManager>(ModelManager());
}

void BuildingAndRegirtrationFacade::buildDeviceBase(const string UNIQUE_ID,
                                                    const string NAME,
                                                    const string DESC) {
  builder_ = new DeviceBuilder(NAME, UNIQUE_ID, DESC);
}

string BuildingAndRegirtrationFacade::buildDeviceElement(const string NAME,
                                                         const string DESC,
                                                         ElementType type) {
  return builder_->addDeviceElement(NAME, DESC, type);
}

string BuildingAndRegirtrationFacade::buildDeviceElement(const string GROUP_ID,
                                                         const string NAME,
                                                         const string DESC,
                                                         ElementType type) {
  return builder_->addDeviceElement(GROUP_ID, NAME, DESC, type);
}

/*unique_ptr<Device> BuildingAndRegirtrationFacade::getDevice() {  //bearbeitet
  unique_ptr<Device> device = builder_->getDevice();
  delete builder_;
  return move(device);
}*/

shared_ptr<Device> BuildingAndRegirtrationFacade::getDevice() {
  shared_ptr<Device> device = builder_->getDevice();
  delete builder_;
  return move(device);
}

/*bool BuildingAndRegirtrationFacade::registerDevice(unique_ptr<Device> device)
//bearbeitet
{
  return manager_->registerDevice(move(device));
}*/
bool BuildingAndRegirtrationFacade::registerDevice(shared_ptr<Device> device) {
  return manager_->registerDevice(move(device));
}

bool BuildingAndRegirtrationFacade::deregisterDevice(const string DEVICE_ID) {
  return manager_->deregisterDevice(DEVICE_ID);
}