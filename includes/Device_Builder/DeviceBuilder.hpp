#ifndef __MODEL_BUILDER_DEVICE_BUILDER_HPP_
#define __MODEL_BUILDER_DEVICE_BUILDER_HPP_

#include "DeviceBuilderInterface.hpp"
#include "DeviceImplementationBuilder.hpp"

namespace Information_Model_Manager {
class DeviceBuilder : public Information_Model::DeviceBuilderInterface {
  std::unique_ptr<DeviceImplementationBuilder> builder_;

public:
  void buildDeviceBase(const std::string &unique_id, const std::string &name,
                       const std::string &desc) override;

  std::string addDeviceElementGroup(const std::string &name,
                                    const std::string &desc) override;

  std::string addDeviceElementGroup(const std::string &group_refid,
                                    const std::string &name,
                                    const std::string &desc) override;

  std::string
  addReadableMetric(const std::string &name, const std::string &desc,
                    Information_Model::DataType data_type,
                    Information_Model::ReadFunctor read_cb) override;

  std::string
  addReadableMetric(const std::string &group_refid, const std::string &name,
                    const std::string &desc,
                    Information_Model::DataType data_type,
                    Information_Model::ReadFunctor read_cb) override;

  std::string
  addWritableMetric(const std::string &name, const std::string &desc,
                    Information_Model::DataType data_type,
                    std::optional<Information_Model::ReadFunctor> read_cb,
                    Information_Model::WriteFunctor write_cb) override;

  std::string
  addWritableMetric(const std::string &group_refid, const std::string &name,
                    const std::string &desc,
                    Information_Model::DataType data_type,
                    std::optional<Information_Model::ReadFunctor> read_cb,
                    Information_Model::WriteFunctor write_cb) override;

  std::string addDeviceElement(
      const std::string &group_refid, const std::string &name,
      const std::string &desc, Information_Model::ElementType type,
      Information_Model::DataType data_type,
      std::optional<Information_Model::ReadFunctor> read_cb,
      std::optional<Information_Model::WriteFunctor> write_cb) override;

  std::shared_ptr<Information_Model::Device> getResult() override;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_BUILDER_HPP_