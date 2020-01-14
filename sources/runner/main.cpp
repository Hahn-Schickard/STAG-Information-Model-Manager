#include "DeviceBuilder.hpp"
#include "Listener.hpp"
#include "ModelManager.hpp"

#include <iostream>
#include <memory>

using namespace std;
using namespace Model_Manager;
using namespace Information_Model;
using namespace Model_Factory;

string elementType_str(ElementType elementType) {
  switch(elementType) {
    case ElementType::UNDEFINED:
      return "Undefined";
    case ElementType::GROUP:
      return "Group";
    case ElementType::READABLE:
      return "Readonly";
    case ElementType::OBSERVABLE:
      return "Observable";
    case ElementType::WRITABLE:
      return "Writable";
    case ElementType::FUNCTION:
      return "Function";
  }
  return to_string(elementType);
}

void printElement(const shared_ptr<DeviceElement>& element) {
  cout << "Element: " << element->getElementName()
       << " has a ref_id: " << element->getElementRefId()
       << ", is of type: " << elementType_str(element->getElementType())
       << " and is described as: " << element->getElementDescription() << endl;
}

void printSubelements(vector<shared_ptr<DeviceElement>> elements) {
  cout << "It has " << elements.size() << " elements" << endl;
  for(auto const& element : elements) {
    printElement(element);
  }

  for(auto const& element : elements) {
    if(element->getElementType() == GROUP) {
      cout << "\n\n==== SUBGROUP: " << element->getElementName() << " >>>\n"
           << endl;
      DeviceElementGroup* group_element
          = static_cast<DeviceElementGroup*>(element.get());
      auto sub_elements = group_element->getSubelements();
      if(sub_elements.size() > 0)
	printSubelements(sub_elements);
      cout << "\n<<< SUBGROUP: " << element->getElementName() << "\n" << endl;
    }
  }
}

void printDevice(const shared_ptr<Device>& device) {
  cout << "Device: " << device->getElementName()
       << " has a ref_id: " << device->getElementRefId()
       << " and is described as: " << device->getElementDescription() << endl;

  vector<shared_ptr<DeviceElement>> elements
      = device->getDeviceElementGroup()->getSubelements();
  printSubelements(elements);
}

class SimpelListener : public Model_Event_Handler::Listener {
 public:
  void handleEvent(shared_ptr<Model_Event_Handler::NotifierEvent> event) {
    if(event->getEventType()
        == Model_Event_Handler::NotifierEventType::NEW_DEVICE_REGISTERED) {
      printDevice(event->getEvent()->device);
    }
  }
};

shared_ptr<Device> makeTestDevice() {
  DeviceBuilder* builder
      = new DeviceBuilder("TestDevice", "1234", "This is a TestDevice");
  string basegroup_id = builder->addDeviceElement(
      "BaseGroup", "This is BaseGroup", ElementType::GROUP);
  builder->addDeviceElement(basegroup_id,
      "SubTestDevice",
      "This is the first Subelement",
      ElementType::READABLE);
  string subgroup_id = builder->addDeviceElement("TestGroup",
      "This is a synthetic test for device element group.",
      ElementType::GROUP);
  builder->addDeviceElement(subgroup_id,
      "Sub2TestDevice",
      "This is the second Subelement",
      ElementType::READABLE);
  shared_ptr<Device> device = builder->getDevice();

  delete builder;
  return move(device);
}

int main() {
  ModelManager* model_manager = model_manager->getInstance();
  model_manager->registerListener(
      static_pointer_cast<Model_Event_Handler::Listener>(
          make_shared<SimpelListener>()));
  model_manager->registerDevice(move(makeTestDevice()));

  delete model_manager;

  exit(0);
}