#include "BuildingAndRegirtrationFacade.hpp"

using namespace std;
using namespace Information_Access_Manager;
using namespace Information_Model;

void BuildingAndRegirtrationFacade::buildDeviceBase(const string UNIQUE_ID,
                                                    const string NAME,
                                                    const string DESC) {}
string BuildingAndRegirtrationFacade::buildDeviceElement(const string NAME,
                                                         const string DESC,
                                                         ElementType type) {}
string BuildingAndRegirtrationFacade::buildDeviceElement(const string GROUP_ID,
                                                         const string NAME,
                                                         const string DESC,
                                                         ElementType type) {}
unique_ptr<Device> BuildingAndRegirtrationFacade::getDevice() {}
bool BuildingAndRegirtrationFacade::registerDevice(unique_ptr<Device> device) {}
bool BuildingAndRegirtrationFacade::deregisterDevice(const string DEVICE_ID) {}