#ifndef __INFORMATION_MODEL_MANAGER_HPP
#define __INFORMATION_MODEL_MANAGER_HPP

#include "DeviceBuilder.hpp"
#include "ModelRepository.hpp"
#include "Technology_Adapter_Interface/TechnologyManagerInterface.hpp"

#include <memory>
#include <vector>

using ModelEventSourcePtr = std::shared_ptr<Event_Model::EventSourceInterface<
    Data_Consumer_Adapter::ModelRepositoryEvent>>;

namespace Information_Model_Manager {
class ModelManager : public Technology_Adapter::TechnologyManagerInterface {
  using TechnologyAdaptersList = std::vector<Technology_Adapter::TAI_Ptr>;
  using DeviceBuilderPtr =
      std::shared_ptr<Information_Model_Manager::DeviceBuilder>;
  using ModelRepositoryPtr =
      std::shared_ptr<Information_Model_Manager::ModelRepository>;

  TechnologyAdaptersList technology_adapters_;
  DeviceBuilderPtr builder_;
  ModelRepositoryPtr registry_;

  TechnologyAdaptersList::iterator findTechnologyAdapter(
      const Technology_Adapter::TAI_Ptr& adapter);

public:
  ModelManager();

  ModelEventSourcePtr getModelEventSource();

  std::vector<Information_Model::NonemptyDevicePtr> getModelSnapshot();

  bool registerTechnologyAdapter(Technology_Adapter::TAI_Ptr adapter) final;
  bool deregisterTechnologyAdapter(Technology_Adapter::TAI_Ptr adapter) final;
};
} // namespace Information_Model_Manager

#endif //__INFORMATION_MODEL_MANAGER_HPP