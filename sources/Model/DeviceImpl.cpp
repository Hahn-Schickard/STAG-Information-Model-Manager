#include "DeviceImpl.hpp"

namespace Information_Model_Manager {
using namespace std;
using namespace Information_Model;

DeviceImpl::DeviceImpl(const std::string& id, const BuildInfo& meta)
    : FullMetaInfo(id, meta), root_(make_shared<GroupImpl>(id + ":")) {}

Information_Model::GroupPtr DeviceImpl::group() const { return root_; }

size_t DeviceImpl::size() const { return root_->size(); }

ElementPtr DeviceImpl::element(const string& ref_id) const {
  return root_->element(ref_id);
}

void DeviceImpl::visit(const Group::Visitor& visitor) const {
  root_->visit(visitor);
}

void DeviceImpl::addElement(const ElementPtr& element) {
  root_->addElement(element);
}

string DeviceImpl::generateID() { return root_->generateID(); }

} // namespace Information_Model_Manager