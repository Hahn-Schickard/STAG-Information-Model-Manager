#ifndef __INFORMATION_MODEL_MANAGER_HPP
#define __INFORMATION_MODEL_MANAGER_HPP

#include "DeviceBuilder.hpp"
#include "ModelRegistry.hpp"
#include "TechnologyManagerInterface.hpp"

#include <memory>
#include <vector>

namespace Information_Model_Manager {
class ModelManager
    : public Information_Access_Manager::TechnologyManagerInterface {
  using TechnologyAdaptersList =
      std::vector<std::shared_ptr<Technology_Adapter::TechnologyAdapter>>;
  using DeviceBuilderPtr =
      std::shared_ptr<Infromation_Model_Manager::DeviceBuilder>;
  using ModelRegistryPtr =
      std::shared_ptr<Infromation_Model_Manager::ModelRegistry>;

  TechnologyAdaptersList technology_adapters_;
  DeviceBuilderPtr builder_;
  ModelRegistryPtr registry_;

  TechnologyAdaptersList::iterator findTechnologyAdapter(
      const std::shared_ptr<Technology_Adapter::TechnologyAdapter> &adapter);

public:
  using TechnologyAdapterPtr =
      std::shared_ptr<Technology_Adapter::TechnologyAdapter>;
  using ModelEventSourcePtr =
      std::shared_ptr<Event_Model::EventSource<DCAI::ModelRegistryEvent>>;

  ModelManager();

  ModelEventSourcePtr getModelEventSource();

  bool registerTechnologyAdapter(TechnologyAdapterPtr adapter) final;
  bool deregisterTechnologyAdapter(TechnologyAdapterPtr adapter) final;
};
} // namespace Information_Model_Manager

#endif //__INFORMATION_MODEL_MANAGER_HPP