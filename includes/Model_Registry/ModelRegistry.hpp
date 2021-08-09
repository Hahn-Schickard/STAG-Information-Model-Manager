#ifndef __MODEL_MANAGER_HPP
#define __MODEL_MANAGER_HPP

#include "Data_Consumer_Adapter_Interface/DataConsumerAdapterInterface.hpp"
#include "Event_Model/AsyncEventSource.hpp"
#include "Information_Model/Device.hpp"
#include "Logger.hpp"
#include "Technology_Adapter_Interface/ModelRegistryInterface.hpp"

#include <memory>
#include <unordered_map>

namespace Information_Model_Manager {
class ModelRegistry
    : public Technology_Adapter::ModelRegistryInterface,
      public Event_Model::AsyncEventSource<DCAI::ModelRegistryEvent> {
  using DevicesMap =
      std::unordered_map<std::string,
                         std::shared_ptr<Information_Model::Device>>;
  DevicesMap devices_;
  std::shared_ptr<HaSLL::Logger> logger_;

  bool deviceExists(const std::string &device_id);
  void logException(std::exception_ptr ex_ptr);

public:
  ModelRegistry();
  ~ModelRegistry();

  bool
  registerDevice(std::shared_ptr<Information_Model::Device> device) override;
  bool deregisterDevice(const std::string &device_id) override;
};
} // namespace Information_Model_Manager

#endif //__MODEL_MANAGER_HPP