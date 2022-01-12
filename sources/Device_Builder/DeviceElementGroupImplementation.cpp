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
size_t countOccurrences(const string &input, const string &pattern,
                        const string &cut_off) {
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
size_t getTreeLevel(const string &ref_id) {
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
size_t findNthSubstring(const string &input, size_t occurrence,
                        const string &pattern) {
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
string getNextElementID(const string &child_ref_id, size_t parent_level) {
  string tmp =
      child_ref_id.substr(0, findNthSubstring(child_ref_id, parent_level, "."));
  return tmp;
}

DeviceElementGroupImplementation::DeviceElementGroupImplementation(
    const string &ref_id, const string &name, const string &desc)
    : DeviceElementGroup(), elemenet_count_(0), base_ref_id_(ref_id) {}

std::vector<NonemptyDeviceElementPtr>
DeviceElementGroupImplementation::getSubelements() {
  vector<NonemptyDeviceElementPtr> subelements;
  // NOLINTNEXTLINE
  for (auto element_pair : elements_map_) {
    subelements.push_back(element_pair.second);
  }
  return subelements;
}

shared_ptr<DeviceElement>
DeviceElementGroupImplementation::getSubelement(const string &ref_id) {
  size_t target_level = getTreeLevel(ref_id) - 1;
  size_t current_level = getTreeLevel(base_ref_id_);
  // Check if a given element is in a sub group
  if (target_level != current_level) {
    string next_id = getNextElementID(ref_id, target_level);
    auto next_element = getSubelement(next_id);
    // Check if next element exists and is a group
    if (next_element) {
      auto next_group = std::get_if<NonemptyDeviceElementGroupPtr>
        (&next_element->specific_interface);
      if (next_group)
        return (*next_group)->getSubelement(ref_id);
    }
  } // If not, check if it is in this group
  else if (elements_map_.find(ref_id) != elements_map_.end()) {
    return elements_map_.at(ref_id).base();
  }
  // If not, return an empty shared_ptr
  return shared_ptr<DeviceElement>();
}

std::shared_ptr<DeviceElementGroupImplementation>
DeviceElementGroupImplementation::getSubgroupImplementation(
  const std::string & ref_id)
{
  size_t target_level = getTreeLevel(ref_id) - 1;
  size_t current_level = getTreeLevel(base_ref_id_);
  // Check if a given element is in a sub group
  if (target_level != current_level) {
    string next_id = getNextElementID(ref_id, target_level);
    auto next_group = getSubgroupImplementation(next_id);
    // Check if next group exists
    if (next_group)
      return next_group->getSubgroupImplementation(ref_id);
  } // If not, check if it is in this group
  else if (subgroups_map_.find(ref_id) != subgroups_map_.end()) {
    return subgroups_map_.at(ref_id).base();
  }
  // If not, return an empty shared_ptr
  return shared_ptr<DeviceElementGroupImplementation>();
}

string DeviceElementGroupImplementation::addSubgroup(const string &name,
                                                     const string &desc) {
  string ref_id = generate_Reference_ID();

  auto implementation =
    NonemptyPointer::make_shared<DeviceElementGroupImplementation>
      (ref_id, name, desc);
  NonemptyDeviceElementGroupPtr interface = implementation;
  auto element = NonemptyPointer::make_shared<DeviceElement>(
    ref_id,name,desc,interface);
  pair<string, NonemptyDeviceElementPtr> element_pair(ref_id,element);
  elements_map_.insert(element_pair);

  subgroups_map_.insert(make_pair(ref_id, implementation));

  return ref_id;
}

string DeviceElementGroupImplementation::addReadableMetric(
    const string &name, const string &desc, DataType data_type,
    function<DataVariant()> read_cb) {
  string ref_id = generate_Reference_ID();

  NonemptyMetricPtr interface =
    NonemptyPointer::make_shared<MetricImplementation>
      (ref_id, name, desc, data_type, read_cb);
  auto element = NonemptyPointer::make_shared<DeviceElement>(
    ref_id,name,desc,interface);
  pair<string, NonemptyDeviceElementPtr> element_pair(ref_id,element);
  elements_map_.insert(element_pair);

  return ref_id;
}

string DeviceElementGroupImplementation::addWritableMetric(
    const string &name, const string &desc, DataType data_type,
    optional<function<DataVariant()>> read_cb,
    function<void(DataVariant)> write_cb) {
  string ref_id = generate_Reference_ID();

  NonemptyWritableMetricPtr interface =
    NonemptyPointer::make_shared<WritableMetricImplementation>
      (ref_id, name, desc, data_type, read_cb, write_cb);
  auto element = NonemptyPointer::make_shared<DeviceElement>(
    ref_id,name,desc,interface);
  pair<string, NonemptyDeviceElementPtr> element_pair(ref_id,element);
  elements_map_.insert(element_pair);

  return ref_id;
}

string DeviceElementGroupImplementation::generate_Reference_ID() {
  string element_id("");

  if (base_ref_id_.back() == ':') {
    element_id = to_string(elemenet_count_);
  } else {
    element_id = "." + to_string(elemenet_count_);
  }
  elemenet_count_++;
  return base_ref_id_ + element_id;
}
} // namespace Information_Model_Manager