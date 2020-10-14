#include "WritableMetricImplementation.hpp"

#include "exception"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
WritableMetricImplementation::WritableMetricImplementation(
    const string &ref_id, const string &name, const string &desc,
    DataType data_type, function<DataVariant()> read_cb,
    function<void(DataVariant)> write_cb)
    : WritableMetric(ref_id, name, desc),
      readadble_part_(
          MetricImplementation(ref_id, name, desc, data_type, move(read_cb))),
      write_cb_(move(write_cb)) {}

void WritableMetricImplementation::setMetricValue(DataVariant value) {
  if (write_cb_) {
    write_cb_(value);
  } else {
    throw runtime_error("Writable metric: " + getElementName() + " " +
                        getElementId() +
                        "called a non exsistan write function!");
  }
}

DataVariant WritableMetricImplementation::getMetricValue() {
  try {
    return readadble_part_.getMetricValue();
  } catch (exception &e) {
    throw;
  }
}

DataType WritableMetricImplementation::getDataType() {
  return readadble_part_.getDataType();
}
} // namespace Information_Model_Manager