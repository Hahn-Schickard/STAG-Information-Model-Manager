#include "ElementMetaInfo.hpp"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {

NamedElementPtr ElementMetaInfo::getMetaInfo() const {
  return meta_info_.lock();
}

string ElementMetaInfo::getElementInfo(const string& type) const {
  auto element_info = "Unknown " + type;
  if (auto meta_info = getMetaInfo()) {
    element_info =
        type + meta_info->getElementName() + " " + meta_info->getElementId();
  }
  return element_info;
}

void ElementMetaInfo::linkMetaInfo(const NonemptyNamedElementPtr& meta_info) {
  meta_info_ = meta_info.base();
}
} // namespace Information_Model_Manager
