#include "DeviceBuilder.hpp"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {
void DeviceBuilder::buildDeviceBase(
    const string& unique_id, const string& name, const string& desc) {
  builder_ = make_unique<DeviceImplementationBuilder>(unique_id, name, desc);
}

string DeviceBuilder::addDeviceElementGroup(
    const string& name, const string& desc) {
  return builder_->addDeviceElementGroup(name, desc);
}

string DeviceBuilder::addDeviceElementGroup(
    const string& group_ref_id, const string& name, const string& desc) {
  return builder_->addDeviceElementGroup(group_ref_id, name, desc);
}

string DeviceBuilder::addReadableMetric(const string& name, const string& desc,
    DataType data_type, ReadFunctor read_cb) {
  return builder_->addReadableMetric(name, desc, data_type, read_cb);
}

string DeviceBuilder::addReadableMetric(const string& group_ref_id,
    const string& name, const string& desc, DataType data_type,
    ReadFunctor read_cb) {
  return builder_->addReadableMetric(
      group_ref_id, name, desc, data_type, read_cb);
}

string DeviceBuilder::addWritableMetric(const string& name, const string& desc,
    DataType data_type, optional<ReadFunctor> read_cb, WriteFunctor write_cb) {
  return builder_->addWritableMetric(name, desc, data_type, read_cb, write_cb);
}

string DeviceBuilder::addWritableMetric(const string& group_ref_id,
    const string& name, const string& desc, DataType data_type,
    optional<ReadFunctor> read_cb, WriteFunctor write_cb) {
  return builder_->addWritableMetric(
      group_ref_id, name, desc, data_type, read_cb, write_cb);
}

string DeviceBuilder::addDeviceElement(const string& group_ref_id,
    const string& name, const string& desc, Information_Model::ElementType type,
    Information_Model::DataType data_type,
    optional<Information_Model::ReadFunctor> read_cb,
    optional<Information_Model::WriteFunctor> write_cb,
    optional<Information_Model::ExecuteFunctor> execute_cb) {
  return builder_->addDeviceElement(
      group_ref_id, name, desc, type, data_type, read_cb, write_cb, execute_cb);
}

shared_ptr<Device> DeviceBuilder::getResult() {
  auto result = builder_->getResult();
  builder_.reset();
  return move(result);
}
} // namespace Information_Model_Manager