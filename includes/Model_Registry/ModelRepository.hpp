#ifndef __MODEL_MANAGER_HPP
#define __MODEL_MANAGER_HPP

#include "Data_Consumer_Adapter_Interface/DataConsumerAdapterInterface.hpp"
#include "Event_Model/AsyncEventSource.hpp"
#include "HaSLL/Logger.hpp"
#include "Information_Model/Device.hpp"
#include "Technology_Adapter_Interface/ModelRepositoryInterface.hpp"

#include <memory>
#include <unordered_map>

namespace Information_Model_Manager {
class ModelRepository : public Technology_Adapter::ModelRepositoryInterface,
                        public Event_Model::AsyncEventSource<
                            Data_Consumer_Adapter::ModelRepositoryEvent> {
  using DevicesMap =
      std::unordered_map<std::string, Information_Model::NonemptyDevicePtr>;
  DevicesMap devices_;
  HaSLL::LoggerPtr logger_;

  bool deviceExists(const std::string& device_id);

public:
  ModelRepository();

  void logException(const std::exception_ptr& ex_ptr);
  bool add(const Information_Model::NonemptyDevicePtr& device) override;
  bool remove(const std::string& device_id) override;
  std::vector<Information_Model::DevicePtr> getModelSnapshot();
};
} // namespace Information_Model_Manager

#endif //__MODEL_MANAGER_HPP