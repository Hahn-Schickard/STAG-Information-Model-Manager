#ifndef __MODEL_BUILDER_METRIC_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_METRIC_IMPLEMENTATION_HPP_

#include "Information_Model/Metric.hpp"
#include "Information_Model/NamedElement.hpp"

#include <functional>

namespace Information_Model_Manager {
struct MetricImplementation : public Information_Model::Metric {
  using Reader = std::function<Information_Model::DataVariant()>;

  MetricImplementation();
  MetricImplementation(Information_Model::DataType data_type, Reader read_cb);

  Information_Model::DataVariant getMetricValue() override;
  Information_Model::DataType getDataType() override;
  void linkMetaInfo(const Information_Model::NonemptyNamedElementPtr&);

protected:
  Information_Model::DataType data_type_;
  Reader read_cb_;
  std::weak_ptr<Information_Model::NamedElement> meta_info_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_METRIC_IMPLEMENTATION_HPP_