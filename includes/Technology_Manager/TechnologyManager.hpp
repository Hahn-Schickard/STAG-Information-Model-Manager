#ifndef _TECHNOLOGY_MANAGER_HPP
#define _TECHNOLOGY_MANAGER_HPP

#include "BuildingAndRegistrationInterface.hpp"
#include "TechnologyManagerInterface.hpp"

#include <memory>
#include <vector>

namespace Information_Access_Manager {
class TechnologyManager : public TechnologyManagerInterface {
  std::vector<std::shared_ptr<Technology_Adapter::TechnologyAdapter>>
      technology_adapters_;
  std::shared_ptr<Information_Access_Manager::BuildingAndRegistrationInterface>
      building_and_registration_facade_;
  static TechnologyManager *instance_;

  TechnologyManager();
  std::vector<std::shared_ptr<Technology_Adapter::TechnologyAdapter>>::iterator
  findTechnologyAdapter(
      const std::shared_ptr<Technology_Adapter::TechnologyAdapter> &adapter);

public:
  static TechnologyManager *getInstance();
  bool registerTechnologyAdapter(
      std::shared_ptr<Technology_Adapter::TechnologyAdapter> adapter) final;
  bool deregisterTechnologyAdapter(
      std::shared_ptr<Technology_Adapter::TechnologyAdapter> adapter) final;
  ~TechnologyManager();
};
} // namespace Information_Access_Manager

#endif //_TECHNOLOGY_MANAGER_HPP