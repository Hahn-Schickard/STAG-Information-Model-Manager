#include "DeviceElementGroupImplementation.hpp"

#include <exception>
#include <vector>

using namespace std;
using namespace Information_Model;

namespace Information_Model_Manager {

/**
 * @brief Counts number of occurencies of a given pattern from a given cut of
 * marker
 *
 * @param input
 * @param pattern
 * @param cut_off
 * @return size_t
 */
size_t countOccurrences(
    const string& input, const string& pattern, const string& cut_off) {
  size_t count = 0;
  string buffer = input.substr(input.find(cut_off) + 1, input.size());
  if (!buffer.empty()) {
    count++;
    size_t next_marker = buffer.find(pattern);
    while (next_marker != string::npos) {
      count++;
      next_marker = buffer.find(pattern, next_marker + pattern.size());
    }
  }
  return count;
}

/**
 * @brief Returns the current depth of subelements in the tree structure
 * based on a given input ref_id
 *
 * @param ref_id
 * @return size_t
 */
size_t getTreeLevel(const string& ref_id) {
  return countOccurrences(ref_id, ".", ":");
}

/**
 * @brief Returns the position of the Nth occurrence of a given pattern
 * within a given input string
 *
 * Based on code from https://stackoverflow.com/a/27668715/4371473
 *
 * @param input
 * @param occurrence
 * @param pattern
 * @return size_t
 */
size_t findNthSubstring(
    const string& input, size_t occurrence, const string& pattern) {
  if (0 == occurrence) {
    return string::npos;
  } else {
    size_t position, offset = 0;
    unsigned int i = 0;
    while (i < occurrence) {
      position = input.find(pattern, offset);
      if (string::npos == position) {
        break;
      } else {
        offset = position + pattern.size();
        i++;
      }
    }
    return position;
  }
}

/**
 * @brief Returns a parent id of a given level.
 * To find the maximum depth of the current child id used
 * getTreeLevel(const string &ref_id)
 *
 * @param child_ref_id
 * @param parent_level
 * @return string
 */
string getNextElementID(const string& child_ref_id, size_t parent_level) {
  string tmp =
      child_ref_id.substr(0, findNthSubstring(child_ref_id, parent_level, "."));
  return tmp;
}

DeviceElementGroupImplementation::DeviceElementGroupImplementation(
    const string& base_ref_id)
    : element_count_(0), base_ref_id_(base_ref_id) {}

DeviceElementGroup::DeviceElements
DeviceElementGroupImplementation::getSubelements() const {
  DeviceElementGroup::DeviceElements subelements;
  // NOLINTNEXTLINE
  for (auto element_pair : elements_map_) {
    subelements.push_back(element_pair.second);
  }
  return subelements;
}

NonemptyDeviceElementPtr DeviceElementGroupImplementation::getSubelement(
    const string& ref_id) const {
  size_t target_level = getTreeLevel(ref_id) - 1;
  size_t current_level = getTreeLevel(base_ref_id_);
  // Check if a given element is in a sub group
  if (target_level != current_level) {
    auto next_id = getNextElementID(ref_id, target_level);
    auto next_element = getSubelement(next_id).base();
    try {
      auto next_group =
          std::get<NonemptyDeviceElementGroupPtr>(next_element->functionality);
      return next_group->getSubelement(ref_id);
    } catch (...) {
      throw DeviceElementNotFound(ref_id);
    }

  } else if (elements_map_.find(ref_id) != elements_map_.end()) {
    return elements_map_.at(ref_id);
  }
  throw DeviceElementNotFound(ref_id);
}

std::shared_ptr<DeviceElementGroupImplementation>
DeviceElementGroupImplementation::getSubgroupImplementation(
    const std::string& ref_id) {
  size_t target_level = getTreeLevel(ref_id) - 1;
  size_t current_level = getTreeLevel(base_ref_id_);
  // Check if a given element is in a sub group
  if (target_level != current_level) {
    string next_id = getNextElementID(ref_id, target_level);
    auto next_group = getSubgroupImplementation(next_id);
    // Check if next group exists
    if (next_group) {
      return next_group->getSubgroupImplementation(ref_id);
    }
  } // If not, check if it is in this group
  else if (subgroups_map_.find(ref_id) != subgroups_map_.end()) {
    return subgroups_map_.at(ref_id).base();
  }
  // If not, return an empty shared_ptr
  return shared_ptr<DeviceElementGroupImplementation>();
}

void DeviceElementGroupImplementation::addSubgroup(
    NonemptyDeviceElementGroupImplementationPtr group) {
  subgroups_map_.emplace(group->base_ref_id_, group);
}

void DeviceElementGroupImplementation::addDeviceElement(
    NonemptyDeviceElementPtr element) {
  elements_map_.emplace(element->getElementId(), element);
}

string DeviceElementGroupImplementation::generateReferenceID() {
  string element_id;

  if (base_ref_id_.back() == ':') {
    element_id = to_string(element_count_);
  } else {
    element_id = "." + to_string(element_count_);
  }
  element_count_++;
  return base_ref_id_ + element_id;
}
} // namespace Information_Model_Manager