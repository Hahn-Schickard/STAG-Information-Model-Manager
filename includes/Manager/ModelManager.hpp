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
  TechnologyAdapterRegistered(const std::string& name)
      : runtime_error(name + " Technology Adapter is already registered") {}
};

struct TechnologyAdapterNotFound : std::runtime_error {
  TechnologyAdapterNotFound(const std::string& name)
      : runtime_error(name + " Technology Adapter is not registered") {}
};

struct ModelManager {
  using TAI_Ptr = Technology_Adapter::TechnologyAdapterPtr;

  ModelManager();

  ~ModelManager() = default;

  Data_Consumer_Adapter::DataConnector getModelDataConnector();

  std::vector<Information_Model::DevicePtr> getModelSnapshot();

  void registerTechnologyAdapter(const TAI_Ptr& adapter);

  void deregisterTechnologyAdapter(const TAI_Ptr& adapter);

private:
  using TechnologyAdaptersList = std::vector<TAI_Ptr>;
  using ModelRepositoryPtr =
      std::shared_ptr<Information_Model_Manager::ModelRepository>;

  Information_Model::DeviceBuilderPtr makeBuilder();

  TechnologyAdaptersList::iterator findTechnologyAdapter(
      const TAI_Ptr& adapter);

  TechnologyAdaptersList technology_adapters_;
  ModelRepositoryPtr registry_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_MANAGER_HPP