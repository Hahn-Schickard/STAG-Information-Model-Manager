#include "ModelRepository.hpp"
#include "HaSLL/LoggerManager.hpp"

#include <functional>

using namespace std;
using namespace Information_Model;
using namespace Data_Consumer_Adapter;
using namespace HaSLI;

namespace Information_Model_Manager {
ModelRepository::ModelRepository()
    : AsyncEventSource(
          bind(&ModelRepository::logException, this, placeholders::_1)),
      logger_(LoggerManager::registerTypedLogger(this)) {}

void ModelRepository::logException(const exception_ptr& ex_ptr) {
  try {
    if (ex_ptr) {
      rethrow_exception(ex_ptr);
    }
  } catch (exception& ex) {
    logger_->log(SeverityLevel::ERROR,
        "Received an exception while trying to notify listeners. Exception: {}",
        ex.what());
  }
}

bool ModelRepository::add(NonemptyDevicePtr device) {
  if (!deviceExists(device->getElementId())) {
    logger_->log(SeverityLevel::TRACE,
        "Registering device with id: {} within the Information Model",
        device->getElementId());
    pair<string, NonemptyDevicePtr> device_pair(device->getElementId(), device);
    devices_.insert(device_pair);
    notify(std::make_shared<ModelRepositoryEvent>(device));
    return true;
  } else {
    logger_->log(SeverityLevel::TRACE,
        "Device with id {} already exists!",
        device->getElementId());
    return false;
  }
}

bool ModelRepository::remove(const string& device_id) {
  if (deviceExists(device_id)) {
    logger_->log(SeverityLevel::TRACE,
        "Removing Device with id {} from the Information Model",
        device_id);
    notify(make_shared<ModelRepositoryEvent>(device_id));
    devices_.erase(device_id);
    return true;
  } else {
    logger_->log(
        SeverityLevel::TRACE, "Device with id {} does not exist!", device_id);
    return false;
  }
}

vector<NonemptyDevicePtr> ModelRepository::getModelSnapshot() {
  vector<NonemptyDevicePtr> result;
  for (auto& device : devices_) {
    result.push_back(device.second);
  }
  return result;
}

bool ModelRepository::deviceExists(const string& device_id) {
  if (devices_.find(device_id) == devices_.end()) {
    logger_->log(
        SeverityLevel::TRACE, "Device with id {} not found!", device_id);
    return false;
  } else {
    return true;
  }
}
} // namespace Information_Model_Manager