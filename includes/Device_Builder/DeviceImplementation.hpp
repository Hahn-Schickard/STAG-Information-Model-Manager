#ifndef __MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_

#include "Device.hpp"
#include "DeviceElementGroupImplementation.hpp"

#include <memory>

namespace Information_Model_Manager {
class DeviceImplementation : public Information_Model::Device {
  std::shared_ptr<Information_Model::DeviceElementGroup> base_group_;

public:
  DeviceImplementation(const std::string &ref_id, const std::string &name,
                       const std::string &desc);

  std::shared_ptr<Information_Model::DeviceElementGroup>
  getDeviceElementGroup() final;
  std::shared_ptr<Information_Model::DeviceElement>
  getDeviceElement(const std::string &ref_id) final;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_IMPLEMENTATION_HPP_