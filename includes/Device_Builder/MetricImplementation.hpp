#ifndef __MODEL_BUILDER_METRIC_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_METRIC_IMPLEMENTATION_HPP_

#include "Metric.hpp"

#include <functional>

namespace Information_Model_Manager {
class MetricImplementation : public Information_Model::Metric {
  Information_Model::DataType data_type_;
  std::function<Information_Model::DataVariant()> read_cb_;

public:
  MetricImplementation(const std::string &ref_id, const std::string &name,
                       const std::string &desc,
                       Information_Model::DataType data_type,
                       std::function<Information_Model::DataVariant()> read_cb);

  Information_Model::DataVariant getMetricValue();
  Information_Model::DataType getDataType();
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_METRIC_IMPLEMENTATION_HPP_