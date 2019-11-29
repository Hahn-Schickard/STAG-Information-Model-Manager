#ifndef __MODEL_MANAGER_HPP
#define __MODEL_MANAGER_HPP

#include "Device.hpp"
#include "Notifier.hpp"

#include <memory>
#include <unordered_map>

namespace Model_Manager {
  class ModelManager : public Model_Event_Handler::Notifier {
   public:
    static ModelManager* getInstance();
    bool registerDevice(std::shared_ptr<Information_Model::Device> device);
    bool deregisterDevice(const std::string& DEVICE_ID);
    ~ModelManager();

   private:
    ModelManager();
    bool deviceExists(const std::string& DEVICE_ID);

    std::unordered_map<std::string, std::shared_ptr<Information_Model::Device>>
        devices;

    static ModelManager* instance_;
  };
}   // namespace Model_Manager

#endif   //__MODEL_MANAGER_HPP