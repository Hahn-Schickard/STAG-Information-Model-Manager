#include "ModelManager.hpp"
#include "Notifier_Event.hpp"

using namespace std;
using namespace Model_Manager;
using namespace Information_Model;
using namespace Model_Event_Handler;

/*bool ModelManager::registerDevice(std::unique_ptr<Device> device) {
  if (deviceExists(device->getElementRefId())) {
    pair<string, Device *> device_pair(
        device->getElementRefId(),
        device.get()); //@TODO: check if ths causes problems
    devices.insert(device_pair);
    NotifierEvent *event = new NotifierEvent(
        NotifierEventType::NEW_DEVICE_REGISTERED, device.get());
    notifyListeners(event);
    return true;
  } else {
    return false;
  }
}*/

bool ModelManager::registerDevice(std::shared_ptr<Device> device) {
  if (deviceExists(device->getElementRefId())) {
    pair<string, Device *> device_pair(
        device->getElementRefId(),
        device.get()); //@TODO: check if ths causes problems
    devices.insert(device_pair);
    NotifierEvent *event = new NotifierEvent(
        NotifierEventType::NEW_DEVICE_REGISTERED, device.get());
    notifyListeners(event);
    return true;
  } else {
    return false;
  }
}

bool ModelManager::deregisterDevice(const std::string &DEVICE_ID) {
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

bool ModelManager::deviceExists(const std::string &DEVICE_ID) {
  if (devices.find(DEVICE_ID) == devices.end()) {
    return false;
  } else {
    return true;
  }
}