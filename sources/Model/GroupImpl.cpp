#include "GroupImpl.hpp"

#include <algorithm>

namespace Information_Model_Manager {
using namespace std;
using namespace Information_Model;

GroupImpl::GroupImpl(const string& id) : id_(id) {}

size_t GroupImpl::size() const { return elements_.size(); }

GroupImpl::ElementsMap GroupImpl::asMap() const { return elements_; }

GroupImpl::ElementVector GroupImpl::asVector() const {
  vector<ElementPtr> result;

  if (!elements_.empty()) {
    result.reserve(elements_.size());
    size_t i = 0;
    while (i < elements_.size()) {
      auto element = elements_.at(to_string(i));
      result.push_back(element);
      i++;
    }
  }
  return result;
}

ElementPtr GroupImpl::element(const string& ref_id) const {
  auto sanitized_id = id_;
  if (sanitized_id.back() == ':') {
    sanitized_id.pop_back();
  }
  if (ref_id == sanitized_id) {
    throw IDPointsThisGroup(ref_id);
  }
  if (ref_id.compare(0, id_.length(), id_) != 0) {
    // if referenced id does not start with this id, than the element is not in
    // this GroupImpl
    throw ElementNotFound(ref_id);
  }

  auto sub_id = ref_id.substr(id_.size());
  if (sub_id.front() == '.') {
    sub_id.erase(0, 1);
  }
  auto group_marker = sub_id.find('.');
  if (group_marker == string::npos) {
    if (auto it = elements_.find(sub_id); it != elements_.end()) {
      return it->second;
    } else {
      // no element with given id exists
      throw ElementNotFound(ref_id);
    }
  } else {
    auto subgroup_id = sub_id.substr(0, group_marker);
    if (auto it = subgroups_.find(subgroup_id); it != subgroups_.end()) {
      return it->second->element(ref_id);
    } else {
      // no subgroup containing given id exists
      throw ElementNotFound(ref_id);
    }
  }
}

void GroupImpl::visit(const Visitor& visitor) const {
  for_each(elements_.begin(), elements_.end(), [&visitor](const auto& pair) {
    visitor(pair.second);
  });
}

string GroupImpl::generateID() {
  string new_id = (id_.back() == ':' ? id_ : id_ + '.') + to_string(next_id_);
  next_id_++;
  return new_id;
}

void GroupImpl::addElement(const ElementPtr& element) {
  if (!element) {
    throw invalid_argument("Given element is empty");
  }
  auto sanitized_id = id_;
  if (sanitized_id.back() == ':') {
    sanitized_id.pop_back();
  }
  if (element->id() == sanitized_id) {
    throw invalid_argument("Given element has the same ID as this group");
  }
  if (element->id().compare(0, id_.length(), id_) != 0) {
    throw invalid_argument("Given element is not part of this group");
  }

  auto sub_id = element->id().substr(id_.size());
  if (sub_id.front() == '.') {
    sub_id.erase(0, 1);
  }
  if (sub_id.back() == '.') {
    sub_id.pop_back();
  }
  auto group_marker = sub_id.find('.');
  if (group_marker != string::npos) {
    auto parent = this->element(id_ + sub_id.substr(0, group_marker));
    if (parent->type() != ElementType::Group) {
      throw invalid_argument(
          "Parent element " + parent->id() + " is not a group");
    }
    auto parent_function =
        dynamic_pointer_cast<GroupImpl>(get<GroupPtr>(parent->function()));
    parent_function->addElement(element);
  } else {
    if (!elements_.try_emplace(sub_id, element).second) {
      throw logic_error(
          "Element with id " + element->id() + " is already in this group");
    }
    if (element->type() == ElementType::Group) {
      auto subgroup_id = sub_id.substr(0, sub_id.find('.'));
      auto sub_group_impl =
          dynamic_pointer_cast<GroupImpl>(get<GroupPtr>(element->function()));
      subgroups_.emplace(subgroup_id, sub_group_impl);
    }
  }
}

} // namespace Information_Model_Manager