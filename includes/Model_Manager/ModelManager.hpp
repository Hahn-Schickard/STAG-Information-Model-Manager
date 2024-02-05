#ifndef __INFORMATION_MODEL_MANAGER_HPP
#define __INFORMATION_MODEL_MANAGER_HPP

#include "DeviceBuilder.hpp"
#include "ModelRepository.hpp"
#include "Technology_Adapter_Interface/TechnologyAdapterInterface.hpp"

#include "HaSLL/Logger.hpp"

#include <memory>
#include <stdexcept>
#include <vector>

using ModelEventSourcePtr = std::shared_ptr<Event_Model::EventSourceInterface<
    Data_Consumer_Adapter::ModelRepositoryEvent>>;

namespace Information_Model_Manager {

struct TechnologyAdapterRegistered : std::runtime_error {
  TechnologyAdapterRegistered(const std::string& name)
      : runtime_error(name + " Technology Adapter is already registered") {}
};

struct TechnologyAdapterNotFound : std::runtime_error {
  TechnologyAdapterNotFound(const std::string& name)
      : runtime_error(name + " Technology Adapter is not registered") {}
};

struct ModelManager {
  ModelManager();

  ModelEventSourcePtr getModelEventSource();
  std::vector<Information_Model::DevicePtr> getModelSnapshot();

  void registerTechnologyAdapter(const Technology_Adapter::TAI_Ptr& adapter);
  void deregisterTechnologyAdapter(const Technology_Adapter::TAI_Ptr& adapter);

private:
  using TechnologyAdaptersList = std::vector<Technology_Adapter::TAI_Ptr>;
  using DeviceBuilderPtr =
      std::shared_ptr<Information_Model_Manager::DeviceBuilder>;
  using ModelRepositoryPtr =
      std::shared_ptr<Information_Model_Manager::ModelRepository>;

  TechnologyAdaptersList::iterator findTechnologyAdapter(
      const Technology_Adapter::TAI_Ptr& adapter);

  TechnologyAdaptersList technology_adapters_;
  HaSLI::LoggerPtr logger_;
  DeviceBuilderPtr builder_;
  ModelRepositoryPtr registry_;
};
} // namespace Information_Model_Manager

#endif //__INFORMATION_MODEL_MANAGER_HPP