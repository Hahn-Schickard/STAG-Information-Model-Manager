#include "DeviceBuilder.hpp"

using namespace std;
using namespace Information_Model;
using namespace Technology_Adapter;

namespace Infromation_Model_Manager {
void DeviceBuilder::buildDeviceBase(const string &unique_id, const string &name,
                                    const string &desc) {
  builder_ = make_unique<DeviceImplementationBuilder>(unique_id, name, desc);
}

string DeviceBuilder::addDeviceElementGroup(const string &name,
                                            const string &desc) {
  return builder_->addDeviceElementGroup(name, desc);
}

string DeviceBuilder::addDeviceElementGroup(const string &group_refid,
                                            const string &name,
                                            const string &desc) {
  return builder_->addDeviceElementGroup(group_refid, name, desc);
}

string DeviceBuilder::addReadableMetric(const string &name, const string &desc,
                                        DataType data_type,
                                        ReadFunctor read_cb) {
  return builder_->addReadableMetric(name, desc, data_type, read_cb);
}

string DeviceBuilder::addReadableMetric(const string &group_refid,
                                        const string &name, const string &desc,
                                        DataType data_type,
                                        ReadFunctor read_cb) {
  return builder_->addReadableMetric(group_refid, name, desc, data_type,
                                     read_cb);
}

string DeviceBuilder::addWritableMetric(const string &name, const string &desc,
                                        DataType data_type, ReadFunctor read_cb,
                                        WriteFunctor write_cb) {
  return builder_->addWritableMetric(name, desc, data_type, read_cb, write_cb);
}

string DeviceBuilder::addWritableMetric(const string &group_refid,
                                        const string &name, const string &desc,
                                        DataType data_type, ReadFunctor read_cb,
                                        WriteFunctor write_cb) {
  return builder_->addWritableMetric(group_refid, name, desc, data_type,
                                     read_cb, write_cb);
}

string DeviceBuilder::addDeviceElement(const string &group_refid,
                                       const string &name, const string &desc,
                                       ElementType type, DataType data_type,
                                       optional<ReadFunctor> read_cb,
                                       optional<WriteFunctor> write_cb) {
  return builder_->addDeviceElement(group_refid, name, desc, type, data_type,
                                    read_cb, write_cb);
}

shared_ptr<Device> DeviceBuilder::getResult() {
  auto result = builder_->getResult();
  builder_.reset();
  return move(result);
}
} // namespace Infromation_Model_Manager