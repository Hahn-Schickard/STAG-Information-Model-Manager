#include "WritableMetricImplementation.hpp"

#include "exception"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
WritableMetricImplementation::WritableMetricImplementation(
    const string &ref_id, const string &name, const string &desc,
    DataType data_type, optional<function<DataVariant()>> read_cb,
    function<void(DataVariant)> write_cb)
    : WritableMetric(ref_id, name, desc), write_cb_(move(write_cb)) {
  if (read_cb.has_value()) {
    readadble_part_ = MetricImplementation(ref_id, name, desc, data_type,
                                           move(read_cb.value()));
  } else {
    DataVariant value;
    switch (data_type) {
    case DataType::BOOLEAN: {
      value = (bool)true;
      break;
    }
    case DataType::INTEGER: {
      value = (int64_t)0;
      break;
    }
    case DataType::UNSIGNED_INTEGER: {
      value = (uint64_t)0;
      break;
    }
    case DataType::DOUBLE: {
      value = (double)0;
      break;
    }
    case DataType::OPAQUE: {
      value = vector<uint8_t>();
      break;
    }
    case DataType::STRING: {
      value = string();
      break;
    }
    case DataType::UNKNOWN:
    default: {
      throw runtime_error("Writable metric must have a known data type!");
    }
    }
    readadble_part_ = MetricImplementation(
        ref_id, name, desc, data_type, [&]() -> DataVariant { return value; });
  }
}

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