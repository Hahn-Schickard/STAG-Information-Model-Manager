#ifndef __TECHNOLOGY_MANAGER_INTERFACE_MOCK_HPP
#define __TECHNOLOGY_MANAGER_INTERFACE_MOCK_HPP

#include "TechnologyAdapter.hpp"

#include <gmock/gmock.h>

namespace Information_Access_Manager {
class TechnologyAdapterMock : public TechnologyAdapter {
  MOCK_METHOD(bool, start, (), (override));
  MOCK_METHOD(bool, isRunning, (), (override));
  MOCK_METHOD(void, BuildingAndRegistrationInterfaceWasSet, (), (override));
  MOCK_METHOD(bool, stop, (), (override));
};
} // namespace Information_Access_Manager

#endif //__TECHNOLOGY_MANAGER_INTERFACE_MOCK_HPP