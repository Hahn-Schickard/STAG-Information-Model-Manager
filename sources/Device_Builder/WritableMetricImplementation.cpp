#include "WritableMetricImplementation.hpp"

#include "exception"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {

WritableMetricImplementation::WritableMetricImplementation(
    DataType data_type, optional<Reader> read_cb, Writer write_cb)
    : MetricImplementation(data_type, read_cb.value_or(nullptr)),
      write_cb_(move(write_cb)) {}

void WritableMetricImplementation::setMetricValue(DataVariant value) {
  if (write_cb_) {
    write_cb_(value);
  } else {
    auto meta_info = meta_info_.lock();
    if (meta_info) {
      throw runtime_error("Writable metric: " + meta_info->getElementName() +
          " " + meta_info->getElementId() +
          "called a nonexistent write function!");
    } else {
      throw runtime_error(
          "Writable metric called a nonexistent write function!");
    }
  }
}

bool WritableMetricImplementation::isWriteOnly() {
  return !hasReadCapability();
}

// Point redeclarations to real implementation in MetricImplementation
DataVariant WritableMetricImplementation::getMetricValue() {
  return MetricImplementation::getMetricValue();
}

DataType WritableMetricImplementation::getDataType() {
  return MetricImplementation::getDataType();
}

} // namespace Information_Model_Manager