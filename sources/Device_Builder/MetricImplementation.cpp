#include "MetricImplementation.hpp"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
MetricImplementation::MetricImplementation()
    : MetricImplementation(DataType::UNKNOWN, nullptr) {}

MetricImplementation::MetricImplementation(DataType data_type, Reader read_cb)
    : data_type_(data_type), read_cb_(move(read_cb)) {}

DataVariant MetricImplementation::getMetricValue() {
  if (read_cb_) {
    return read_cb_();
  } else {
    throw logic_error(getElementInfo("Readable metric") +
        " metric called a nonexistent read function!");
  }
}

bool MetricImplementation::hasReadCapability() {
  // Use operator bool, instead of casting to bool
  return read_cb_ ? true : false; // NOLINT(readability-simplify-boolean-expr)
}

DataType MetricImplementation::getDataType() { return data_type_; }
} // namespace Information_Model_Manager
