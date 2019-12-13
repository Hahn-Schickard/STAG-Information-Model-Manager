#ifndef __TECHNOLOGY_MANAGER_INTERFACE_MOCK_HPP
#define __TECHNOLOGY_MANAGER_INTERFACE_MOCK_HPP

#include "TechnologyManagerInterface.hpp"

#include <gmock/gmock.h>

namespace Information_Access_Manager {
  class TechnologyManagerInterfaceMock : public TechnologyManagerInterface {
    MOCK_METHOD(bool,
        registerTechnologyAdapter,
        (std::shared_ptr<TechnologyAdapter> adapter),
        (override));

    MOCK_METHOD(bool,
        deregisterTechnologyAdapter,
        (std::shared_ptr<TechnologyAdapter> adapter),
        (override));
  };
}   // namespace Information_Access_Manager

#endif   //__TECHNOLOGY_MANAGER_INTERFACE_MOCK_HPP