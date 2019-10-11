#ifndef __TECHNOLOGY_ADAPTER_HPP
#define __TECHNOLOGY_ADAPTER_HPP

#include "BuildingAndRegistrationInterface.hpp"
#include <memory>

namespace Information_Access_Manager {
class TechnologyAdapter {
public:
  bool setBuildingAndRegistrationInterface(
      std::shared_ptr<
          Information_Model_Static_Part::BuildingAndRegistrationInterface>
          building_and_registration_interface);

protected:
  bool buildNewDevice(const std::string UNIQUE_ID, const std::string NAME,
                      const std::string DESC);
  std::string addDeviceElement(const std::string NAME, const std::string DESC,
                               Information_Model::ElementType type);
  std::string addDeviceElement(const std::string GROUP_ID,
                               const std::string NAME, const std::string DESC,
                               Information_Model::ElementType type);
  std::unique_ptr<Information_Model::Device> getDeviceFromBuilder();
  bool registerDeviceToModel(std::unique_ptr<Information_Model::Device> device);
  bool deregisterDeviceFromModel(const std::string DEVICE_ID);

private:
  bool isBuildingAndRegistrationInterface();

  std::shared_ptr<
      Information_Model_Static_Part::BuildingAndRegistrationInterface>
      model_interface_;
};
} // namespace Information_Access_Manager

#endif //__TECHNOLOGY_ADAPTER_HPP