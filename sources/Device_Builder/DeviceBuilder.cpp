#include "DeviceBuilder.hpp"
#include "FunctionImplementation.hpp"
#include "MetricImplementation.hpp"
#include "ObservableMetricImplementation.hpp"
#include "WritableMetricImplementation.hpp"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
DeviceBuilder::DeviceBuilder(
    const ExceptionHandler& ex_handler, const HaSLL::LoggerPtr& logger)
    : ex_handler_(ex_handler), logger_(logger) {}

// NOLINTBEGIN(bugprone-easily-swappable-parameters)
void DeviceBuilder::buildDeviceBase(
    const string& unique_id, const string& name, const string& desc) {
  device_ = make_unique<DeviceImplementation>(unique_id, name, desc);
}

string DeviceBuilder::addDeviceElementGroup(
    const string& group_ref_id, const string& name, const string& desc) {
  return addDeviceElement(group_ref_id, name, desc, Functionality())
      ->getElementId();
}

string DeviceBuilder::addReadableMetric(const string& group_ref_id,
    const string& name,
    const string& desc,
    DataType data_type,
    const Reader& read_cb) {
  return addDeviceElement(
      group_ref_id, name, desc, Functionality(data_type, read_cb))
      ->getElementId();
}

string DeviceBuilder::addWritableMetric(const string& group_ref_id,
    const string& name,
    const string& desc,
    DataType data_type,
    const Writer& write_cb,
    const Reader& read_cb) {
  return addDeviceElement(
      group_ref_id, name, desc, Functionality(data_type, read_cb, write_cb))
      ->getElementId();
}

pair<string, DeviceBuilder::ObservedValue> DeviceBuilder::addObservableMetric(
    const string& group_ref_id,
    const string& name,
    const string& desc,
    DataType data_type,
    const Reader& read_cb,
    const ObserveInitializer& initialized_cb) {
  auto element = addDeviceElement(group_ref_id,
      name,
      desc,
      Functionality(data_type, read_cb, initialized_cb));
  auto observable =
      std::get<NonemptyObservableMetricPtr>(element->functionality).base();
  return std::make_pair(element->getElementId(),
      std::bind(
          &ObservableMetric::observed, observable, std::placeholders::_1));
}

string DeviceBuilder::addFunction(const string& group_ref_id,
    const string& name,
    const string& desc,
    DataType result_type,
    const Executor& execute_cb,
    const Canceler& cancel_cb,
    const Function::ParameterTypes& supported_params) {
  return addDeviceElement(group_ref_id,
      name,
      desc,
      Functionality(result_type, execute_cb, cancel_cb, supported_params))
      ->getElementId();
}

DeviceElementPtr DeviceBuilder::addDeviceElement(const string& group_ref_id,
    const string& name,
    const string& desc,
    const Functionality& functionality) {
  auto group = getGroupImplementation(group_ref_id);
  auto ref_id = group->generateReferenceID();
  DeviceElementPtr element;
  switch (functionality.type()) {
  case ElementType::Group: {
    auto sub_group =
        Nonempty::make_shared<DeviceElementGroupImplementation>(ref_id);
    group->addSubgroup(sub_group);
    element = makeDeviceElement(
        ref_id, name, desc, NonemptyDeviceElementGroupPtr(sub_group));
    break;
  }
  case ElementType::Readable: {
    auto read = functionality.getRead();
    auto readable = Nonempty::make_shared<MetricImplementation>(
        functionality.data_type, read.callback);
    NonemptyMetricPtr interface(readable);
    element = makeDeviceElement(ref_id, name, desc, interface);
    readable->linkMetaInfo(NonemptyDeviceElementPtr(element));
    break;
  }
  case ElementType::Writable: {
    auto write = functionality.getWrite();
    auto writable = Nonempty::make_shared<WritableMetricImplementation>(
        functionality.data_type, write.read_part.callback, write.callback);
    NonemptyWritableMetricPtr interface(writable);
    element = makeDeviceElement(ref_id, name, desc, interface);
    writable->linkMetaInfo(NonemptyDeviceElementPtr(element));
    break;
  }
  case ElementType::Executable: {
    auto execute = functionality.getExecute();
    auto executable = Nonempty::make_shared<FunctionImplementation>(logger_,
        functionality.data_type,
        execute.supported_params,
        execute.call,
        execute.cancel);
    NonemptyFunctionPtr interface(executable);
    element = makeDeviceElement(ref_id, name, desc, interface);
    executable->linkMetaInfo(NonemptyDeviceElementPtr(element));
    break;
  }
  case ElementType::Observable: {
    auto observe = functionality.getObserve();
    auto observable = Nonempty::make_shared<ObservableMetricImplementation>(
        functionality.data_type,
        ex_handler_,
        observe.read_part.callback,
        observe.callback);
    NonemptyObservableMetricPtr interface(observable);
    element = makeDeviceElement(ref_id, name, desc, interface);
    observable->linkMetaInfo(NonemptyDeviceElementPtr(element));
  }
  default: {
    throw invalid_argument("Requested to build unsupported ElementType");
  }
  }
  group->addDeviceElement(NonemptyDeviceElementPtr(element));

  return element;
}
// NOLINTEND(bugprone-easily-swappable-parameters)

Information_Model::UniqueDevicePtr DeviceBuilder::getResult() {
  return move(device_);
}

DeviceGroupImplementationPtr DeviceBuilder::getGroupImplementation(
    const string& ref_id) {
  if (ref_id.empty()) {
    return device_->getGroupImplementation().base();
  } else {
    return device_->getGroupImplementation()->getSubgroupImplementation(ref_id);
  }
}
} // namespace Information_Model_Manager