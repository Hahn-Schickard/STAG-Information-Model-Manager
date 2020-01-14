#include "ModelManager.hpp"

#include "Notifier_Event.hpp"

using namespace std;
using namespace Model_Manager;
using namespace Information_Model;
using namespace Model_Event_Handler;

ModelManager::ModelManager() {}
ModelManager::~ModelManager() {
  devices.clear();
}

bool ModelManager::registerDevice(shared_ptr<Device> device) {
  if(!deviceExists(device->getElementRefId())) {
    pair<string, shared_ptr<Device>> device_pair(
        device->getElementRefId(), device);
    devices.insert(device_pair);
    notifyListeners(make_shared<NotifierEvent>(
        NotifierEventType::NEW_DEVICE_REGISTERED, device));
    return true;
  } else {
    return false;
  }
}

bool ModelManager::deregisterDevice(const string& device_id) {
  if(deviceExists(device_id)) {
    notifyListeners(make_shared<NotifierEvent>(
        NotifierEventType::DEVICE_REMOVED, device_id));
    devices.erase(device_id);
    return true;
  } else {
    return false;
  }
}

bool ModelManager::deviceExists(const string& device_id) {
  if(devices.find(device_id) == devices.end()) {
    return false;
  } else {
    return true;
  }
}

ModelManager* ModelManager::getInstance() {
  if(!instance_) {
    instance_ = new ModelManager();
  }
  return instance_;
}

// NOLINTNEXTLINE
ModelManager* ModelManager::instance_ = 0;