#include "DeviceImplementationBuilder.hpp"

using namespace std;
using namespace Information_Model;
namespace Information_Model_Manager {
DeviceImplementationBuilder::DeviceImplementationBuilder(
    const string& ref_id, const string& name, const string& desc) {
  device_ = make_shared<DeviceImplementation>(ref_id, name, desc);
}

string DeviceImplementationBuilder::addDeviceElementGroup(
    const string& name, const string& desc) {
  return addDeviceElement(string(), name, desc, ElementType::GROUP,
      DataType::UNKNOWN, std::nullopt, std::nullopt, std::nullopt);
}

string DeviceImplementationBuilder::addDeviceElementGroup(
    const string& group_ref_id, const string& name, const string& desc) {
  return addDeviceElement(group_ref_id, name, desc, ElementType::GROUP,
      DataType::UNKNOWN, std::nullopt, std::nullopt, std::nullopt);
}

string DeviceImplementationBuilder::addReadableMetric(const string& name,
    const string& desc, DataType data_type, ReadFunctor read_cb) {
  return addDeviceElement(string(), name, desc, ElementType::READABLE,
      data_type, move(read_cb), std::nullopt, std::nullopt);
}

string DeviceImplementationBuilder::addReadableMetric(
    const string& group_ref_id, const string& name, const string& desc,
    DataType data_type, ReadFunctor read_cb) {
  return addDeviceElement(group_ref_id, name, desc, ElementType::READABLE,
      data_type, move(read_cb), std::nullopt, std::nullopt);
}

string DeviceImplementationBuilder::addWritableMetric(const string& name,
    const string& desc, DataType data_type, std::optional<ReadFunctor> read_cb,
    WriteFunctor write_cb) {
  return addDeviceElement(string(), name, desc, ElementType::WRITABLE,
      data_type, move(read_cb), move(write_cb), std::nullopt);
}

string DeviceImplementationBuilder::addWritableMetric(
    const string& group_ref_id, const string& name, const string& desc,
    DataType data_type, std::optional<ReadFunctor> read_cb,
    WriteFunctor write_cb) {
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

string DeviceImplementationBuilder::addDeviceElement(const string& group_ref_id,
    const string& name, const string& desc, Information_Model::ElementType type,
    Information_Model::DataType data_type,
    std::optional<Information_Model::ReadFunctor> read_cb,
    std::optional<Information_Model::WriteFunctor> write_cb,
    std::optional<Information_Model::ExecuteFunctor> execute_cb) {
  string ref_id("");

  auto group = getGroupImplementation(group_ref_id);

  switch (type) {
  case ElementType::GROUP: {
    ref_id = group->addSubgroup(name, desc);
    break;
  };
  case ElementType::WRITABLE: {
    ref_id = group->addWritableMetric(name, desc, data_type,
        setCallback<ReadFunctor>(read_cb), setCallback<WriteFunctor>(write_cb));
    break;
  }
  case ElementType::READABLE: {
    ref_id = group->addReadableMetric(
        name, desc, data_type, setCallback<ReadFunctor>(read_cb));
    break;
  }
  case ElementType::FUNCTION: {
    // @TODO: implement function support
    __attribute__((unused)) auto suppress = execute_cb;
  }
  default: {
    break;
  }
  }
  return ref_id;
}

shared_ptr<Device> DeviceImplementationBuilder::getResult() { return device_; }

DeviceImplementationBuilder::DeviceGroupImplementation
DeviceImplementationBuilder::getGroupImplementation(const string& ref_id) {
  if (ref_id.empty()) {
    return device_->getGroupImplementation().base();
  } else {
    return device_->getGroupImplementation()->getSubgroupImplementation(ref_id);
  }
}
} // namespace Information_Model_Manager