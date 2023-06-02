#include "DeviceBuilder.hpp"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
void DeviceBuilder::buildDeviceBase(
    const string& unique_id, const string& name, const string& desc) {
  device_ = make_unique<DeviceImplementation>(unique_id, name, desc);
}

string DeviceBuilder::addDeviceElementGroup(
    const string& group_ref_id, const string& name, const string& desc) {
  return addDeviceElement(group_ref_id, name, desc, Functionality());
}

string DeviceBuilder::addReadableMetric(const string& group_ref_id,
    const string& name, const string& desc, DataType data_type,
    Reader read_cb) {
  return addDeviceElement(
      group_ref_id, name, desc, Functionality(data_type, read_cb));
}

string DeviceBuilder::addWritableMetric(const string& group_ref_id,
    const string& name, const string& desc, DataType data_type, Writer write_cb,
    Reader read_cb) {
  return addDeviceElement(
      group_ref_id, name, desc, Functionality(data_type, read_cb, write_cb));
}

string DeviceBuilder::addDeviceElement(const string& group_ref_id,
    const string& name, const string& desc,
    const Functionality& functionality) {
  auto group = getGroupImplementation(group_ref_id);
  auto ref_id = group->generateReferenceID();
  DeviceElementPtr element;
  switch (functionality.type()) {
  case ElementType::GROUP: {
    auto sub_group =
        NonemptyPointer::make_shared<DeviceElementGroupImplementation>(ref_id);
    group->addSubgroup(sub_group);
    element = makeDeviceElement(
        ref_id, name, desc, NonemptyDeviceElementGroupPtr(sub_group));
    break;
  }
  case ElementType::READABLE: {
    auto read = functionality.getRead();
    auto readable = NonemptyPointer::make_shared<MetricImplementation>(
        functionality.data_type, read.callback);
    NonemptyMetricPtr interface(readable);
    element = makeDeviceElement(ref_id, name, desc, interface);
    readable->linkMetaInfo(NonemptyDeviceElementPtr(element));
    break;
  }
  case ElementType::WRITABLE: {
    auto write = functionality.getWrite();
    auto writable = NonemptyPointer::make_shared<WritableMetricImplementation>(
        functionality.data_type, write.read_part.callback, write.callback);
    NonemptyWritableMetricPtr interface(writable);
    element = makeDeviceElement(ref_id, name, desc, interface);
    writable->linkMetaInfo(NonemptyDeviceElementPtr(element));
    break;
  }
  case ElementType::FUNCTION: {
    // @TODO: implement function support
    __attribute__((unused)) auto suppress = functionality;
    throw std::invalid_argument("Function metric types are not implemented");
  }
  default: {
    throw std::invalid_argument("Requested to build unsupported ElementType");
  }
  }
  group->addDeviceElement(NonemptyDeviceElementPtr(element));

  return ref_id;
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