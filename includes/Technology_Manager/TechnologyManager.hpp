#ifndef _TECHNOLOGY_MANAGER_HPP
#define _TECHNOLOGY_MANAGER_HPP

#include "TechnologyManagerInterface.hpp"
#include <memory>
#include <vector>

namespace Information_Access_Manager {
class TechnologyManager : public TechnologyManagerInterface {
public:
  bool
  registerTechnologyAdapter(std::shared_ptr<TechnologyAdapter> adapter) final;
  bool
  deregisterTechnologyAdapter(std::shared_ptr<TechnologyAdapter> adapter) final;

private:
  std::vector<std::shared_ptr<TechnologyAdapter>>::iterator
  findTechnologyAdapter(std::shared_ptr<TechnologyAdapter> adapter);

  std::vector<std::shared_ptr<TechnologyAdapter>> technology_adapters_;
};
} // namespace Information_Access_Manager

#endif //_TECHNOLOGY_MANAGER_HPP