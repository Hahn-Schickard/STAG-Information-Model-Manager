#ifndef __MODEL_BUILDER_OBSERVABLE_METRIC_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_OBSERVABLE_METRIC_IMPLEMENTATION_HPP_

#include "Information_Model/ObservableMetric.hpp"
#include "MetricImplementation.hpp"

namespace Information_Model_Manager {

struct ObservableMetricImplementation
    : public Information_Model::ObservableMetric,
      public MetricImplementation {
  using ObserveInitializer = std::function<void(bool)>;

  ObservableMetricImplementation(Information_Model::DataType data_type,
      const ObservableMetric::ExceptionHandler& handler,
      Reader read_cb,
      const ObserveInitializer& observe_cb);

private:
  std::size_t attach(
      Event_Model::HandleEventCallback<Information_Model::DataVariant>&&
          listener_callback) final;
  void detach(std::size_t callback_id) final;

  ObserveInitializer observe_;
};

} // namespace Information_Model_Manager
#endif //__MODEL_BUILDER_OBSERVABLE_METRIC_IMPLEMENTATION_HPP_