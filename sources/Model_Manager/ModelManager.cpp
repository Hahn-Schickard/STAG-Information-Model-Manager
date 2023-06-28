#include "ModelManager.hpp"
#include <algorithm>

using namespace std;
using namespace Technology_Adapter;
using namespace Information_Model;

namespace Information_Model_Manager {
ModelManager::ModelManager()
    : builder_(make_shared<DeviceBuilder>()),
      registry_(make_shared<ModelRepository>()) {}

ModelManager::TechnologyAdaptersList::iterator
ModelManager::findTechnologyAdapter(const TAI_Ptr& adapter) {
  return find(
      technology_adapters_.begin(), technology_adapters_.end(), adapter);
}

ModelEventSourcePtr ModelManager::getModelEventSource() { return registry_; }

bool ModelManager::registerTechnologyAdapter(TAI_Ptr adapter) {
  if (findTechnologyAdapter(adapter) == technology_adapters_.end()) {
    adapter->setInterfaces(NonemptyDeviceBuilderInterfacePtr(builder_),
        NonemptyModelRepositoryInterfacePtr(registry_));
    technology_adapters_.push_back(adapter);
    return true;
  } else {
    //@TODO: Add logging/exception throwing here
    return false;
  }
}

bool ModelManager::deregisterTechnologyAdapter(TAI_Ptr adapter) {
  auto iterator = findTechnologyAdapter(adapter);
  if (iterator != technology_adapters_.end()) {
    technology_adapters_.erase(iterator);
    return true;
  } else {
    //@TODO: Add logging/exception throwing here
    return false;
  }
}
} // namespace Information_Model_Manager