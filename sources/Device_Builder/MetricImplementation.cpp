#include "MetricImplementation.hpp"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
MetricImplementation::MetricImplementation()
    : MetricImplementation(DataType::UNKNOWN, nullptr) {}

MetricImplementation::MetricImplementation(
    DataType data_type, function<DataVariant()> read_cb)
    : Metric(), data_type_(data_type), read_cb_(move(read_cb)) {}

DataVariant MetricImplementation::getMetricValue() {
  if (read_cb_) {
    return read_cb_();
  } else {
    auto meta_info = meta_info_.lock();
    if (meta_info)
      throw runtime_error("Readable metric: " + meta_info->getElementName() +
          " " + meta_info->getElementId() +
          "called a nonexistent read function!");
    else
      throw runtime_error(
          "Readable metric called a nonexistent read function!");
  }
}

DataType MetricImplementation::getDataType() { return data_type_; }

void MetricImplementation::linkMetaInfo(
    const NonemptyNamedElementPtr& meta_info) {
  meta_info_ = meta_info.base();
}

} // namespace Information_Model_Manager
