#include "WritableMetricImplementation.hpp"

#include "exception"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {

WritableMetricImplementation::WritableMetricImplementation(
    DataType data_type, Reader read_cb, Writer write_cb)
    : MetricImplementation(data_type, move(read_cb)),
      write_cb_(move(write_cb)) {}

void WritableMetricImplementation::setMetricValue(DataVariant value) {
  if (write_cb_) {
    write_cb_(value);
  } else {
    throw logic_error(getElementInfo("Writable metric") +
        " metric called a nonexistent write function!");
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