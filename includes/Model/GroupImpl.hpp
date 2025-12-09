#ifndef __MODEL_GROUP_IMPLEMENTATION_HPP_
#define __MODEL_GROUP_IMPLEMENTATION_HPP_

#include <Information_Model/Element.hpp>
#include <Information_Model/Group.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Information_Model_Manager {
struct GroupImpl : public Information_Model::Group {
  using ElementsMap =
      std::unordered_map<std::string, Information_Model::ElementPtr>;
  using ElementVector = std::vector<Information_Model::ElementPtr>;

  GroupImpl(const std::string& id);

  size_t size() const final;

  ElementsMap asMap() const final;

  ElementVector asVector() const final;

  Information_Model::ElementPtr element(const std::string& ref_id) const final;

  void visit(const Visitor& visitor) const final;

  std::string generateID();

  void addElement(const Information_Model::ElementPtr& element);

private:
  using SubgroupsMap =
      std::unordered_map<std::string, Information_Model::GroupPtr>;

  Information_Model::ElementPtr getElement(const std::string& ref_id);

  ElementsMap elements_;
  SubgroupsMap subgroups_;
  size_t next_id_ = 0;
  std::string id_;
};

using GroupImplPtr = std::shared_ptr<GroupImpl>;
} // namespace Information_Model_Manager

#endif //__MODEL_GROUP_IMPLEMENTATION_HPP_