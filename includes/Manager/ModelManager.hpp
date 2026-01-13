#ifndef __MODEL_MANAGER_HPP
#define __MODEL_MANAGER_HPP

#include "ModelRepository.hpp"

#include <Technology_Adapter_Interface/ResponseRepository.hpp>
#include <Technology_Adapter_Interface/TechnologyAdapter.hpp>

#include <memory>
#include <stdexcept>
#include <vector>

namespace Information_Model_Manager {
using ModelEventSourcePtr = std::shared_ptr<
    Event_Model::SourceInterface<Data_Consumer_Adapter::RegistryChangePtr>>;

struct TechnologyAdapterRegistered : std::runtime_error {
  explicit TechnologyAdapterRegistered(const std::string& name)
      : runtime_error(name + " Technology Adapter is already registered") {}
};

struct TechnologyAdapterNotFound : std::runtime_error {
  explicit TechnologyAdapterNotFound(const std::string& name)
      : runtime_error(name + " Technology Adapter is not registered") {}
};

struct ModelManager {
  using TAI_Ptr = Technology_Adapter::TechnologyAdapterPtr;

  ModelManager() = default;

  ~ModelManager() = default;

  Data_Consumer_Adapter::DataConnector getModelDataConnector();

  std::vector<Information_Model::DevicePtr> getModelSnapshot();

  void registerTechnologyAdapter(const TAI_Ptr& adapter);

  void deregisterTechnologyAdapter(const TAI_Ptr& adapter);

private:
  using TechnologyAdaptersList = std::vector<TAI_Ptr>;
  using ModelRepositoryPtr = std::shared_ptr<ModelRepository>;

  TechnologyAdaptersList::iterator find(const TAI_Ptr& adapter);

  TechnologyAdaptersList adapters_;
  ModelRepositoryPtr registry_ = std::make_shared<ModelRepository>();
};
} // namespace Information_Model_Manager

#endif //__MODEL_MANAGER_HPP