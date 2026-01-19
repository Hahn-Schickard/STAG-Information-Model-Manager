#include "ModelManager.hpp"
#include "Builder.hpp"

#include <algorithm>
#include <functional>

namespace Information_Model_Manager {
using namespace std;
using namespace Technology_Adapter;
using namespace Information_Model;

ModelManager::TechnologyAdaptersList::iterator ModelManager::find(
    const TAI_Ptr& adapter) {
  return std::find(adapters_.begin(), adapters_.end(), adapter);
}

Data_Consumer_Adapter::DataConnector
ModelManager::getModelDataConnector() const {
  return registry_->getModelDataConnector();
}

vector<DevicePtr> ModelManager::getModelSnapshot() const {
  return registry_->getModelSnapshot();
}

void ModelManager::registerTechnologyAdapter(const TAI_Ptr& adapter) {
  if (!adapter) {
    throw invalid_argument("Can not register an empty adapter");
  }

  if (find(adapter) == adapters_.end()) {
    adapter->setInterfaces(
        []() { return std::make_shared<Builder>(); }, registry_);
    adapters_.push_back(adapter);
  } else {
    throw TechnologyAdapterRegistered(adapter->name());
  }
}

void ModelManager::deregisterTechnologyAdapter(const TAI_Ptr& adapter) {
  if (!adapter) {
    throw invalid_argument("Can not deregister an empty adapter");
  }

  if (auto iterator = find(adapter); iterator != adapters_.end()) {
    adapters_.erase(iterator);
  } else {
    throw TechnologyAdapterNotFound(adapter->name());
  }
}
} // namespace Information_Model_Manager