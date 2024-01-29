#ifndef __INFORMATION_MODEL_MANAGER_HPP
#define __INFORMATION_MODEL_MANAGER_HPP

#include "ModelRepository.hpp"

#include "HaSLL/Logger.hpp"
#include "Technology_Adapter_Interface/TechnologyManagerInterface.hpp"

#include <memory>
#include <vector>

using ModelEventSourcePtr = std::shared_ptr<Event_Model::EventSourceInterface<
    Data_Consumer_Adapter::ModelRepositoryEvent>>;

namespace Information_Model_Manager {
struct ModelManager : public Technology_Adapter::TechnologyManagerInterface {
  ModelManager();

  ModelEventSourcePtr getModelEventSource();
  std::vector<Information_Model::DevicePtr> getModelSnapshot();

  bool registerTechnologyAdapter(Technology_Adapter::TAI_Ptr adapter) final;
  bool deregisterTechnologyAdapter(Technology_Adapter::TAI_Ptr adapter) final;

private:
  using TechnologyAdaptersList = std::vector<Technology_Adapter::TAI_Ptr>;
  using UniqueDeviceBuilderPtr =
      Technology_Adapter::TAI::UniqueDeviceBuilderPtr;
  using ModelRepositoryPtr =
      std::shared_ptr<Information_Model_Manager::ModelRepository>;

  UniqueDeviceBuilderPtr makeBuilder();

  TechnologyAdaptersList::iterator findTechnologyAdapter(
      const Technology_Adapter::TAI_Ptr& adapter);

  TechnologyAdaptersList technology_adapters_;
  HaSLI::LoggerPtr logger_;
  ModelRepositoryPtr registry_;
};
} // namespace Information_Model_Manager

#endif //__INFORMATION_MODEL_MANAGER_HPP