#ifndef __MODEL_BUILDER_WRITABLE_METRIC_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_WRITABLE_METRIC_IMPLEMENTATION_HPP_

#include "Information_Model/WritableMetric.hpp"
#include "MetricImplementation.hpp"

namespace Information_Model_Manager {

class WritableMetricImplementation : public Information_Model::WritableMetric {
  MetricImplementation readable_part_;
  std::function<void(Information_Model::DataVariant)> write_cb_;
  std::weak_ptr<Information_Model::NamedElement> names_;

public:
  WritableMetricImplementation(
      const std::string &ref_id, const std::string &name,
      const std::string &desc, Information_Model::DataType data_type,
      std::optional<std::function<Information_Model::DataVariant()>> read_cb,
      std::function<void(Information_Model::DataVariant)> write_cb);

  void setMetricValue(Information_Model::DataVariant value);
  Information_Model::DataVariant getMetricValue();
  Information_Model::DataType getDataType();
  void linkNames(const Information_Model::NonemptyNamedElementPtr &);
};

} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_WRITABLE_METRIC_IMPLEMENTATION_HPP_