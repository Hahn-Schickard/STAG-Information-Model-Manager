#ifndef __BUILDING_AND_REGISTRATION_FACADE_HPP
#define __BUILDING_AND_REGISTRATION_FACADE_HPP

#include "BuildingAndRegistrationInterface.hpp"
#include "DeviceBuilder.hpp"
#include "ModelManager.hpp"

#include <memory>
#include <string>

namespace Information_Access_Manager {
  class BuildingAndRegirtrationFacade
      : public Information_Model_Static_Part::BuildingAndRegistrationInterface {
   public:
    BuildingAndRegirtrationFacade();
    void buildDeviceBase(const std::string& UNIQUE_ID,
        const std::string& NAME,
        const std::string& DESC) final;
    std::string buildDeviceElement(const std::string& NAME,
        const std::string& DESC,
        Information_Model::ElementType type) final;
    std::string buildDeviceElement(const std::string& GROUP_ID,
        const std::string& NAME,
        const std::string& DESC,
        Information_Model::ElementType type) final;
    std::shared_ptr<Information_Model::Device> getDevice() final;
    bool registerDevice(
        std::shared_ptr<Information_Model::Device> device) final;
    bool deregisterDevice(const std::string& DEVICE_ID) final;

   private:
    Model_Manager::ModelManager* manager_;
    Model_Factory::DeviceBuilder* builder_;
  };
}   // namespace Information_Access_Manager

#endif   //__BUILDING_AND_REGISTRATION_FACADE_HPPs