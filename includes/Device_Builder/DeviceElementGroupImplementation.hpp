#ifndef __MODEL_BUILDER_DEVICE_ELEMENT_GROUP_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_DEVICE_ELEMENT_GROUP_IMPLEMENTATION_HPP_

#include "Information_Model/DeviceElement.hpp"
#include "Information_Model/DeviceElementGroup.hpp"

#include <optional>
#include <unordered_map>

namespace Information_Model_Manager {
struct DeviceElementGroupImplementation
    : public Information_Model::DeviceElementGroup {
  DeviceElementGroupImplementation(const std::string& base_ref_id);

  std::vector<Information_Model::NonemptyDeviceElementPtr> getSubelements();

  std::shared_ptr<Information_Model::DeviceElement> getSubelement(
      const std::string& ref_id);

private:
  using DeviceElementsMap = std::unordered_map<std::string,
      Information_Model::NonemptyDeviceElementPtr>;
  using NonemptyDeviceElementGroupImplementationPtr =
      NonemptyPointer::NonemptyPtr<
          std::shared_ptr<DeviceElementGroupImplementation>>;
  using SubgroupsMap = std::unordered_map<std::string,
      NonemptyDeviceElementGroupImplementationPtr>;

  std::string generateReferenceID();
  void addSubgroup(NonemptyDeviceElementGroupImplementationPtr group);
  void addDeviceElement(Information_Model::NonemptyDeviceElementPtr element);
  std::shared_ptr<DeviceElementGroupImplementation> getSubgroupImplementation(
      const std::string& ref_id);

  DeviceElementsMap elements_map_;
  SubgroupsMap subgroups_map_;
  size_t element_count_;
  std::string base_ref_id_;

  friend struct DeviceBuilder;
};
using DeviceGroupImplementationPtr =
    std::shared_ptr<DeviceElementGroupImplementation>;
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_ELEMENT_GROUP_IMPLEMENTATION_HPP_