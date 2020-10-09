#ifndef _TECHNOLOGY_MANAGER_HPP
#define _TECHNOLOGY_MANAGER_HPP

#include "DeviceBuilder.hpp"
#include "ModelRegistry.hpp"
#include "TechnologyManagerInterface.hpp"

#include <memory>
#include <vector>

namespace Information_Access_Manager {
class TechnologyManager : public TechnologyManagerInterface {
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

  TechnologyManager();

  bool registerTechnologyAdapter(TechnologyAdapterPtr adapter) final;
  bool deregisterTechnologyAdapter(TechnologyAdapterPtr adapter) final;
};
} // namespace Information_Access_Manager

#endif //_TECHNOLOGY_MANAGER_HPP