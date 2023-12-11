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

DevicePtr buildMock(const DeviceBuilderInterfacePtr& builder) {
  builder->buildDeviceBase(
      "1234", "Mocky", "Mocked test device without any elements");
  return builder->getResult();
}

using ModelRepositoryEvent =
    std::variant<std::string, Information_Model::NonemptyDevicePtr>;

struct EventListener
    : Event_Model::EventListenerInterface<ModelRepositoryEvent> {
  using ModelRepositoryEventPtr = std::shared_ptr<ModelRepositoryEvent>;

  EventListener(const ModelEventSourcePtr& event_source)
      : EventListenerInterface(event_source),
        logger_(LoggerManager::registerTypedLogger(this)) {
    logger_->trace("Listener Registered!");
  }

  void handleEvent(ModelRepositoryEventPtr /* event */) override {
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

    auto technology_manager = std::make_unique<ModelManager>();

    auto event_source = technology_manager->getModelEventSource();
    if (!event_source) {
      throw runtime_error("Event source can not be null ptr");
    }
    auto event_listener = std::make_shared<EventListener>(event_source);

    auto tai_mock =
        std::make_shared<::testing::NiceMock<TechnologyAdapterMock>>(
            "MockedTAI");
    technology_manager->registerTechnologyAdapter(tai_mock);
    auto builder = tai_mock->getDeviceBuilder();
    auto device_mock = buildMock(builder.base());
    auto registry = tai_mock->getDeviceRegistry();
    registry->registrate(NonemptyDevicePtr(device_mock));

    event_listener->waitForEvent();
  } catch (const exception& ex) {
    cerr << "An unhandled exception occurred while running example. Exception: "
         << ex.what() << endl;
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
