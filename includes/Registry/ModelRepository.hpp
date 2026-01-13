#ifndef __MODEL_REPOSITORY_HPP
#define __MODEL_REPOSITORY_HPP

#include <Data_Consumer_Adapter_Interface/DataConsumerAdapter.hpp>
#include <Event_Model/SourceInterface.hpp>
#include <HaSLL/Logger.hpp>
#include <Information_Model/Device.hpp>
#include <Technology_Adapter_Interface/ModelRepository.hpp>

#include <memory>
#include <unordered_map>

namespace Information_Model_Manager {
struct ModelRepository : public Technology_Adapter::ModelRepository {
  ModelRepository();

  ~ModelRepository() override;

  ModelRepository(const ModelRepository&) = delete;

  ModelRepository(ModelRepository&&) = delete;

  ModelRepository& operator=(const ModelRepository&) = delete;

  ModelRepository& operator=(ModelRepository&&) = delete;

  bool add(const Information_Model::DevicePtr& device) override;

  bool remove(const std::string& device_id) override;

  std::vector<Information_Model::DevicePtr> getModelSnapshot();

  Data_Consumer_Adapter::DataConnector getModelDataConnector();

private:
  void logException(const std::exception_ptr& ex_ptr);

  Data_Consumer_Adapter::DataConnectionPtr connect(
      const Data_Consumer_Adapter::DataNotifier& notifier);

  using RegistryChange = Data_Consumer_Adapter::RegistryChange;
  using EventSourcePtr = Event_Model::SourceInterfacePtr<RegistryChange>;
  using DevicesMap =
      std::unordered_map<std::string, Information_Model::DevicePtr>;

  bool deviceExists(const std::string& device_id);

  HaSLL::LoggerPtr logger_;
  EventSourcePtr source_;
  DevicesMap devices_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_REPOSITORY_HPP