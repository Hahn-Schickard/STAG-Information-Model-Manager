#ifndef __MODEL_BUILDER_DEVICE_ELEMENT_GROUP_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_DEVICE_ELEMENT_GROUP_IMPLEMENTATION_HPP_

#include "DeviceElementGroup.hpp"
#include "MetricImplementation.hpp"
#include "WritableMetricImplementation.hpp"

#include <unordered_map>

namespace Information_Model_Manager {
class DeviceElementGroupImplementation
    : public Information_Model::DeviceElementGroup {
  using DeviceElementsMap =
      std::unordered_map<std::string,
                         std::shared_ptr<Information_Model::DeviceElement>>;

  DeviceElementsMap elements_map_;
  size_t elemenet_count_;

  std::string generate_Reference_ID();

public:
  DeviceElementGroupImplementation(const std::string &ref_id,
                                   const std::string &name,
                                   const std::string &desc);

  std::vector<std::shared_ptr<Information_Model::DeviceElement>>
  getSubelements();

  std::shared_ptr<Information_Model::DeviceElement>
  getSubelement(const std::string &ref_id);

  std::string addSubgroup(const std::string &name, const std::string &desc);

  std::string
  addReadableMetric(const std::string &name, const std::string &desc,
                    Information_Model::DataType data_type,
                    std::function<Information_Model::DataVariant()> read_cb);

  std::string addWritableMetric(
      const std::string &name, const std::string &desc,
      Information_Model::DataType data_type,
      std::function<Information_Model::DataVariant()> read_cb,
      std::function<void(Information_Model::DataVariant)> write_cb);
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_ELEMENT_GROUP_IMPLEMENTATION_HPP_