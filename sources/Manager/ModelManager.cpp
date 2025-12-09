#include "ModelManager.hpp"
#include "Builder.hpp"
#include <HaSLL/LoggerManager.hpp>

#include <algorithm>
#include <functional>

namespace Information_Model_Manager {
using namespace std;
using namespace Technology_Adapter;
using namespace Information_Model;
using namespace HaSLL;

ModelManager::ModelManager()
    : logger_(LoggerManager::registerTypedLogger(this)),
      registry_(make_shared<ModelRepository>()) {}

ModelManager::TechnologyAdaptersList::iterator
ModelManager::findTechnologyAdapter(const TAI_Ptr& adapter) {
  return find(
      technology_adapters_.begin(), technology_adapters_.end(), adapter);
}

Data_Consumer_Adapter::DataConnector ModelManager::getModelDataConnector() {
  return registry_->getModelDataConnector();
}

vector<DevicePtr> ModelManager::getModelSnapshot() {
  return registry_->getModelSnapshot();
}

Information_Model::DeviceBuilderPtr ModelManager::makeBuilder() {
  return std::make_shared<Builder>();
}

void ModelManager::registerTechnologyAdapter(const TAI_Ptr& adapter) {
  if (findTechnologyAdapter(adapter) == technology_adapters_.end()) {
    adapter->setInterfaces(
        std::bind(&ModelManager::makeBuilder, this), registry_);
    technology_adapters_.push_back(adapter);
  } else {
    throw TechnologyAdapterRegistered(adapter->name());
  }
}

void ModelManager::deregisterTechnologyAdapter(const TAI_Ptr& adapter) {
  auto iterator = findTechnologyAdapter(adapter);
  if (iterator != technology_adapters_.end()) {
    technology_adapters_.erase(iterator);
  } else {
    throw TechnologyAdapterNotFound(adapter->name());
  }
}
} // namespace Information_Model_Manager