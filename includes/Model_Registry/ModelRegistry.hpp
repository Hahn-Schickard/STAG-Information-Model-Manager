#ifndef __MODEL_MANAGER_HPP
#define __MODEL_MANAGER_HPP

#include "Data_Consumer_Adapter_Interface/DataConsumerAdapterInterface.hpp"
#include "Event_Model/EventSource.hpp"
#include "Information_Model/Device.hpp"
#include "Technology_Adapter_Interface/ModelRegistryInterface.hpp"

#include <memory>
#include <unordered_map>

namespace Information_Model_Manager {
class ModelRegistry
    : public Technology_Adapter::ModelRegistryInterface,
      public Event_Model::EventSource<DCAI::ModelRegistryEvent> {
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
} // namespace Information_Model_Manager

#endif //__MODEL_MANAGER_HPP