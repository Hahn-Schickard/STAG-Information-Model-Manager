#include "ModelRepository.hpp"
#include <Event_Model/ListenerFactory.hpp>
#include <Event_Model/Source.hpp>
#include <Event_Model/ThreadPool.hpp>
#include <HaSLL/LoggerManager.hpp>

#include <functional>

namespace Information_Model_Manager {
using namespace std;
using namespace Information_Model;
using namespace Data_Consumer_Adapter;
using namespace Event_Model;
using namespace HaSLL;

ModelRepository::ModelRepository()
    : logger_(LoggerManager::registerTypedLogger(this)),
      source_(make_shared<Source<RegistryChange>>()) {
  Simple_Thread_Pool::Manager::initialise();
}

ModelRepository::~ModelRepository() {
  Simple_Thread_Pool::Manager::terminate();
}

bool ModelRepository::add(const DevicePtr& device) {
  if (!deviceExists(device->id())) {
    logger_->trace(
        "Registering device with id: {} within the Information Model",
        device->id());
    devices_.emplace(device->id(), device);
    source_->notify(make_shared<RegistryChange>(device));
    return true;
  } else {
    logger_->trace("Device with id {} already exists!", device->id());
    return false;
  }
}

bool ModelRepository::remove(const string& device_id) {
  if (deviceExists(device_id)) {
    logger_->trace(
        "Removing Device with id {} from the Information Model", device_id);
    source_->notify(make_shared<RegistryChange>(device_id));
    devices_.erase(device_id);
    return true;
  } else {
    logger_->trace("Device with id {} does not exist!", device_id);
    return false;
  }
}

vector<DevicePtr> ModelRepository::getModelSnapshot() const {
  vector<DevicePtr> result;
  for (const auto& [_, device] : devices_) {
    result.push_back(device);
  }
  return result;
}

DataConnector ModelRepository::getModelDataConnector() {
  return bind(&ModelRepository::connect, this, placeholders::_1);
}

void ModelRepository::logException(const std::exception_ptr& ex_ptr) {
  try {
    if (ex_ptr) {
      rethrow_exception(ex_ptr);
    }
  } catch (exception& ex) {
    logger_->error(
        "Received an exception while trying to notify listeners. Exception: {}",
        ex.what());
  }
}

struct ListenerConnection : public DataConnection {
  explicit ListenerConnection(ListenerPtr<RegistryChange>&& listener)
      : listener_(move(listener)) {}

  ~ListenerConnection() override = default;

private:
  ListenerPtr<RegistryChange> listener_;
};

static constexpr int8_t MODEL_DATA_LISTENER_PRIORITY = 125;

Data_Consumer_Adapter::DataConnectionPtr ModelRepository::connect(
    const Data_Consumer_Adapter::DataNotifier& notifier) {
  auto listener = makeListener<RegistryChange>(notifier,
      bind(&ModelRepository::logException, this, placeholders::_1),
      source_,
      MODEL_DATA_LISTENER_PRIORITY);
  return make_shared<ListenerConnection>(move(listener));
}

bool ModelRepository::deviceExists(const string& device_id) {
  if (devices_.find(device_id) == devices_.end()) {
    logger_->trace("Device with id {} not found!", device_id);
    return false;
  } else {
    return true;
  }
}
} // namespace Information_Model_Manager