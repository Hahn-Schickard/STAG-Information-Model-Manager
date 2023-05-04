#ifndef __MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_

#include "DeviceElementGroupImplementation.hpp"
#include "Information_Model/Device.hpp"

#include <memory>

namespace Information_Model_Manager {
struct DeviceImplementation : public Information_Model::Device {
  using DeviceGroupImplementation = NonemptyPointer::NonemptyPtr<
      std::shared_ptr<DeviceElementGroupImplementation>>;

  DeviceImplementation(const std::string& ref_id, const std::string& name,
      const std::string& desc);

  Information_Model::NonemptyDeviceElementGroupPtr
  getDeviceElementGroup() final;
  DeviceGroupImplementation getGroupImplementation();
  Information_Model::DeviceElementPtr getDeviceElement(
      const std::string& ref_id) final;

private:
  DeviceGroupImplementation base_group_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_