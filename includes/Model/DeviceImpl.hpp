#ifndef __MODEL_DEVICE_IMPLEMENTATION_HPP_
#define __MODEL_DEVICE_IMPLEMENTATION_HPP_

#include <Information_Model/Device.hpp>

#include "FullMetaInfo.hpp"
#include "GroupImpl.hpp"

#include <memory>

namespace Information_Model_Manager {
struct DeviceImpl : virtual public Information_Model::Device,
                    public FullMetaInfo {
  DeviceImpl(const std::string& id, const Information_Model::BuildInfo& meta);

  ~DeviceImpl() override = default;

  Information_Model::GroupPtr group() const final;

  size_t size() const final;

  Information_Model::ElementPtr element(const std::string& ref_id) const final;

  void visit(const Information_Model::Group::Visitor& visitor) const final;

  void addElement(const Information_Model::ElementPtr& element);

  std::string generateID();

private:
  GroupImplPtr root_;
};

using DeviceImplPtr = std::shared_ptr<DeviceImpl>;
} // namespace Information_Model_Manager

#endif //__MODEL_DEVICE_IMPLEMENTATION_HPP_