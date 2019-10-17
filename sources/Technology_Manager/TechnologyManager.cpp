#include "TechnologyManager.hpp"
#include "BuildingAndRegirtrationFacade.hpp"
#include <algorithm>

using namespace std;
using namespace Information_Access_Manager;
using namespace Information_Model_Static_Part;

TechnologyManager::TechnologyManager() {
  building_and_registration_facade_ =
      shared_ptr<BuildingAndRegistrationInterface>(
          new BuildingAndRegirtrationFacade());
}

vector<shared_ptr<TechnologyAdapter>>::iterator
TechnologyManager::findTechnologyAdapter(
    shared_ptr<TechnologyAdapter> adapter) {
  return find(technology_adapters_.begin(), technology_adapters_.end(),
              adapter);
}

bool TechnologyManager::registerTechnologyAdapter(
    shared_ptr<TechnologyAdapter> adapter) {

  auto iterator = findTechnologyAdapter(adapter);
  if (iterator == technology_adapters_.end()) {
    if (adapter->setBuildingAndRegistrationInterface(
            building_and_registration_facade_)) {
      technology_adapters_.push_back(adapter);
      return true;
    } else {
      // @TODO: Log smtnhg
      return false;
    }

  } else {
    //@TODO: Add logging/exception throwing here
    return false;
  }
}

bool TechnologyManager::deregisterTechnologyAdapter(
    shared_ptr<TechnologyAdapter> adapter) {
  auto iterator = findTechnologyAdapter(adapter);

  if (iterator != technology_adapters_.end()) {
    technology_adapters_.erase(iterator);
    return true;
  } else {
    //@TODO: Add logging/exception throwing here
    return false;
  }
}

TechnologyManager *TechnologyManager::getInstance() {
  if (!instance_) {
    instance_ = new TechnologyManager();
  }
  return instance_;
}

TechnologyManager::~TechnologyManager() { technology_adapters_.clear(); }

TechnologyManager *TechnologyManager::instance_ = 0;