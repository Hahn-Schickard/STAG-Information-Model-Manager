#include "WritableMetricImplementation.hpp"

#include "exception"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
WritableMetricImplementation::WritableMetricImplementation(
    const string &ref_id, const string &name, const string &desc,
    DataType data_type, optional<function<DataVariant()>> read_cb,
    function<void(DataVariant)> write_cb)
    : WritableMetric(), write_cb_(move(write_cb)) {
  if (read_cb.has_value()) {
    readable_part_ = MetricImplementation(ref_id, name, desc, data_type,
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
    readable_part_ = MetricImplementation(
        ref_id, name, desc, data_type, [&]() -> DataVariant { return value; });
  }
}

void WritableMetricImplementation::setMetricValue(DataVariant value) {
  if (write_cb_) {
    write_cb_(value);
  } else {
    auto names = names_.lock();
    if (names)
      throw runtime_error("Writable metric: " + names->getElementName() + " " +
                          names->getElementId() +
                          "called a nonexistent write function!");
    else
      throw runtime_error("Writable metric called a nonexistent write function!");
  }
}

DataVariant WritableMetricImplementation::getMetricValue() {
  try {
    return readable_part_.getMetricValue();
  } catch (exception &e) {
    throw;
  }
}

DataType WritableMetricImplementation::getDataType() {
  return readable_part_.getDataType();
}

void WritableMetricImplementation::linkNames(
  const NonemptyNamedElementPtr & names)
{
  names_ = names.base();
}

} // namespace Information_Model_Manager