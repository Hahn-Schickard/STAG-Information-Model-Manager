#ifndef __MODEL_BUILDER_DEVICE_IMPLEMENTATION_BUILDER_HPP_
#define __MODEL_BUILDER_DEVICE_IMPLEMENTATION_BUILDER_HPP_

#include "DeviceElementGroupImplementation.hpp"
#include "DeviceImplementation.hpp"

#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace Information_Model_Manager {
class DeviceImplementationBuilder {
  using DeviceImplementationPtr = std::shared_ptr<DeviceImplementation>;
  using DeviceGroupImplementation =
      std::shared_ptr<DeviceElementGroupImplementation>;

  DeviceImplementationPtr device_;

  DeviceGroupImplementation getGroupImplementation(const std::string &ref_id);

public:
  using ReadFunctor = std::function<Information_Model::DataVariant()>;
  using WriteFunctor = std::function<void(Information_Model::DataVariant)>;

  DeviceImplementationBuilder(const std::string &ref_id,
                              const std::string &name, const std::string &desc);

  std::string addDeviceElementGroup(const std::string &name,
                                    const std::string &desc);

  std::string addDeviceElementGroup(const std::string &group_refid,
                                    const std::string &name,
                                    const std::string &desc);

  std::string addReadableMetric(const std::string &name,
                                const std::string &desc,
                                Information_Model::DataType data_type,
                                ReadFunctor read_cb);

  std::string addReadableMetric(const std::string &group_refid,
                                const std::string &name,
                                const std::string &desc,
                                Information_Model::DataType data_type,
                                ReadFunctor read_cb);

  std::string addWritableMetric(const std::string &name,
                                const std::string &desc,
                                Information_Model::DataType data_type,
                                std::optional<ReadFunctor> read_cb,
                                WriteFunctor write_cb);

  std::string addWritableMetric(const std::string &group_refid,
                                const std::string &name,
                                const std::string &desc,
                                Information_Model::DataType data_type,
                                std::optional<ReadFunctor> read_cb,
                                WriteFunctor write_cb);

  std::string addDeviceElement(const std::string &group_refid,
                               const std::string &name, const std::string &desc,
                               Information_Model::ElementType type,
                               Information_Model::DataType data_type,
                               std::optional<ReadFunctor> read_cb,
                               std::optional<WriteFunctor> write_cb);

  std::shared_ptr<Information_Model::Device> getResult();
};

} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_IMPLEMENTATION_BUILDER_HPP_