#ifndef __ABSTRACTION_FACTORY_HPP
#define __ABSTRACTION_FACTORY_HPP

#include "BuildingAndRegistrationInterface.hpp"

namespace Information_Access_Manager {
class AbstractionFactory {
public:
  AbstractionFactory(
      std::shared_ptr<
          Information_Model_Static_Part::BuildingAndRegistrationInterface>
          model_interface);

  bool buildNewDevice(const std::string &UNIQUE_ID, const std::string &NAME,
                      const std::string &DESC);
  std::string addDeviceElement(const std::string &NAME, const std::string &DESC,
                               Information_Model::ElementType type);
  std::string addDeviceElement(const std::string &GROUP_ID,
                               const std::string &NAME, const std::string &DESC,
                               Information_Model::ElementType type);
  std::shared_ptr<Information_Model::Device> getDeviceFromBuilder();
  bool registerDeviceToModel(std::shared_ptr<Information_Model::Device> device);
  bool deregisterDeviceFromModel(const std::string &DEVICE_ID);

private:
  std::shared_ptr<
      Information_Model_Static_Part::BuildingAndRegistrationInterface>
      model_interface_;
};
} // namespace Information_Access_Manager

#endif //__ABSTRACTION_FACTORY_HPP