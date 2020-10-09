#ifndef __MODEL_MANAGER_HPP
#define __MODEL_MANAGER_HPP

#include "Device.hpp"
#include "ModelRegistryInterface.hpp"
#include "Notifier.hpp"

#include <memory>
#include <unordered_map>

namespace Infromation_Model_Manager {
class ModelRegistry : public Technology_Adapter::ModelRegistryInterface,
                      public Model_Event_Handler::Notifier {
  using DevicesMap =
      std::unordered_map<std::string,
                         std::shared_ptr<Information_Model::Device>>;
  DevicesMap devices_;

  bool deviceExists(const std::string &device_id);

public:
  bool
  registerDevice(std::shared_ptr<Information_Model::Device> device) override;
  bool deregisterDevice(const std::string &device_id) override;
};
} // namespace Infromation_Model_Manager

#endif //__MODEL_MANAGER_HPP