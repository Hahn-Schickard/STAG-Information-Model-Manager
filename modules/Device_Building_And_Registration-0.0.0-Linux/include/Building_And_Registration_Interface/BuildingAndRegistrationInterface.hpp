#ifndef __BUILDING_AND_REGISTRATION_INTERFACE_HPP
#define __BUILDING_AND_REGISTRATION_INTERFACE_HPP

#include "Device.hpp"
#include <memory>
#include <string>

/**
 * @brief This Namespace contains the static elements within Information Model,
 * these elements do not change their information during their lifetime.
 */
namespace Information_Model_Static_Part {
/**
 * @brief This Interface is the main entry point for Device modellign and
 * registration for various Technology adapter implementations. It is
 * implemented and provided by Information Access Manager Component and works as
 * a Facade for various subcomponents.
 * @author Dovydas Girdvainis
 * @date 25.09.2019
 */
class BuildingAndRegistrationInterface {
public:
  virtual void buildDeviceBase(const std::string &UNIQUE_ID,
                               const std::string &NAME,
                               const std::string &DESC) = 0;

  /**
   * @brief Primary method for device element creation. Elementes created by
   * this method will always be in the root level.
   *
   * @param NAME - name of this element
   * @param DESC - description for this element
   * @param type - element type. @see Information_Model::ElementType
   * @return std::string - ID of this element.
   */
  virtual std::string
  buildDeviceElement(const std::string &NAME, const std::string &DESC,
                     Information_Model::ElementType type) = 0;
  /**
   * @brief This method allows the caller to add nested device elements.
   *
   * @param GROUP_ID - Parent element ID. This element MUST always be of GROUP
   * type.
   * @param NAME - name of this element
   * @param DESC - description for this element
   * @param type - element type. @see Information_Model::ElementType
   * @return std::string - ID of this element.
   */
  virtual std::string
  buildDeviceElement(const std::string &GROUP_ID, const std::string &NAME,
                     const std::string &DESC,
                     Information_Model::ElementType type) = 0;

  /**
   * @brief Returns a fully built Device instance. If any signature type of
   * Information_Model_Static_Part::BuildingAndRegistrationInterface::buildDeviceElement
   * method has been called, this method will return a Device with root group
   * only. This method relinquishes ownership of the Object to the caller.
   *
   * @return std::unique_ptr<Information_Model::Device>
   */
  virtual std::shared_ptr<Information_Model::Device> getDevice() = 0;

  /**
   * @brief This method takes ownership of a given Device instance and registers
   * it within the Information Model. This method MUST be called like this:
   * @code{.cpp}
   * auto device = BuildingAndRegistrationInterface->getDevice();
   * BuildingAndRegistrationInterface->registerDevice(move(device));
   * @endcode
   *
   * @param device
   * @return true - registration succeeded
   * @return false - registration failled
   */
  virtual bool
  registerDevice(std::shared_ptr<Information_Model::Device> device) = 0;

  /**
   * @brief This method deletes a given Device, identified by its ID.
   *
   * @param DEVICE_ID
   * @return true - deletion succeeded
   * @return false - deletion failled
   */
  virtual bool deregisterDevice(const std::string &DEVICE_ID) = 0;

  virtual ~BuildingAndRegistrationInterface() = default;
};

} // namespace Information_Model_Static_Part

#endif //__BUILDING_AND_REGISTRATION_INTERFACE_HPP