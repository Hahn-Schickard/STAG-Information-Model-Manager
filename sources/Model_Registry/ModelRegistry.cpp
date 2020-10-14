#include "ModelRegistry.hpp"

using namespace std;
using namespace Information_Model;
using namespace DCAI;

namespace Information_Model_Manager {
bool ModelRegistry::registerDevice(shared_ptr<Device> device) {
  if (!deviceExists(device->getElementId())) {
    pair<string, shared_ptr<Device>> device_pair(device->getElementId(),
                                                 device);
    devices_.insert(device_pair);
    notify(make_shared<ModelRegistryEvent>(device));
    return true;
  } else {
    return false;
  }
}

bool ModelRegistry::deregisterDevice(const string &device_id) {
  if (deviceExists(device_id)) {
    notify(make_shared<ModelRegistryEvent>(device_id));
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
} // namespace Information_Model_Manager