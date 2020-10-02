#include "BuildingAndRegirtrationFacade.hpp"

using namespace std;
using namespace Information_Access_Manager;
using namespace Model_Builder;
using namespace Model_Manager;
using namespace Information_Model;

BuildingAndRegirtrationFacade::BuildingAndRegirtrationFacade() {
  manager_ = manager_->getInstance();
}

void BuildingAndRegirtrationFacade::buildDeviceBase(const string &unique_Id,
                                                    const string &name,
                                                    const string &desc) {
  builder_ = new DeviceBuilder(name, unique_Id, desc);
}

string
BuildingAndRegirtrationFacade::addDeviceElementGroup(const string &name,
                                                     const string &desc) {
  return builder_->addDeviceElementGroup(name, desc);
}

string BuildingAndRegirtrationFacade::addDeviceElementGroup(
    const string &group_refid, const string &name, const string &desc) {
  return builder_->addDeviceElementGroup(group_refid, name, desc);
}

string BuildingAndRegirtrationFacade::addReadableMetric(
    const string &name, const string &desc,
    Information_Model::DataType data_type, ReadFunctor read_cb) {
  return builder_->addReadableMetric(name, desc, data_type, read_cb);
}

string BuildingAndRegirtrationFacade::addReadableMetric(
    const string &group_refid, const string &name, const string &desc,
    Information_Model::DataType data_type, ReadFunctor read_cb) {
  return builder_->addReadableMetric(group_refid, name, desc, data_type,
                                     read_cb);
}

string BuildingAndRegirtrationFacade::addWritableMetric(
    const string &name, const string &desc,
    Information_Model::DataType data_type, ReadFunctor read_cb,
    WriteFunctor write_cb) {
  return builder_->addWritableMetric(name, desc, data_type, read_cb, write_cb);
}

string BuildingAndRegirtrationFacade::addWritableMetric(
    const string &group_refid, const string &name, const string &desc,
    Information_Model::DataType data_type, ReadFunctor read_cb,
    WriteFunctor write_cb) {
  return builder_->addWritableMetric(group_refid, name, desc, data_type,
                                     read_cb, write_cb);
}

string BuildingAndRegirtrationFacade::addDeviceElement(
    const string &group_refid, const string &name, const string &desc,
    Information_Model::ElementType type, Information_Model::DataType data_type,
    optional<ReadFunctor> read_cb, optional<WriteFunctor> write_cb) {
  return builder_->addDeviceElement(group_refid, name, desc, type, data_type,
                                    *read_cb, *write_cb);
}

shared_ptr<Information_Model::Device>
BuildingAndRegirtrationFacade::getResult() {
  shared_ptr<Device> device = builder_->getResult();
  delete builder_;
  return move(device);
}

bool BuildingAndRegirtrationFacade::registerDevice(shared_ptr<Device> device) {
  return manager_->registerDevice(move(device));
}

bool BuildingAndRegirtrationFacade::deregisterDevice(const string &device_id) {
  return manager_->deregisterDevice(device_id);
}