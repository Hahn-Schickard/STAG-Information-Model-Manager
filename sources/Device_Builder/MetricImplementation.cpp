#include "MetricImplementation.hpp"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
MetricImplementation::MetricImplementation()
    : MetricImplementation(DataType::UNKNOWN, nullptr) {}

MetricImplementation::MetricImplementation(DataType data_type, Reader read_cb)
    : Metric(data_type), read_cb_(move(read_cb)) {}

DataVariant MetricImplementation::getMetricValue() const {
  if (read_cb_) {
    return read_cb_();
  } else {
    throw logic_error(getElementInfo("Readable metric") +
        " metric called a nonexistent read function!");
  }
}

bool MetricImplementation::hasReadCapability() const {
  // Use operator bool, instead of casting to bool
  return read_cb_ ? true : false; // NOLINT(readability-simplify-boolean-expr)
}
} // namespace Information_Model_Manager
