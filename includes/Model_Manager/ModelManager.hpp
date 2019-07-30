#ifndef __MODEL_MANAGER_HPP
#define __MODEL_MANAGER_HPP

#include "Device.hpp"
#include "Notifier.hpp"
#include <memory>
#include <unordered_map>

namespace Model_Manager {
class ModelManager : Notifier::Notifier {
public:
  void register_device(std::unique_ptr<Information_Model::Device> device);

private:
  std::unordered_map<std::string, Information_Model::Device *> devices;
};
}

#endif //__MODEL_MANAGER_HPP