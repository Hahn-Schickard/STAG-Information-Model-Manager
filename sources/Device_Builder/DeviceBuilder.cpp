#include "DeviceBuilder.hpp"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
void DeviceBuilder::buildDeviceBase(
    const string& unique_id, const string& name, const string& desc) {
  device_ = make_unique<DeviceImplementation>(unique_id, name, desc);
}

string DeviceBuilder::addDeviceElementGroup(
    const string& name, const string& desc) {
  return addDeviceElement(string(), name, desc, ElementType::GROUP,
      DataType::UNKNOWN, std::nullopt, std::nullopt, std::nullopt);
}

string DeviceBuilder::addDeviceElementGroup(
    const string& group_ref_id, const string& name, const string& desc) {
  return addDeviceElement(group_ref_id, name, desc, ElementType::GROUP,
      DataType::UNKNOWN, std::nullopt, std::nullopt, std::nullopt);
}

string DeviceBuilder::addReadableMetric(const string& name, const string& desc,
    DataType data_type, ReadFunctor read_cb) {
  return addDeviceElement(string(), name, desc, ElementType::READABLE,
      data_type, move(read_cb), std::nullopt, std::nullopt);
}

string DeviceBuilder::addReadableMetric(const string& group_ref_id,
    const string& name, const string& desc, DataType data_type,
    ReadFunctor read_cb) {
  return addDeviceElement(group_ref_id, name, desc, ElementType::READABLE,
      data_type, move(read_cb), std::nullopt, std::nullopt);
}

string DeviceBuilder::addWritableMetric(const string& name, const string& desc,
    DataType data_type, std::optional<ReadFunctor> read_cb,
    WriteFunctor write_cb) {
  return addDeviceElement(string(), name, desc, ElementType::WRITABLE,
      data_type, move(read_cb), move(write_cb), std::nullopt);
}

string DeviceBuilder::addWritableMetric(const string& group_ref_id,
    const string& name, const string& desc, DataType data_type,
    std::optional<ReadFunctor> read_cb, WriteFunctor write_cb) {
  return addDeviceElement(group_ref_id, name, desc, ElementType::WRITABLE,
      data_type, move(read_cb), move(write_cb), std::nullopt);
}

template <class T> T setCallback(optional<T> optional_value) {
  if (optional_value.has_value()) {
    return optional_value.value();
  } else {
    return T();
  }
}

string DeviceBuilder::addDeviceElement(const string& group_ref_id,
    const string& name, const string& desc, Information_Model::ElementType type,
    Information_Model::DataType data_type,
    std::optional<Information_Model::ReadFunctor> read_cb,
    std::optional<Information_Model::WriteFunctor> write_cb,
    std::optional<Information_Model::ExecuteFunctor> execute_cb) {
  auto group = getGroupImplementation(group_ref_id);
  auto new_id = group->generateReferenceID();

  Information_Model::DeviceElementPtr element;
  switch (type) {
  case ElementType::GROUP: {
    auto sub_group =
        NonemptyPointer::make_shared<DeviceElementGroupImplementation>(new_id);
    group->addSubgroup(sub_group);
    element = makeDeviceElement(
        new_id, name, desc, NonemptyDeviceElementGroupPtr(sub_group));
    break;
  }
  case ElementType::WRITABLE: {
    auto implementation =
        NonemptyPointer::make_shared<WritableMetricImplementation>(data_type,
            setCallback<ReadFunctor>(move(read_cb)),
            setCallback<WriteFunctor>(move(write_cb)));
    NonemptyWritableMetricPtr interface(implementation);
    element = makeDeviceElement(new_id, name, desc, interface);
    implementation->linkMetaInfo(NonemptyDeviceElementPtr(element));
    break;
  }
  case ElementType::READABLE: {
    auto implementation = NonemptyPointer::make_shared<MetricImplementation>(
        data_type, setCallback<ReadFunctor>(move(read_cb)));
    NonemptyMetricPtr interface(implementation);
    element = makeDeviceElement(new_id, name, desc, interface);
    implementation->linkMetaInfo(NonemptyDeviceElementPtr(element));
    break;
  }
  case ElementType::FUNCTION: {
    // @TODO: implement function support
    __attribute__((unused)) auto suppress = execute_cb;
    throw std::invalid_argument("Function metric types are not implemented");
  }
  default: {
    throw std::invalid_argument("Requested to build unsupported ElementType");
  }
  }

  group->addDeviceElement(NonemptyDeviceElementPtr(element));

  return new_id;
}

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