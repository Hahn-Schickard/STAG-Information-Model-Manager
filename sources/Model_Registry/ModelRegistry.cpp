#include "ModelRegistry.hpp"
#include "LoggerRepository.hpp"

#include <functional>

using namespace std;
using namespace Information_Model;
using namespace DCAI;
using namespace HaSLL;

namespace Information_Model_Manager {
ModelRegistry::ModelRegistry()
    : AsyncEventSource(
          bind(&ModelRegistry::logException, this, placeholders::_1)),
      logger_(LoggerRepository::getInstance().registerTypedLoger(this)) {}

ModelRegistry::~ModelRegistry() {
  logger_->flushMessages();
  LoggerRepository::getInstance().deregisterLoger(logger_->getName());
}

void ModelRegistry::logException(const std::exception &ex) {
  logger_->log(
      SeverityLevel::ERROR,
      "Received an exceptio nwhile trying to notify listeners. Exception: {}",
      ex.what());
}

bool ModelRegistry::registerDevice(shared_ptr<Device> device) {
  if (!deviceExists(device->getElementId())) {
    logger_->log(SeverityLevel::TRACE,
                 "Registering device with id: {} within the Information Model",
                 device->getElementId());
    pair<string, shared_ptr<Device>> device_pair(device->getElementId(),
                                                 device);
    devices_.insert(device_pair);
    notify(make_shared<ModelRegistryEvent>(device));
    return true;
  } else {
    logger_->log(SeverityLevel::TRACE, "Device with id {} already exists!",
                 device->getElementId());
    return false;
  }
}

bool ModelRegistry::deregisterDevice(const string &device_id) {
  if (deviceExists(device_id)) {
    logger_->log(SeverityLevel::TRACE,
                 "Removing Device with id {} from the Information Model",
                 device_id);
    notify(make_shared<ModelRegistryEvent>(device_id));
    devices_.erase(device_id);
    return true;
  } else {
    logger_->log(SeverityLevel::TRACE, "Device with id {} does not exist!",
                 device_id);
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