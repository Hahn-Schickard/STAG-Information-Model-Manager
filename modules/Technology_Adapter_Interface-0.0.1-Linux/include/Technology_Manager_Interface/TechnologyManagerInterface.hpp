#ifndef __TECHNOLOGY_MANAGER_INTERFACE_HPP
#define __TECHNOLOGY_MANAGER_INTERFACE_HPP

#include "TechnologyAdapter.hpp"

#include <memory>

namespace Information_Access_Manager {
  class TechnologyManagerInterface {
   public:
    virtual bool registerTechnologyAdapter(
        std::shared_ptr<TechnologyAdapter> adapter)
        = 0;
    virtual bool deregisterTechnologyAdapter(
        std::shared_ptr<TechnologyAdapter> adapter)
        = 0;
    virtual ~TechnologyManagerInterface() = default;
  };
}   // namespace Information_Access_Manager

#endif   //__TECHNOLOGY_MANAGER_INTERFACE_HPP