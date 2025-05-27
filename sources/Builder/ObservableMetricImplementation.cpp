#include "ObservableMetricImplementation.hpp"

using namespace std;
using namespace Event_Model;
using namespace Information_Model;

namespace Information_Model_Manager {

ObservableMetricImplementation::ObservableMetricImplementation(
    Information_Model::DataType data_type,
    const ObservableMetric::ExceptionHandler& handler,
    Reader read_cb,
    const ObserveInitializer& observe_cb)
    : ObservableMetric(data_type, handler),
      MetricImplementation(data_type, move(read_cb)), observe_(observe_cb) {}

size_t ObservableMetricImplementation::attach(
    HandleEventCallback<DataVariant>&& listener_callback) {
  bool has_listeners = hasListeners();
  auto listener_id = ObservableMetric::attach(move(listener_callback));
  if (!has_listeners) {
    if (observe_) {
      observe_(true);
    }
  }
  return listener_id;
}

void ObservableMetricImplementation::detach(size_t callback_id) {
  ObservableMetric::detach(callback_id);
  if (!hasListeners()) {
    if (observe_) {
      observe_(false);
    }
  }
}

} // namespace Information_Model_Manager
