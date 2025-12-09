#ifndef __MODEL_ELEMENT_IMPLEMENTATION_HPP_
#define __MODEL_ELEMENT_IMPLEMENTATION_HPP_

#include "Information_Model/Element.hpp"

#include "FullMetaInfo.hpp"

#include <memory>

namespace Information_Model_Manager {
struct ElementImpl : virtual public Information_Model::Element,
                     public FullMetaInfo {
  ElementImpl(const std::string& id,
      const Information_Model::BuildInfo& meta,
      const Information_Model::ElementFunction& function);

  Information_Model::ElementType type() const final;

  Information_Model::ElementFunction function() const final;

private:
  Information_Model::ElementFunction function_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_ELEMENT_IMPLEMENTATION_HPP_