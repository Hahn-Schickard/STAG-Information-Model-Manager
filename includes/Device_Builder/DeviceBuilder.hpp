#ifndef __MODEL_BUILDER_DEVICE_BUILDER_HPP_
#define __MODEL_BUILDER_DEVICE_BUILDER_HPP_

#include "DeviceImplementation.hpp"
#include "Information_Model/DeviceBuilderInterface.hpp"

#include <optional>

namespace Information_Model_Manager {
struct DeviceBuilder : public Information_Model::DeviceBuilderInterface {
  // import interface overloads
  using DeviceBuilderInterface::addDeviceElementGroup;
  using DeviceBuilderInterface::addFunction;
  using DeviceBuilderInterface::addReadableMetric;
  using DeviceBuilderInterface::addWritableMetric;

  void buildDeviceBase(const std::string& unique_id, const std::string& name,
      const std::string& desc) override;

  std::string addDeviceElementGroup(const std::string& group_ref_id,
      const std::string& name, const std::string& desc) override;

  std::string addReadableMetric(const std::string& group_ref_id,
      const std::string& name, const std::string& desc,
      Information_Model::DataType data_type, Reader read_cb) override;

  std::string addWritableMetric(const std::string& group_ref_id,
      const std::string& name, const std::string& desc,
      Information_Model::DataType data_type, Writer write_cb,
      Reader read_cb) override;

  Information_Model::UniqueDevicePtr getResult() override;

private:
  using DeviceImplementationPtr = std::unique_ptr<DeviceImplementation>;

  DeviceGroupImplementationPtr getGroupImplementation(
      const std::string& ref_id);

  std::string addDeviceElement(const std::string& group_ref_id,
      const std::string& name, const std::string& desc,
      const Functionality& functionality);

  DeviceImplementationPtr device_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_BUILDER_HPP_