#ifndef __MODEL_BUILDER_DEVICE_BUILDER_HPP_
#define __MODEL_BUILDER_DEVICE_BUILDER_HPP_

#include "DeviceImplementation.hpp"

#include "HaSLL/Logger.hpp"
#include "Information_Model/DeviceBuilderInterface.hpp"

#include <optional>

namespace Information_Model_Manager {
struct DeviceBuilder : public Information_Model::DeviceBuilderInterface {
  // import interface overloads
  using DeviceBuilderInterface::addDeviceElementGroup;
  using DeviceBuilderInterface::addFunction;
  using DeviceBuilderInterface::addObservableMetric;
  using DeviceBuilderInterface::addReadableMetric;
  using DeviceBuilderInterface::addWritableMetric;

  using ExceptionHandler = std::function<void(const std::exception_ptr&)>;

  DeviceBuilder(
      const ExceptionHandler& ex_handler, const HaSLL::LoggerPtr& logger);

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
      const Reader& read_cb) override;

  std::string addWritableMetric(const std::string& group_ref_id,
      const std::string& name,
      const std::string& desc,
      Information_Model::DataType data_type,
      const Writer& write_cb,
      const Reader& read_cb) override;

  std::pair<std::string, ObservedValue> addObservableMetric(
      const std::string& group_ref_id,
      const std::string& name,
      const std::string& desc,
      Information_Model::DataType data_type,
      const Reader& read_cb,
      const ObserveInitializer& initialized_cb) override;

  std::string addFunction(const std::string& group_ref_id,
      const std::string& name,
      const std::string& desc,
      Information_Model::DataType result_type,
      const Executor& execute_cb,
      const Canceler& cancel_cb,
      const Information_Model::Function::ParameterTypes& supported_params = {})
      override;

  Information_Model::UniqueDevicePtr getResult() override;

private:
  using DeviceImplementationPtr = std::unique_ptr<DeviceImplementation>;

  DeviceGroupImplementationPtr getGroupImplementation(
      const std::string& ref_id);

  Information_Model::DeviceElementPtr addDeviceElement(
      const std::string& group_ref_id,
      const std::string& name,
      const std::string& desc,
      const Functionality& functionality);

  DeviceImplementationPtr device_;
  ExceptionHandler ex_handler_;
  HaSLL::LoggerPtr logger_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_BUILDER_HPP_