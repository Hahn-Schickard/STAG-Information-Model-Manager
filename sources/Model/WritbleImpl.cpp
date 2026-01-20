#include "WritableImpl.hpp"

namespace Information_Model_Manager {
using namespace std;
using namespace Information_Model;

WritableImpl::WritableImpl(DataType type, const WriteCallback& write_cb)
    : WritableImpl(type, nullptr, write_cb) {}

WritableImpl::WritableImpl(
    DataType type, const ReadCallback& read_cb, const WriteCallback& write_cb)
    : type_(type), read_(read_cb), write_(write_cb) {}

DataType WritableImpl::dataType() const { return type_; }

DataVariant WritableImpl::read() const {
  if (!read_) {
    throw NonReadable();
  }
  return read_();
}

bool WritableImpl::isWriteOnly() const { return read_ == nullptr; }

void WritableImpl::write(const DataVariant& value) const { write_(value); }
} // namespace Information_Model_Manager