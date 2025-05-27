#ifndef __MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_

#include "DeviceElementGroupImplementation.hpp"
#include "Information_Model/Device.hpp"

#include <memory>

namespace Information_Model_Manager {
struct DeviceImplementation : public Information_Model::Device {
  using DeviceGroupImplementation =
      Nonempty::Pointer<std::shared_ptr<DeviceElementGroupImplementation>>;

  DeviceImplementation(const std::string& ref_id,
      const std::string& name,
      const std::string& desc);

  Information_Model::NonemptyDeviceElementGroupPtr
  getDeviceElementGroup() const final;
  DeviceGroupImplementation getGroupImplementation();
  Information_Model::NonemptyDeviceElementPtr getDeviceElement(
      const std::string& ref_id) const final;

private:
  DeviceGroupImplementation base_group_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_