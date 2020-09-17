#include "DeviceElementGroupImpl.hpp"

#include "DeviceElement.hpp"
#include "DeviceElementBuilder.hpp"
#include "DeviceGroupBuilder.hpp"
#include "LoggerRepository.hpp"

#include <exception>
#include <memory>

using namespace std;
using namespace HaSLL;
using namespace Model_Factory;
using namespace Information_Model;

DeviceElementGroupImpl::DeviceElementGroupImpl(const string& ref_Id,
    const string& name,
    const string& desc)
    : DeviceElementGroup(ref_Id, name, desc)
    , logger_(LoggerRepository::getInstance().registerTypedLoger(this)) {
  elementId = 0;
}

string DeviceElementGroupImpl::addDeviceElement(const string& name,
    const string& desc,
    ElementType element_Type) {
  const string REF_ID = generate_Reference_ID();

  switch(element_Type) {
    case ElementType::GROUP: {
      pair<string, shared_ptr<DeviceElementGroup>> element_pair(REF_ID,
          shared_ptr<DeviceElementGroup>(
              new DeviceGroupBuilder(REF_ID, name, desc)));
      subelements.insert(element_pair);
    }; break;
    case ElementType::OBSERVABLE:
    case ElementType::WRITABLE:
    case ElementType::READABLE: {
      addReadableMetric(name, desc);
      break;
    }
    case ElementType::FUNCTION: {
      //@TODO remove at once Readonly when it is implemented
      pair<string, shared_ptr<DeviceElement>> element_pair(REF_ID,
          shared_ptr<DeviceElement>(new Model_Factory::DeviceElementBuilder(
              REF_ID, name, desc, element_Type)));
      subelements.insert(element_pair);
    }; break;
    default: {}
  }
  return REF_ID;
}

string DeviceElementGroupImpl::addSubgroup(const string& name,
    const string& desc) {
  const string REF_ID = generate_Reference_ID();

  logger_->log(SeverityLevel::TRACE,
      "Building a subgroup element: {} with id {}.",
      name,
      REF_ID);
  pair<string, shared_ptr<DeviceElement>> element_pair(
      REF_ID, make_shared<DeviceGroupBuilder>(REF_ID, name, desc));
  subelements.insert(element_pair);

  return REF_ID;
}

string DeviceElementGroupImpl::addFunction(const string& name,
    const string& desc) {
  logger_->log(SeverityLevel::ERROR, "Function build is not implemented!");
  return nullptr;
}

shared_ptr<Information_Model::DeviceElement>
DeviceElementGroupImpl::findSubelement(const string& ref_Id) {
  if(subelements.find(ref_Id) != subelements.end())
    return subelements.at(ref_Id);

  for(auto el = subelements.begin(); el != subelements.end(); ++el) {
    if(el->second->getElementType() == ElementType::GROUP) {
      auto group_element
          = static_cast<DeviceElementGroupImpl*>(el->second.get());
      auto subelement = group_element->findSubelement(ref_Id);
      if(subelement != nullptr) {
	return subelement;
      }
    }
  }

  return nullptr;
}

shared_ptr<Information_Model::DeviceElement>
DeviceElementGroupImpl::getSubelement(const string& ref_Id) {
  auto el = findSubelement(ref_Id);
  if(el != nullptr)
    return el;
  else
    throw runtime_error("RefId " + ref_Id + " not found.");
}

vector<shared_ptr<Information_Model::DeviceElement>>
DeviceElementGroupImpl::getSubelements() {
  vector<shared_ptr<Information_Model::DeviceElement>> v_subelements;
  //NOLINTNEXTLINE
  for(auto elelement : subelements) {
    v_subelements.push_back(elelement.second);
  }
  return v_subelements;
}

void DeviceElementGroupImpl::incrementElementId() {
  elementId++;
}

unsigned int DeviceElementGroupImpl::getNumericElementId() {
  return elementId;
}

string DeviceElementGroupImpl::generate_Reference_ID() {
  const string BASE_ID = this->getElementRefId();
  string element_id    = "";
  auto elemen_id_int   = getNumericElementId();

  if(BASE_ID.back() == ':')
    element_id = to_string(elemen_id_int);
  else
    element_id = "." + to_string(elemen_id_int);
  incrementElementId();
  return BASE_ID + element_id;
}