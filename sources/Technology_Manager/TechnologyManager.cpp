#include "TechnologyManager.hpp"
#include <algorithm>

using namespace std;
using namespace Information_Access_Manager;

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
    technology_adapters_.push_back(adapter);
  }
}

bool TechnologyManager::deregisterTechnologyAdapter(
    shared_ptr<TechnologyAdapter> adapter) {
  auto iterator = findTechnologyAdapter(adapter);

  if (iterator != technology_adapters_.end()) {
    technology_adapters_.erase(iterator);
  }
}

TechnologyManager *TechnologyManager::getInstance() {
  if (!instance_) {
    instance_ = new TechnologyManager();
  }
  return instance_;
}

TechnologyManager *TechnologyManager::instance_ = 0;