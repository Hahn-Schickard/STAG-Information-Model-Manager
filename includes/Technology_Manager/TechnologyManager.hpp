#ifndef _TECHNOLOGY_MANAGER_HPP
#define _TECHNOLOGY_MANAGER_HPP

#include "TechnologyManagerInterface.hpp"

namespace Infromation_Access_Manager {
class TechnologyManager : public TechnologyManagerInterface {
  bool registerTechnologyAdapter(
      std::shared_ptr<TechnologyAdapter> adapter) const final;
  bool deregisterTechnologyAdapter(
      std::shared_ptr<TechnologyAdapter> adapter) const final;
};
} // namespace Infromation_Access_Manager

#endif //_TECHNOLOGY_MANAGER_HPP