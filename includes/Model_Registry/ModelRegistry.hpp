#ifndef __MODEL_MANAGER_HPP
#define __MODEL_MANAGER_HPP

#include "Data_Consumer_Adapter_Interface/DataConsumerAdapterInterface.hpp"
#include "Event_Model/AsyncEventSource.hpp"
#include "HaSLL/Logger.hpp"
#include "Information_Model/Device.hpp"
#include "Technology_Adapter_Interface/ModelRegistryInterface.hpp"

#include <memory>
#include <unordered_map>

namespace Information_Model_Manager {
class ModelRegistry
    : public Technology_Adapter::ModelRegistryInterface,
      public Event_Model::AsyncEventSource<DCAI::ModelRegistryEvent> {
  using DevicesMap =
      std::unordered_map<std::string, Information_Model::DevicePtr>;
  DevicesMap devices_;
  HaSLI::LoggerPtr logger_;

  bool deviceExists(const std::string& device_id);
  void logException(std::exception_ptr ex_ptr);

public:
  ModelRegistry();
  ~ModelRegistry();

  bool registerDevice(Information_Model::DevicePtr device) override;
  bool deregisterDevice(const std::string& device_id) override;
};
} // namespace Information_Model_Manager

#endif //__MODEL_MANAGER_HPP