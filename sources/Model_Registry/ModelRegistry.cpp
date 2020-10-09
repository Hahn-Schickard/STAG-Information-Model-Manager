#include "ModelRegistry.hpp"

#include "Notifier_Event.hpp"

using namespace std;
using namespace Infromation_Model_Manager;
using namespace Information_Model;
using namespace Model_Event_Handler;

bool ModelRegistry::registerDevice(shared_ptr<Device> device) {
  if (!deviceExists(device->getElementId())) {
    pair<string, shared_ptr<Device>> device_pair(device->getElementId(),
                                                 device);
    devices_.insert(device_pair);
    notifyListeners(make_shared<NotifierEvent>(
        NotifierEventType::NEW_DEVICE_REGISTERED, device));
    return true;
  } else {
    return false;
  }
}

bool ModelRegistry::deregisterDevice(const string &device_id) {
  if (deviceExists(device_id)) {
    notifyListeners(make_shared<NotifierEvent>(
        NotifierEventType::DEVICE_REMOVED, device_id));
    devices_.erase(device_id);
    return true;
  } else {
    return false;
  }
}

bool ModelRegistry::deviceExists(const string &device_id) {
  if (devices_.find(device_id) == devices_.end()) {
    return false;
  } else {
    return true;
  }
}