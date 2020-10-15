#include "ModelManager.hpp"
#include <algorithm>

using namespace std;

namespace Information_Model_Manager {
ModelManager::ModelManager()
    : builder_(make_shared<DeviceBuilder>()),
      registry_(make_shared<ModelRegistry>()) {}

ModelManager::TechnologyAdaptersList::iterator
ModelManager::findTechnologyAdapter(const TechnologyAdapterPtr &adapter) {
  return find(technology_adapters_.begin(), technology_adapters_.end(),
              adapter);
}

ModelEventSourcePtr ModelManager::getModelEventSource() { return registry_; }

bool ModelManager::registerTechnologyAdapter(TechnologyAdapterPtr adapter) {
  if (findTechnologyAdapter(adapter) == technology_adapters_.end()) {
    adapter->setInterfaces(builder_, registry_);
    technology_adapters_.push_back(adapter);
    return true;
  } else {
    //@TODO: Add logging/exception throwing here
    return false;
  }
}
bool ModelManager::deregisterTechnologyAdapter(TechnologyAdapterPtr adapter) {
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