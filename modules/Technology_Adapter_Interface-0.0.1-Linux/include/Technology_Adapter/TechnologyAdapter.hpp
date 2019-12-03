#ifndef __TECHNOLOGY_ADAPTER_HPP
#define __TECHNOLOGY_ADAPTER_HPP

#include "AbstractionFactory.hpp"
#include "BuildingAndRegistrationInterface.hpp"
#include <memory>

namespace Information_Access_Manager {
class TechnologyAdapter {
public:
  bool setBuildingAndRegistrationInterface(
      std::shared_ptr<
          Information_Model_Static_Part::BuildingAndRegistrationInterface>
          building_and_registration_interface) {
    if (!abstraction_factory_) {
      abstraction_factory_ =
          new AbstractionFactory(building_and_registration_interface);
      BuildingAndRegistrationInterfaceWasSet();
    }
  }

  TechnologyAdapter(std::string name) : adapter_name_(name) {
    abstraction_factory_ = nullptr;
  }

  virtual bool start() = 0;
  virtual bool isRunning() = 0;
  virtual void BuildingAndRegistrationInterfaceWasSet() = 0;
  virtual bool stop() = 0;

  AbstractionFactory *getAbstractionFactory() { return abstraction_factory_; }

  ~TechnologyAdapter() {
    if (abstraction_factory_) {
      delete abstraction_factory_;
    }
  }

private:
  std::string adapter_name_;
  AbstractionFactory *abstraction_factory_;
};
} // namespace Information_Access_Manager

#endif //__TECHNOLOGY_ADAPTER_HPP