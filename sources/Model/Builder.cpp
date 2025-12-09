#include "Builder.hpp"

#include "CallableImpl.hpp"
#include "ElementImpl.hpp"
#include "GroupImpl.hpp"
#include "ObservableImpl.hpp"
#include "ReadableImpl.hpp"
#include "WritableImpl.hpp"

namespace Information_Model_Manager {
using namespace std;
using namespace Information_Model;

void Builder::setDeviceInfo(
    const string& unique_id, const BuildInfo& element_info) {
  if (!result_) {
    result_ = make_unique<DeviceImpl>(unique_id, element_info);
  } else {
    throw DeviceBuildInProgress();
  }
}

string Builder::addGroup(const BuildInfo& element_info) {
  return addGroup("", element_info);
}

string Builder::addGroup(
    const string& parent_id, const BuildInfo& element_info) {
  checkBase();

  auto id = assignID(parent_id);
  auto group = make_shared<GroupImpl>(id);
  subgroups_.try_emplace(id, group);
  makeElementWithId(id, element_info, group);
  return id;
}

string Builder::addReadable(const BuildInfo& element_info,
    DataType data_type,
    const ReadCallback& read_cb) {
  return addReadable("", element_info, data_type, read_cb);
}

string Builder::addReadable(const string& parent_id,
    const BuildInfo& element_info,
    DataType data_type,
    const ReadCallback& read_cb) {
  if (data_type == DataType::None || data_type == DataType::Unknown) {
    throw invalid_argument("Data Type can not be None or Unknown");
  }
  if (!read_cb) {
    throw invalid_argument("ReadCallback can not be nullptr");
  }

  auto readable = make_shared<ReadableImpl>(data_type, read_cb);
  return makeElement(parent_id, element_info, readable);
}

string Builder::addWritable(const BuildInfo& element_info,
    DataType data_type,
    const WriteCallback& write_cb,
    const ReadCallback& read_cb) {
  return addWritable("", element_info, data_type, write_cb, read_cb);
}

string Builder::addWritable(const string& parent_id,
    const BuildInfo& element_info,
    DataType data_type,
    const WriteCallback& write_cb,
    const ReadCallback& read_cb) {
  if (data_type == DataType::None || data_type == DataType::Unknown) {
    throw invalid_argument("Data Type can not be None or Unknown");
  }
  if (!write_cb) {
    throw invalid_argument("WriteCallback can not be nullptr");
  }

  auto writable = make_shared<WritableImpl>(data_type, read_cb, write_cb);
  return makeElement(parent_id, element_info, writable);
}

pair<string, Builder::NotifyCallback> Builder::addObservable(
    const BuildInfo& element_info,
    DataType data_type,
    const ReadCallback& read_cb,
    const IsObservingCallback& observe_cb) {
  return addObservable("", element_info, data_type, read_cb, observe_cb);
}

pair<string, Builder::NotifyCallback> Builder::addObservable(
    const string& parent_id,
    const BuildInfo& element_info,
    DataType data_type,
    const ReadCallback& read_cb,
    const IsObservingCallback& observe_cb) {
  if (data_type == DataType::None || data_type == DataType::Unknown) {
    throw invalid_argument("Data Type can not be None or Unknown");
  }
  if (!read_cb) {
    throw invalid_argument("ReadCallback can not be nullptr");
  }
  if (!observe_cb) {
    throw invalid_argument("IsObservingCallback can not be nullptr");
  }

  auto observable = make_shared<ObservableImpl>(data_type, read_cb, observe_cb);
  auto id = makeElement(parent_id, element_info, observable);

  return make_pair(
      id, bind(&ObservableImpl::notify, observable, placeholders::_1));
}

string Builder::addCallable(const BuildInfo& element_info,
    const ExecuteCallback& execute_cb,
    const ParameterTypes& parameter_types) {
  return addCallable("", element_info, execute_cb, parameter_types);
}

string Builder::addCallable(const string& parent_id,
    const BuildInfo& element_info,
    const ExecuteCallback& execute_cb,
    const ParameterTypes& parameter_types) {
  if (!execute_cb) {
    throw invalid_argument("ExecuteCallback can not be nullptr");
  }

  auto callable = make_shared<CallableImpl>(parameter_types, execute_cb);
  return makeElement(parent_id, element_info, callable);
}

string Builder::addCallable(const BuildInfo& element_info,
    DataType result_type,
    const ExecuteCallback& execute_cb,
    const AsyncExecuteCallback& async_execute_cb,
    const CancelCallback& cancel_cb,
    const ParameterTypes& parameter_types) {
  return addCallable("",
      element_info,
      result_type,
      execute_cb,
      async_execute_cb,
      cancel_cb,
      parameter_types);
}

string Builder::addCallable(const string& parent_id,
    const BuildInfo& element_info,
    DataType result_type,
    const ExecuteCallback& execute_cb,
    const AsyncExecuteCallback& async_execute_cb,
    const CancelCallback& cancel_cb,
    const ParameterTypes& parameter_types) {
  if (result_type == DataType::None || result_type == DataType::Unknown) {
    throw invalid_argument("Result Type can not be None or Unknown");
  }
  if (!execute_cb) {
    throw invalid_argument("ExecuteCallback can not be nullptr");
  }
  if (!async_execute_cb) {
    throw invalid_argument("AsyncExecuteCallback can not be nullptr");
  }
  if (!cancel_cb) {
    throw invalid_argument("CancelCallback can not be nullptr");
  }

  auto callable = make_shared<CallableImpl>(
      result_type, parameter_types, execute_cb, async_execute_cb, cancel_cb);
  return makeElement(parent_id, element_info, callable);
}

unique_ptr<Device> Builder::result() {
  checkBase();
  checkGroups();
  subgroups_.clear();
  return move(result_);
}

GroupImplPtr Builder::getParentGroup(const string& parent_id) {
  if (auto it = subgroups_.find(parent_id); it != subgroups_.end()) {
    return it->second;
  } else {
    throw invalid_argument("No parent group with ID " + parent_id +
        " exists. Build parent group first");
  }
}

string Builder::assignID(const string& parent_id) {
  if (parent_id.empty()) {
    return result_->generateID();
  } else {
    auto subgroup = getParentGroup(parent_id);
    return subgroup->generateID();
  }
}

void Builder::makeElementWithId(const string& id,
    const BuildInfo& element_info,
    const ElementFunction& function) {
  auto element = make_shared<ElementImpl>(id, element_info, function);
  result_->addElement(element);
}

string Builder::makeElement(const string& parent_id,
    const BuildInfo& element_info,
    const ElementFunction& function) {
  checkBase();

  auto id = assignID(parent_id);
  makeElementWithId(id, element_info, function);
  return id;
}

void Builder::checkBase() const {
  if (!result_) {
    throw DeviceInfoNotSet();
  }
}

void Builder::checkGroups() const {
  if (result_->group()->size() == 0) {
    throw GroupEmpty(result_->id());
  }
  for (const auto& [id, group] : subgroups_) {
    if (group->size() == 0) {
      throw GroupEmpty(result_->id(), id);
    }
  }
}

} // namespace Information_Model_Manager