#include "ModelManager.hpp"

using namespace std;
using namespace Model_Manager;

void ModelManager::registerDevice(
    std::unique_ptr<Information_Model::Device> device) {
  pair<string, Information_Model::Device *> device_pair(
      device->getElementRefId(),
      device.get()); //@TODO: check if ths causes problems
  devices.insert(device_pair);
  notifyListeners(device.get());
}
