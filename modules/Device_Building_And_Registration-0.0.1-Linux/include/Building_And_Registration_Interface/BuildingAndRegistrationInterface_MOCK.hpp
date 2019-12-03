#ifndef __BUILDING_AND_REGISTRATION_INTERFACE_MOCK_HPP
#define __BUILDING_AND_REGISTRATION_INTERFACE_MOCK_HPP

#include "BuildingAndRegistrationInterface.hpp"

#include <gmock/gmock.h>

class MockBnR
    : public Information_Model_Static_Part::BuildingAndRegistrationInterface {
public:
  MOCK_METHOD(void, buildDeviceBase,
              (const std::string &UNIQUE_ID, const std::string &NAME,
               const std::string &DESC),
              (override));

  MOCK_METHOD(std::string, buildDeviceElement,
              (const std::string &NAME, const std::string &DESC,
               Information_Model::ElementType type),
              (override));

  MOCK_METHOD(std::string, buildDeviceElement,
              (const std::string &GROUP_ID, const std::string &NAME,
               const std::string &DESC, Information_Model::ElementType type),
              (override));

  MOCK_METHOD(std::shared_ptr<Information_Model::Device>, getDevice, (),
              (override));

  MOCK_METHOD(bool, registerDevice,
              (std::shared_ptr<Information_Model::Device> device), (override));

  MOCK_METHOD(bool, deregisterDevice, (const std::string &DEVICE_ID),
              (override));
};

#endif //__BUILDING_AND_REGISTRATION_INTERFACE_MOCK_HPP