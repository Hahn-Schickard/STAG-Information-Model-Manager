#ifndef _TECHNOLOGY_MANAGER_HPP
#define _TECHNOLOGY_MANAGER_HPP

#include "BuildingAndRegistrationInterface.hpp"
#include "TechnologyManagerInterface.hpp"
#include <memory>
#include <vector>

namespace Information_Access_Manager {
class TechnologyManager : public TechnologyManagerInterface {
public:
  static TechnologyManager *getInstance();
  bool
  registerTechnologyAdapter(std::shared_ptr<TechnologyAdapter> adapter) final;
  bool
  deregisterTechnologyAdapter(std::shared_ptr<TechnologyAdapter> adapter) final;
  ~TechnologyManager();

private:
  TechnologyManager();
  std::vector<std::shared_ptr<TechnologyAdapter>>::iterator
  findTechnologyAdapter(std::shared_ptr<TechnologyAdapter> adapter);

  std::vector<std::shared_ptr<TechnologyAdapter>> technology_adapters_;
  std::shared_ptr<
      Information_Model_Static_Part::BuildingAndRegistrationInterface>
      building_and_registration_facade_;
  static TechnologyManager *instance_;
};
} // namespace Information_Access_Manager

#endif //_TECHNOLOGY_MANAGER_HPP