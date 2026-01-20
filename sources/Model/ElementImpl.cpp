#include "ElementImpl.hpp"

namespace Information_Model_Manager {
using namespace std;
using namespace Information_Model;

ElementImpl::ElementImpl(
    const string& id, const BuildInfo& meta, const ElementFunction& function)
    : FullMetaInfo(id, meta), function_(function) {}

ElementType ElementImpl::type() const {
  if (holds_alternative<GroupPtr>(function_)) {
    return ElementType::Group;
  } else if (holds_alternative<ReadablePtr>(function_)) {
    return ElementType::Readable;
  } else if (holds_alternative<WritablePtr>(function_)) {
    return ElementType::Writable;
  } else if (holds_alternative<ObservablePtr>(function_)) {
    return ElementType::Observable;
  } else if (holds_alternative<CallablePtr>(function_)) {
    return ElementType::Callable;
  } else {
    throw runtime_error(
        "Unknown functionality for " + id() + " " + name() + " ElementImpl");
  }
}

ElementFunction ElementImpl::function() const { return function_; }

} // namespace Information_Model_Manager