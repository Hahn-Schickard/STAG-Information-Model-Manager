#ifndef __BUILDING_AND_REGISTRATION_FACADE_HPP
#define __BUILDING_AND_REGISTRATION_FACADE_HPP

#include "BuildingAndRegistrationInterface.hpp"
#include "DeviceBuilder.hpp"
#include "ModelManager.hpp"

#include <memory>
#include <string>

namespace Information_Access_Manager {
class BuildingAndRegirtrationFacade : public BuildingAndRegistrationInterface {
  Model_Manager::ModelManager *manager_;
  Model_Builder::DeviceBuilder *builder_;

public:
  BuildingAndRegirtrationFacade();
  void buildDeviceBase(const std::string &UNIQUE_ID, const std::string &NAME,
                       const std::string &DESC) final;
  std::string addDeviceElementGroup(const std::string &name,
                                    const std::string &desc) final;
  std::string addDeviceElementGroup(const std::string &group_refid,
                                    const std::string &name,
                                    const std::string &desc) final;
  std::string addReadableMetric(
      const std::string &name, const std::string &desc,
      Information_Model::DataType data_type,
      std::function<Information_Model::DataVariant()> read_cb) final;
  std::string addReadableMetric(
      const std::string &group_refid, const std::string &name,
      const std::string &desc, Information_Model::DataType data_type,
      std::function<Information_Model::DataVariant()> read_cb) final;
  std::string addWritableMetric(
      const std::string &name, const std::string &desc,
      Information_Model::DataType data_type,
      std::function<Information_Model::DataVariant()> read_cb,
      std::function<void(Information_Model::DataVariant)> write_cb) final;
  std::string addWritableMetric(
      const std::string &group_refid, const std::string &name,
      const std::string &desc, Information_Model::DataType data_type,
      std::function<Information_Model::DataVariant()> read_cb,
      std::function<void(Information_Model::DataVariant)> write_cb) final;

  std::string addDeviceElement(
      const std::string &group_refid, const std::string &name,
      const std::string &desc, Information_Model::ElementType type,
      Information_Model::DataType data_type,
      std::function<Information_Model::DataVariant()> read_cb,
      std::function<void(Information_Model::DataVariant)> write_cb) final;

  std::shared_ptr<Information_Model::Device> getResult() final;

  bool registerDevice(std::shared_ptr<Information_Model::Device> device) final;
  bool deregisterDevice(const std::string &DEVICE_ID) final;
};
} // namespace Information_Access_Manager

#endif //__BUILDING_AND_REGISTRATION_FACADE_HPPs