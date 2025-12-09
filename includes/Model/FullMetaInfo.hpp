#ifndef __MODEL_META_INFO_IMPLEMENTATION_HPP_
#define __MODEL_META_INFO_IMPLEMENTATION_HPP_

#include "Information_Model/DeviceBuilder.hpp"
#include "Information_Model/MetaInfo.hpp"

#include <functional>
#include <memory>

namespace Information_Model_Manager {

struct FullMetaInfo : public virtual Information_Model::MetaInfo {
  FullMetaInfo(const std::string& id, const Information_Model::BuildInfo& meta);

  std::string id() const final;

  std::string name() const final;

  std::string description() const final;

private:
  std::string id_;
  Information_Model::BuildInfo meta_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_META_INFO_IMPLEMENTATION_HPP_