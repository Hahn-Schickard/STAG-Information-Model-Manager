
#ifndef __MODEL_BUILDER_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_IMPLEMENTATION_HPP_

#include <Information_Model/DeviceBuilder.hpp>

#include "DeviceImpl.hpp"

namespace Information_Model_Manager {
struct Builder : public Information_Model::DeviceBuilder {
  using ReadCallback = Information_Model::DeviceBuilder::ReadCallback;
  using WriteCallback = Information_Model::DeviceBuilder::WriteCallback;
  using ExecuteCallback = Information_Model::DeviceBuilder::ExecuteCallback;
  using AsyncExecuteCallback =
      Information_Model::DeviceBuilder::AsyncExecuteCallback;
  using CancelCallback = Information_Model::DeviceBuilder::CancelCallback;
  using NotifyCallback = Information_Model::DeviceBuilder::NotifyCallback;
  using IsObservingCallback =
      Information_Model::DeviceBuilder::IsObservingCallback;

  void setDeviceInfo(const std::string& unique_id,
      const Information_Model::BuildInfo& element_info) final;

  std::string addGroup(const Information_Model::BuildInfo& element_info) final;

  std::string addGroup(const std::string& parent_id,
      const Information_Model::BuildInfo& element_info) final;

  std::string addReadable(const Information_Model::BuildInfo& element_info,
      Information_Model::DataType data_type,
      const ReadCallback& read_cb) final;

  std::string addReadable(const std::string& parent_id,
      const Information_Model::BuildInfo& element_info,
      Information_Model::DataType data_type,
      const ReadCallback& read_cb) final;

  std::string addWritable(const Information_Model::BuildInfo& element_info,
      Information_Model::DataType data_type,
      const WriteCallback& write_cb,
      const ReadCallback& read_cb) final;

  std::string addWritable(const std::string& parent_id,
      const Information_Model::BuildInfo& element_info,
      Information_Model::DataType data_type,
      const WriteCallback& write_cb,
      const ReadCallback& read_cb) final;

  std::pair<std::string, NotifyCallback> addObservable(
      const Information_Model::BuildInfo& element_info,
      Information_Model::DataType data_type,
      const ReadCallback& read_cb,
      const IsObservingCallback& observe_cb) final;

  std::pair<std::string, NotifyCallback> addObservable(
      const std::string& parent_id,
      const Information_Model::BuildInfo& element_info,
      Information_Model::DataType data_type,
      const ReadCallback& read_cb,
      const IsObservingCallback& observe_cb) final;

  std::string addCallable(const Information_Model::BuildInfo& element_info,
      const ExecuteCallback& execute_cb,
      const Information_Model::ParameterTypes& parameter_types) final;

  std::string addCallable(const std::string& parent_id,
      const Information_Model::BuildInfo& element_info,
      const ExecuteCallback& execute_cb,
      const Information_Model::ParameterTypes& parameter_types) final;

  std::string addCallable(const Information_Model::BuildInfo& element_info,
      Information_Model::DataType result_type,
      const ExecuteCallback& execute_cb,
      const AsyncExecuteCallback& async_execute_cb,
      const CancelCallback& cancel_cb,
      const Information_Model::ParameterTypes& parameter_types) final;

  std::string addCallable(const std::string& parent_id,
      const Information_Model::BuildInfo& element_info,
      Information_Model::DataType result_type,
      const ExecuteCallback& execute_cb,
      const AsyncExecuteCallback& async_execute_cb,
      const CancelCallback& cancel_cb,
      const Information_Model::ParameterTypes& parameter_types) final;

  std::unique_ptr<Information_Model::Device> result() final;

private:
  GroupImplPtr getParentGroup(const std::string& parent_id);

  std::string assignID(const std::string& parent_id);

  void makeElementWithId(const std::string& id,
      const Information_Model::BuildInfo& element_info,
      const Information_Model::ElementFunction& function);

  std::string makeElement(const std::string& parent_id,
      const Information_Model::BuildInfo& element_info,
      const Information_Model::ElementFunction& function);

  void checkBase() const;

  void checkGroups() const;

  std::unique_ptr<DeviceImpl> result_;
  std::unordered_map<std::string, GroupImplPtr> subgroups_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_IMPLEMENTATION_HPP_