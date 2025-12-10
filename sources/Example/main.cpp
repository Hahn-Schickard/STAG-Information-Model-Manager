#include <Data_Consumer_Adapter_Interface/DataConsumerAdapter.hpp>
#include <HaSLL/LoggerManager.hpp>
#include <Technology_Adapter_Interface/TechnologyAdapter.hpp>

#include "ModelManager.hpp"

#include <iostream>
#include <set>
#include <stdexcept>
#include <thread>

using namespace HaSLL;
using namespace std;
using namespace Information_Model;
using namespace Information_Model_Manager;
using namespace Technology_Adapter;

DevicePtr buildDummyDevice(const DeviceBuilderPtr& builder) {
  builder->setDeviceInfo(
      "1234", BuildInfo{"Fakie", "Fake test device with a readable label"});
  builder->addReadable(BuildInfo{"Label", "A label describing this device "},
      DataType::String,
      []() { return "Hahn-Schickard"; });
  return builder->result();
}

struct DummyDCA : public Data_Consumer_Adapter::DataConsumerAdapter {
  explicit DummyDCA(const Data_Consumer_Adapter::DataConnector& connector)
      : DataConsumerAdapter("Example DCAI", connector) {}

  ~DummyDCA() override = default;

private:
  void registrate(const DevicePtr& device) override {
    auto [_, emplaced] = devices_.emplace(device->id());
    if (emplaced) {
      logger->trace("Device: {} was registered!", device->name());
    } else {
      logger->trace("Device: {} was already registered. Ignoring new instance!",
          device->name());
    }
  }

  void deregistrate(const string& device_id) override {
    auto it = devices_.find(device_id);
    if (it != devices_.end()) {
      logger->trace("Device: {} was deregistered!", device_id);
    } else {
      string error_msg = "Device " + device_id + " does not exist!";
      throw runtime_error(error_msg);
    }
  }

  set<string> devices_;
};

int main() {
  auto status = EXIT_SUCCESS;
  try {
    LoggerManager::initialise(makeDefaultRepository());

    try {
      auto technology_manager = std::make_unique<ModelManager>();

      auto model_connector = technology_manager->getModelDataConnector();
      auto dummy_dca = std::make_shared<DummyDCA>(model_connector);

      auto dummy_tai = std::make_shared<TechnologyAdapter>("Dummy_TAI");
      technology_manager->registerTechnologyAdapter(dummy_tai);
      auto registry = dummy_tai->getRegistry();
      registry->registrate(buildDummyDevice(dummy_tai->getBuilder()));

      this_thread::sleep_for(1s);

      registry->deregistrate("1234");
    } catch (const exception& ex) {
      cerr << "An unhandled exception occurred while running example. "
              "Exception: "
           << ex.what() << endl;
      status = EXIT_FAILURE;
    }
    LoggerManager::terminate();
  } catch (...) {
    cerr << "Unknown error occurred during program execution." << endl;
    status = EXIT_FAILURE;
  }

  exit(status);
}
