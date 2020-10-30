#include "MetricImplementation.hpp"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
MetricImplementation::MetricImplementation()
    : MetricImplementation(string(), string(), string(), DataType::UNKNOWN,
                           nullptr) {}

MetricImplementation::MetricImplementation(const string &ref_id,
                                           const string &name,
                                           const string &desc,
                                           DataType data_type,
                                           function<DataVariant()> read_cb)
    : Metric(ref_id, name, desc), data_type_(data_type),
      read_cb_(move(read_cb)) {}

DataVariant MetricImplementation::getMetricValue() {
  if (read_cb_) {
    return read_cb_();
  } else {
    throw runtime_error("Readable metric: " + getElementName() + " " +
                        getElementId() +
                        "called a non exsistan read function!");
  }
}

DataType MetricImplementation::getDataType() { return data_type_; }
} // namespace Information_Model_Manager