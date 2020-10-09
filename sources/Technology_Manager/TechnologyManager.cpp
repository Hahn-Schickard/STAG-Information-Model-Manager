#include "TechnologyManager.hpp"
#include <algorithm>

using namespace std;
using namespace Infromation_Model_Manager;
using namespace Technology_Adapter;

namespace Information_Access_Manager {
TechnologyManager::TechnologyManager() : builder_(), registry_() {}

TechnologyManager::TechnologyAdaptersList::iterator
TechnologyManager::findTechnologyAdapter(const TechnologyAdapterPtr &adapter) {
  return find(technology_adapters_.begin(), technology_adapters_.end(),
              adapter);
}

bool TechnologyManager::registerTechnologyAdapter(
    TechnologyAdapterPtr adapter) {
  if (findTechnologyAdapter(adapter) == technology_adapters_.end()) {
    adapter->setInterfaces(builder_, registry_);
    technology_adapters_.push_back(adapter);
    return true;
  } else {
    //@TODO: Add logging/exception throwing here
    return false;
  }
}
bool TechnologyManager::deregisterTechnologyAdapter(
    TechnologyAdapterPtr adapter) {
  auto iterator = findTechnologyAdapter(adapter);
  if (iterator != technology_adapters_.end()) {
    technology_adapters_.erase(iterator);
    return true;
  } else {
    //@TODO: Add logging/exception throwing here
    return false;
  }
}
} // namespace Information_Access_Manager