#ifndef __MODEL_BUILDER_DEVICE_BUILDER_HPP_
#define __MODEL_BUILDER_DEVICE_BUILDER_HPP_

#include "DeviceImplementation.hpp"

#include "HaSLL/Logger.hpp"
#include "Information_Model/DeviceBuilderInterface.hpp"

#include <exception>
#include <mutex>
#include <optional>

namespace Information_Model_Manager {
struct DeviceBuilder : public Information_Model::DeviceBuilderInterface {
  // import interface overloads
  using DeviceBuilderInterface::addDeviceElementGroup;
  using DeviceBuilderInterface::addFunction;
  using DeviceBuilderInterface::addReadableMetric;
  using DeviceBuilderInterface::addWritableMetric;

  DeviceBuilder(const HaSLI::LoggerPtr& logger);

  void buildDeviceBase(const std::string& unique_id,
      const std::string& name,
      const std::string& desc) override;

  std::string addDeviceElementGroup(const std::string& group_ref_id,
      const std::string& name,
      const std::string& desc) override;

  std::string addReadableMetric(const std::string& group_ref_id,
      const std::string& name,
      const std::string& desc,
      Information_Model::DataType data_type,
      Reader read_cb) override;

  std::string addWritableMetric(const std::string& group_ref_id,
      const std::string& name,
      const std::string& desc,
      Information_Model::DataType data_type,
      Writer write_cb,
      Reader read_cb) override;

  std::string addObservableMetric(const std::string& group_ref_id,
      const std::string& name,
      const std::string& desc,
      Information_Model::DataType data_type) override;

  std::string addFunction(const std::string& group_ref_id,
      const std::string& name,
      const std::string& desc,
      Information_Model::DataType result_type,
      Executor execute_cb,
      Canceler cancel_cb,
      Information_Model::Function::ParameterTypes supported_params = {})
      override;

  Information_Model::UniqueDevicePtr getResult() override;

private:
  using DeviceImplementationPtr = std::unique_ptr<DeviceImplementation>;

  DeviceGroupImplementationPtr getGroupImplementation(
      const std::string& ref_id);

  std::string addDeviceElement(const std::string& group_ref_id,
      const std::string& name,
      const std::string& desc,
      const Functionality& functionality);

  void handleException(
      const std::string& element_info, const std::exception_ptr& e_ptr);

  DeviceImplementationPtr device_;
  std::mutex handle_exception_mx_;
  HaSLI::LoggerPtr logger_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_BUILDER_HPP_