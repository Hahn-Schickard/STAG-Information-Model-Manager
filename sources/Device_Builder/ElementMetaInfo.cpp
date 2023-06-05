#include "ElementMetaInfo.hpp"

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {

NamedElementPtr ElementMetaInfo::getMetaInfo() const {
  return meta_info_.lock();
}

void ElementMetaInfo::linkMetaInfo(const NonemptyNamedElementPtr& meta_info) {
  meta_info_ = meta_info.base();
}
} // namespace Information_Model_Manager
