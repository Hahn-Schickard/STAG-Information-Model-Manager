#include "DeviceImplementationBuilder.hpp"

using namespace std;
using namespace Information_Model;
namespace Information_Model_Manager {
DeviceImplementationBuilder::DeviceImplementationBuilder(const string &name,
                                                         const string &ref_id,
                                                         const string &desc) {
  device_ = make_shared<DeviceImplementation>(ref_id, name, desc);
}

string DeviceImplementationBuilder::addDeviceElementGroup(const string &name,
                                                          const string &desc) {
  return addDeviceElement(string(), name, desc, ElementType::GROUP,
                          DataType::UNKNOWN, nullptr, nullptr);
}

string DeviceImplementationBuilder::addDeviceElementGroup(
    const string &group_refid, const string &name, const string &desc) {
  return addDeviceElement(group_refid, name, desc, ElementType::GROUP,
                          DataType::UNKNOWN, nullptr, nullptr);
}

string DeviceImplementationBuilder::addReadableMetric(const string &name,
                                                      const string &desc,
                                                      DataType data_type,
                                                      ReadFunctor read_cb) {
  return addDeviceElement(string(), name, desc, ElementType::READABLE,
                          data_type, move(read_cb), nullptr);
}

string DeviceImplementationBuilder::addReadableMetric(
    const string &group_ref_id, const string &name, const string &desc,
    DataType data_type, ReadFunctor read_cb) {
  return addDeviceElement(group_ref_id, name, desc, ElementType::READABLE,
                          data_type, move(read_cb), nullptr);
}

string DeviceImplementationBuilder::addWritableMetric(
    const string &name, const string &desc, DataType data_type,
    std::optional<ReadFunctor> read_cb, WriteFunctor write_cb) {
  return addDeviceElement(string(), name, desc, ElementType::WRITABLE,
                          data_type, move(read_cb), move(write_cb));
}

string DeviceImplementationBuilder::addWritableMetric(
    const string &group_ref_id, const string &name, const string &desc,
    DataType data_type, std::optional<ReadFunctor> read_cb,
    WriteFunctor write_cb) {
  return addDeviceElement(group_ref_id, name, desc, ElementType::WRITABLE,
                          data_type, move(read_cb), move(write_cb));
}

template <class T> T setCallback(optional<T> optional_value) {
  if (optional_value.has_value()) {
    return optional_value.value();
  } else {
    return T();
  }
}

string DeviceImplementationBuilder::addDeviceElement(
    const string &group_refid, const string &name, const string &desc,
    Information_Model::ElementType type, Information_Model::DataType data_type,
    optional<ReadFunctor> read_cb, optional<WriteFunctor> write_cb) {
  string ref_id("");

  auto group = getGroupImplementation(group_refid);

  switch (type) {
  case ElementType::GROUP: {
    ref_id = group->addSubgroup(name, desc);
    break;
  };
  case ElementType::OBSERVABLE:
  case ElementType::WRITABLE: {
    ref_id = group->addWritableMetric(name, desc, data_type,
                                      setCallback<ReadFunctor>(read_cb),
                                      setCallback<WriteFunctor>(write_cb));
    break;
  }
  case ElementType::READABLE: {
    ref_id = group->addReadableMetric(name, desc, data_type,
                                      setCallback<ReadFunctor>(read_cb));
    break;
  }
  case ElementType::FUNCTION:
  default: { break; }
  }
  return ref_id;
}

shared_ptr<Device> DeviceImplementationBuilder::getResult() {
  return static_pointer_cast<Device>(device_);
}

shared_ptr<DeviceElementGroupImplementation>
DeviceImplementationBuilder::getGroupImplementation(const string &ref_id) {
  if (ref_id.empty()) {
    return static_pointer_cast<DeviceElementGroupImplementation>(
        device_->getDeviceElementGroup());
  } else {
    return static_pointer_cast<DeviceElementGroupImplementation>(
        device_->getDeviceElementGroup()->getSubelement(ref_id));
  }
}
} // namespace Information_Model_Manager