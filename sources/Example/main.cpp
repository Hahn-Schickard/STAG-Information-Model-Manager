#include "HaSLL/LoggerManager.hpp"
#include "HaSLL/SPD_LoggerRepository.hpp"

#include "Event_Model/EventListenerInterface.hpp"
#include "Technology_Adapter_Interface/mocks/TechnologyAdapter_MOCK.hpp"

#include "ModelManager.hpp"

#include <iostream>
#include <stdexcept>

using namespace HaSLL;
using namespace std;
using namespace Information_Model;
using namespace Information_Model_Manager;
using namespace Technology_Adapter;
using namespace Technology_Adapter::testing;

DevicePtr buildMock(DeviceBuilderPtr builder) {
  builder->buildDeviceBase(
      "1234", "Mocky", "Mocked test device without any elements");
  return builder->getResult();
}

struct TechnologyAdapterFake : TechnologyAdapter {
  TechnologyAdapterFake() : TechnologyAdapter("TAI-Fake") {}

  void interfaceSet() override {
    auto logger = getLogger();
    logger->info("Interface set properly!");
  }
};

using ModelRegistryEvent =
    std::variant<std::string, Information_Model::NonemptyDevicePtr>;

struct EventListener : Event_Model::EventListenerInterface<ModelRegistryEvent> {
  using ModelRegistryEventPtr = std::shared_ptr<ModelRegistryEvent>;

  EventListener(ModelEventSourcePtr event_source)
      : EventListenerInterface(event_source),
        logger_(LoggerManager::registerTypedLogger(this)) {
    logger_->trace("Listener Registered!");
  }

  void handleEvent(ModelRegistryEventPtr /* event */) override {
    logger_->info("Handle Event was called!");
    finished_.set_value(true);
  }

  void waitForEvent() {
    auto result = finished_.get_future();
    auto status = result.wait_for(1s);
    if (status != future_status::ready) {
      throw runtime_error("handleEvent was not called and timed out!");
    } else {
      result.get();
    }
  }

private:
  LoggerPtr logger_;
  std::promise<bool> finished_;
};

int main() {
  try {
    auto repo = std::make_shared<SPD_LoggerRepository>();
    LoggerManager::initialise(repo);

    auto technology_manager = ModelManager();

    auto event_source = technology_manager.getModelEventSource();
    if (!event_source) {
      throw runtime_error("Event source can not be null ptr");
    }
    auto event_listener = std::make_shared<EventListener>(event_source);

    auto tai_fake = std::make_shared<TechnologyAdapterFake>();
    technology_manager.registerTechnologyAdapter(tai_fake);
    auto builder = tai_fake->getDeviceBuilder();
    if (!builder) {
      throw runtime_error("Device Builder can not be null ptr");
    }
    auto device_mock = buildMock(builder);
    auto registry = tai_fake->getModelRegistry();
    registry->registerDevice(device_mock);

    event_listener->waitForEvent();

    exit(EXIT_SUCCESS);
  } catch (const exception& ex) {
    cerr << "An unhandled exception occurred while running example. Exception: "
         << ex.what() << endl;
    exit(EXIT_FAILURE);
  }
}
