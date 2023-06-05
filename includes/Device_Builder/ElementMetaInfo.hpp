#ifndef __MODEL_BUILDER_ELEMENT_META_INFO_HPP_
#define __MODEL_BUILDER_ELEMENT_META_INFO_HPP_

#include "Information_Model/NamedElement.hpp"

namespace Information_Model_Manager {

/**
 * @brief Stores Information_Model::NamedElement information
 *
 * @attention Meta value MUST only be set via DeviceBuilder during element
 * construction. NamedElement information consumers MUST NOT be able to change
 * this value
 */
struct ElementMetaInfo {
  using MetaInfoPtr = std::weak_ptr<Information_Model::NamedElement>;

protected:
  Information_Model::NamedElementPtr getMetaInfo() const;

private:
  void linkMetaInfo(
      const Information_Model::NonemptyNamedElementPtr& meta_info);

  friend struct DeviceBuilder;

  MetaInfoPtr meta_info_;
};

} // namespace Information_Model_Manager
#endif //__MODEL_BUILDER_ELEMENT_META_INFO_HPP_