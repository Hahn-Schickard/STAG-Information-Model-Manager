#ifndef __MODEL_BUILDER_METRIC_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_METRIC_IMPLEMENTATION_HPP_

#include "Information_Model/Metric.hpp"
#include "Information_Model/NamedElement.hpp"

#include <functional>

namespace Information_Model_Manager {
class MetricImplementation : public Information_Model::Metric {
  Information_Model::DataType data_type_;
  std::function<Information_Model::DataVariant()> read_cb_;
  std::weak_ptr<Information_Model::NamedElement> meta_info_;

public:
  MetricImplementation();
  MetricImplementation(Information_Model::DataType data_type,
                       std::function<Information_Model::DataVariant()> read_cb);

  Information_Model::DataVariant getMetricValue();
  Information_Model::DataType getDataType();
  void linkMetaInfo(const Information_Model::NonemptyNamedElementPtr &);

friend class WritableMetricImplementation;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_METRIC_IMPLEMENTATION_HPP_