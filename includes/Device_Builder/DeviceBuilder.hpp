#ifndef __MODEL_BUILDER_DEVICE_BUILDER_HPP_
#define __MODEL_BUILDER_DEVICE_BUILDER_HPP_

#include "DeviceImplementation.hpp"
#include "Information_Model/DeviceBuilderInterface.hpp"

#include <optional>

namespace Information_Model_Manager {
struct DeviceBuilder : public Information_Model::DeviceBuilderInterface {
  void buildDeviceBase(const std::string& unique_id, const std::string& name,
      const std::string& desc) override;

  std::string addDeviceElementGroup(
      const std::string& name, const std::string& desc) override;

  std::string addDeviceElementGroup(const std::string& group_ref_id,
      const std::string& name, const std::string& desc) override;

  std::string addReadableMetric(const std::string& name,
      const std::string& desc, Information_Model::DataType data_type,
      Information_Model::ReadFunctor read_cb) override;

  std::string addReadableMetric(const std::string& group_ref_id,
      const std::string& name, const std::string& desc,
      Information_Model::DataType data_type,
      Information_Model::ReadFunctor read_cb) override;

  std::string addWritableMetric(const std::string& name,
      const std::string& desc, Information_Model::DataType data_type,
      std::optional<Information_Model::ReadFunctor> read_cb,
      Information_Model::WriteFunctor write_cb) override;

  std::string addWritableMetric(const std::string& group_ref_id,
      const std::string& name, const std::string& desc,
      Information_Model::DataType data_type,
      std::optional<Information_Model::ReadFunctor> read_cb,
      Information_Model::WriteFunctor write_cb) override;

  std::string addDeviceElement(const std::string& group_ref_id,
      const std::string& name, const std::string& desc,
      Information_Model::ElementType type,
      Information_Model::DataType data_type,
      std::optional<Information_Model::ReadFunctor> read_cb,
      std::optional<Information_Model::WriteFunctor> write_cb,
      std::optional<Information_Model::ExecuteFunctor> execute_cb) override;

  Information_Model::UniqueDevicePtr getResult() override;

private:
  using DeviceImplementationPtr = std::unique_ptr<DeviceImplementation>;

  DeviceGroupImplementationPtr getGroupImplementation(
      const std::string& ref_id);
  Information_Model::NonemptyDeviceElementPtr buildDeviceElement(
      const std::string& group_ref_id, const std::string& name,
      const std::string& desc, Information_Model::ElementType type,
      Information_Model::DataType data_type,
      std::optional<Information_Model::ReadFunctor> read_cb,
      std::optional<Information_Model::WriteFunctor> write_cb,
      std::optional<Information_Model::ExecuteFunctor> execute_cb);

  DeviceImplementationPtr device_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_BUILDER_HPP_