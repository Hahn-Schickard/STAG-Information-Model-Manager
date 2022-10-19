#ifndef __INFORMATION_MODEL_MANAGER_HPP
#define __INFORMATION_MODEL_MANAGER_HPP

#include "DeviceBuilder.hpp"
#include "ModelRegistry.hpp"
#include "Technology_Adapter_Interface/TechnologyManagerInterface.hpp"

#include <memory>
#include <vector>

using ModelEventSourcePtr = std::shared_ptr<
    Event_Model::EventSourceInterface<DCAI::ModelRegistryEvent>>;

namespace Information_Model_Manager {
class ModelManager : public Technology_Adapter::TechnologyManagerInterface {
  using TechnologyAdaptersList =
      std::vector<Technology_Adapter::TechnologyAdapterPtr>;
  using DeviceBuilderPtr =
      std::shared_ptr<Information_Model_Manager::DeviceBuilder>;
  using ModelRegistryPtr =
      std::shared_ptr<Information_Model_Manager::ModelRegistry>;

  TechnologyAdaptersList technology_adapters_;
  DeviceBuilderPtr builder_;
  ModelRegistryPtr registry_;

  TechnologyAdaptersList::iterator findTechnologyAdapter(
      const Technology_Adapter::TechnologyAdapterPtr& adapter);

public:
  ModelManager();

  ModelEventSourcePtr getModelEventSource();

  bool registerTechnologyAdapter(
      Technology_Adapter::TechnologyAdapterPtr adapter) final;
  bool deregisterTechnologyAdapter(
      Technology_Adapter::TechnologyAdapterPtr adapter) final;
};
} // namespace Information_Model_Manager

#endif //__INFORMATION_MODEL_MANAGER_HPP