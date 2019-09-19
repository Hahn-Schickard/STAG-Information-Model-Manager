#include "ModelManager.hpp"
#include "DeviceBuilder.hpp"
#include "Listener.hpp"
#include <iostream>
#include <memory>

using namespace std;
using namespace Model_Manager;
using namespace Information_Model;
using namespace Model_Factory;

string
elementType_str(ElementType elementType)
{
    switch (elementType)
    {
    case ElementType::Undefined:
        return "Undefined";
    case ElementType::Group:
        return "Group";
    case ElementType::Readonly:
        return "Readonly";
    case ElementType::Observable:
        return "Observable";
    case ElementType::Writable:
        return "Writable";
    case ElementType::Function:
        return "Function";
    }
    return to_string(elementType);
}

void printElement(DeviceElement *element)
{
    cout << "Element: " << element->getElementName()
         << " has a ref_id: " << element->getElementRefId()
         << ", is of type: " << elementType_str(element->getElementType())
         << " and is described as: " << element->getElementDescription()
         << endl;
}

void printSubelements(vector<shared_ptr<DeviceElement>> elements)
{
    cout << "It has " << elements.size() << " elements" << endl;
    for (auto element : elements)
    {
        printElement(element.get());
    }

    for (auto element : elements)
    {
        if (element->getElementType() == Group)
        {
            cout << "\n\n==== SUBGROUP: " << element->getElementName() << " >>>\n"
                 << endl;
            DeviceElementGroup *groupElement = static_cast<DeviceElementGroup *>(element.get());
            auto subElements = groupElement->getSubelements();
            if (subElements.size() > 0)
                printSubelements(subElements);
            cout << "\n<<< SUBGROUP: " << element->getElementName() << "\n"
                 << endl;
        }
    }
}

void printDevice(Device *device)
{
    cout << "Device: " << device->getElementName()
         << " has a ref_id: " << device->getElementRefId()
         << " and is described as: " << device->getElementDescription() << endl;

    vector<shared_ptr<DeviceElement>> elements = device->getDeviceElementGroup()->getSubelements();
    printSubelements(elements);
}

class SimpelListener : public Notifier::Listener
{
public:
    void handleEvent(Device *device)
    {
        printDevice(device);
    }
};

unique_ptr<Device> makeTestDevice(){
    DeviceBuilder *builder = new DeviceBuilder("TestDevice","1234","This is a TestDevice");
    std::string basegroupID = builder->addDeviceElementGroup("BaseGroup","This is BaseGroup");
    builder->addDeviceElement(basegroupID, "SubTestDevice","This is the first Subelement", ElementType::Readonly);
    std::string subgroupID = builder->addDeviceElement("TestGroup", "This is a synthetic test for device element group.", ElementType::Group);
    builder->addDeviceElement(subgroupID, "Sub2TestDevice","This is the second Subelement", ElementType::Readonly);
    unique_ptr<Device> device = builder->getDevice();

    delete builder;
    return move(device);
}

int main()
{
    ModelManager *model_manager = new ModelManager();
    SimpelListener *this_listemer = new SimpelListener();
    model_manager->registerListener(this_listemer);

    unique_ptr<Device> local_scope_device = makeTestDevice();
    model_manager->registerDevice(move(local_scope_device));

    exit(0);
}