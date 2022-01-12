#ifndef __MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_

#include "DeviceElementGroupImplementation.hpp"
#include "Information_Model/Device.hpp"

#include <memory>

namespace Information_Model_Manager {
class DeviceImplementation : public Information_Model::Device {
public:
  using DeviceGroupImplementation = NonemptyPointer::NonemptyPtr<
    std::shared_ptr<DeviceElementGroupImplementation>>;

private:
  DeviceGroupImplementation base_group_;

public:
  DeviceImplementation(const std::string &ref_id, const std::string &name,
                       const std::string &desc);

  Information_Model::NonemptyDeviceElementGroupPtr getDeviceElementGroup() final;
  DeviceGroupImplementation getGroupImplementation();
  std::shared_ptr<Information_Model::DeviceElement>
  getDeviceElement(const std::string &ref_id) final;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_