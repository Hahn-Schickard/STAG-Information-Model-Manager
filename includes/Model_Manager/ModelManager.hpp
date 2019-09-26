#ifndef __MODEL_MANAGER_HPP
#define __MODEL_MANAGER_HPP

#include "Device.hpp"
#include "Notifier.hpp"
#include <memory>
#include <unordered_map>

namespace Model_Manager {
class ModelManager : public Model_Event_Handler::Notifier {
public:
  void registerDevice(std::unique_ptr<Information_Model::Device> device);

private:
  std::unordered_map<std::string, Information_Model::Device *> devices;
};
} // namespace Model_Manager

#endif //__MODEL_MANAGER_HPP