#include "ReadableImpl.hpp"

namespace Information_Model_Manager {
using namespace std;
using namespace Information_Model;

ReadableImpl::ReadableImpl(DataType type, const ReadCallback& read_cb)
    : type_(type), read_(read_cb) {
  if (!read_) {
    throw invalid_argument(
        "ReadableImpl element must have a valid, non empty read callback");
  }
}

DataType ReadableImpl::dataType() const { return type_; }

DataVariant ReadableImpl::read() const { return read_(); }

} // namespace Information_Model_Manager