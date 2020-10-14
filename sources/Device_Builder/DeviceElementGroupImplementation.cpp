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
 * @param occurence
 * @param pattern
 * @return size_t
 */
size_t findNthSubstring(const string &input, size_t occurence,
                        const string &pattern) {
  if (0 == occurence) {
    return string::npos;
  } else {
    size_t position, offset = 0;
    unsigned int i = 0;
    while (i < occurence) {
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
 * To find the maximum depth of the current child id usel
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
    : DeviceElementGroup(ref_id, name, desc), elemenet_count_(0) {}

vector<shared_ptr<DeviceElement>>
DeviceElementGroupImplementation::getSubelements() {
  vector<shared_ptr<DeviceElement>> subelements;
  // NOLINTNEXTLINE
  for (auto elelement_pair : elements_map_) {
    subelements.push_back(elelement_pair.second);
  }
  return subelements;
}

shared_ptr<DeviceElement>
DeviceElementGroupImplementation::getSubelement(const string &ref_id) {
  size_t target_level = getTreeLevel(ref_id) - 1;
  size_t current_level = getTreeLevel(getElementId());
  // Check if a given element is in a sub group
  if (target_level != current_level) {
    string next_id = getNextElementID(ref_id, target_level);
    auto next_element = getSubelement(next_id);
    // Check if next element exists and is a group
    if (next_element && next_element->getElementType() == ElementType::GROUP) {
      auto next_group = static_pointer_cast<DeviceElementGroup>(next_element);
      // If so look for the element in it
      return next_group->getSubelement(ref_id);
    }
  } // If not, check if it is in this group
  else if (elements_map_.find(ref_id) != elements_map_.end()) {
    return elements_map_.at(ref_id);
  }
  // If not, return an empty shared_ptr
  return shared_ptr<DeviceElement>();
}

string DeviceElementGroupImplementation::addSubgroup(const string &name,
                                                     const string &desc) {
  string ref_id = generate_Reference_ID();

  pair<string, shared_ptr<DeviceElement>> element_pair(
      ref_id,
      make_shared<DeviceElementGroupImplementation>(ref_id, name, desc));
  elements_map_.insert(element_pair);

  return ref_id;
}

string DeviceElementGroupImplementation::addReadableMetric(
    const string &name, const string &desc, DataType data_type,
    function<DataVariant()> read_cb) {
  string ref_id = generate_Reference_ID();

  pair<string, shared_ptr<DeviceElement>> element_pair(
      ref_id, make_shared<MetricImplementation>(ref_id, name, desc, data_type,
                                                read_cb));
  elements_map_.insert(element_pair);

  return ref_id;
}

string DeviceElementGroupImplementation::addWritableMetric(
    const string &name, const string &desc, DataType data_type,
    function<DataVariant()> read_cb, function<void(DataVariant)> write_cb) {
  string ref_id = generate_Reference_ID();

  pair<string, shared_ptr<DeviceElement>> element_pair(
      ref_id, make_shared<WritableMetricImplementation>(
                  ref_id, name, desc, data_type, read_cb, write_cb));
  elements_map_.insert(element_pair);

  return ref_id;
}

string DeviceElementGroupImplementation::generate_Reference_ID() {
  const string BASE_ID = getElementId();
  string element_id("");

  if (BASE_ID.back() == ':') {
    element_id = to_string(elemenet_count_);
  } else {
    element_id = "." + to_string(elemenet_count_);
  }
  elemenet_count_++;
  return BASE_ID + element_id;
}
} // namespace Information_Model_Manager