#ifndef __MODEL_MANAGER_HPP
#define __MODEL_MANAGER_HPP

#include "Device.hpp"
#include "Notifier.hpp"
#include <memory>
#include <unordered_map>

namespace Model_Manager {
class ModelManager : public Model_Event_Handler::Notifier {
public:
  // bool registerDevice(std::unique_ptr<Information_Model::Device>
  // device);//bearbeitet
  bool registerDevice(std::shared_ptr<Information_Model::Device> device);
  bool deregisterDevice(const std::string &DEVICE_ID);

private:
  bool deviceExists(const std::string &DEVICE_ID);

private:
  std::unordered_map<std::string, std::shared_ptr<Information_Model::Device>>
      devices;
};
} // namespace Model_Manager

#endif //__MODEL_MANAGER_HPP