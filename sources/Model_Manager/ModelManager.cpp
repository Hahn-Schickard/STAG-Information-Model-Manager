#include "ModelManager.hpp"
#include "Notifier_Event.hpp"

using namespace std;
using namespace Model_Manager;
using namespace Model_Event_Handler;

void ModelManager::registerDevice(
    std::unique_ptr<Information_Model::Device> device) {
  pair<string, Information_Model::Device *> device_pair(
      device->getElementRefId(),
      device.get()); //@TODO: check if ths causes problems
  devices.insert(device_pair);
  NotifierEvent *event =
      new NotifierEvent(NotifierEventType::NEW_DEVICE_REGISTERED, device.get());
  notifyListeners(event);
}
