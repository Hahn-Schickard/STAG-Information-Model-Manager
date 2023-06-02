#ifndef __MODEL_BUILDER_WRITABLE_METRIC_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_WRITABLE_METRIC_IMPLEMENTATION_HPP_

#include "Information_Model/WritableMetric.hpp"
#include "MetricImplementation.hpp"

#include <optional>

namespace Information_Model_Manager {

struct WritableMetricImplementation : public Information_Model::WritableMetric,
                                      public MetricImplementation {
  using Writer = std::function<void(Information_Model::DataVariant)>;

  WritableMetricImplementation(
      Information_Model::DataType data_type, Reader read_cb, Writer write_cb);

  void setMetricValue(Information_Model::DataVariant value) override;
  bool isWriteOnly() override;
  // Redeclare overrides, so default Information_Model::WritableMetric
  // implementations are not used instead of MetricImplementation
  Information_Model::DataVariant getMetricValue() override;
  Information_Model::DataType getDataType() override;

private:
  Writer write_cb_;
};

} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_WRITABLE_METRIC_IMPLEMENTATION_HPP_