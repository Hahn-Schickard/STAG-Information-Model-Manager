#include "ModelManager.hpp"
#include "Notifier_Event.hpp"

using namespace std;
using namespace Model_Manager;
using namespace Information_Model;
using namespace Model_Event_Handler;

ModelManager::ModelManager() {}
ModelManager::~ModelManager() { devices.clear(); }

bool ModelManager::registerDevice(shared_ptr<Device> device) {
  if (!deviceExists(device->getElementRefId())) {
    pair<string, shared_ptr<Device>> device_pair(device->getElementRefId(),
                                                 device);
    devices.insert(device_pair);
    NotifierEvent *event =
        new NotifierEvent(NotifierEventType::NEW_DEVICE_REGISTERED, device);
    notifyListeners(event);
    return true;
  } else {
    return false;
  }
}

bool ModelManager::deregisterDevice(const string &DEVICE_ID) {
  if (deviceExists(DEVICE_ID)) {
    NotifierEvent *event =
        new NotifierEvent(NotifierEventType::DEVICE_REMOVED, DEVICE_ID);
    notifyListeners(event);
    devices.erase(DEVICE_ID);
    return true;
  } else {
    return false;
  }
}

bool ModelManager::deviceExists(const string &DEVICE_ID) {
  if (devices.find(DEVICE_ID) == devices.end()) {
    return false;
  } else {
    return true;
  }
}

ModelManager *ModelManager::getInstance() {
  if (!instance_) {
    instance_ = new ModelManager();
  }
  return instance_;
}

ModelManager *ModelManager::instance_ = 0;