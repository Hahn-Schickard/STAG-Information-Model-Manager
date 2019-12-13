#ifndef _DEVICE_FACTORY_HPP
#define _DEVICE_FACTORY_HPP

#include "DeviceElement.hpp"
#include "DeviceImpl.hpp"
#include "Logger.hpp"
#include "ReadableMetricImpl.hpp"
#include "WritableMetricImpl.hpp"

#include <memory>

/**
 * @brief This namespace contains all of the implementations of
 * Information_Model classes and
 * building mechanisms for their instances. It should only be used to create a
 * Device Model and
 * not as it's representatin.
 */
namespace Model_Factory {

  /**
 * @brief This class constructs an instance of Model_Factory::DevicImpl as a
 * Infromation_Model::Device
 * @author Dovydas Girdvainis
 * @date 18.07.2019
 */
  class DeviceBuilder {
   private:
    std::shared_ptr<Model_Factory::DeviceElementGroupImpl>
    getDeviceElementGroup();
    std::string addDeviceElementToSubgroup(
        std::shared_ptr<Model_Factory::DeviceElementGroupImpl> parentGroup,
        const std::string& GROUP_REFID,
        const std::string& NAME,
        const std::string& DESC,
        Information_Model::ElementType type);
    std::shared_ptr<Model_Factory::DeviceElementGroupImpl> getSubelementGroup(
        std::shared_ptr<Model_Factory::DeviceElementGroupImpl>
            deviceElementGroup,
        const std::string& REFID);
    std::shared_ptr<Model_Factory::DeviceElementGroupImpl> findElementGroup(
        const std::string& REFID,
        std::shared_ptr<Model_Factory::DeviceElementGroupImpl>
            deviceElementGroup);

   public:
    DeviceBuilder(const std::string& NAME,
        const std::string& REF_ID,
        const std::string& DESC);

    /**
   * @brief This method calls DeviceElementGroupImpl::addDeviceElement() method
   * to
   * create an instance of Information_Model:DeviceElement class
   *
   * @param NAME
   * @param DESC
   * @param type
   * @return std::string Reference ID of  Information_Model:DeviceElement
   * @deprecated this method wil lbe removed with next release 
   * instance
   */
    std::string addDeviceElement(const std::string& NAME,
        const std::string& DESC,
        Information_Model::ElementType type);

    /**
   * @brief This method calls DeviceElementGroupImpl::addDeviceElement() method
   * to
   * create an instance of Information_Model:DeviceElement class
   *
   * @param NAME
   * @param DESC
   * @param type
   * @return std::string Reference ID of  Information_Model:DeviceElement
   * @deprecated this method wil lbe removed with next release 
   * instance
   */
    std::string addDeviceElement(const std::string& GROUP_REFID,
        const std::string& NAME,
        const std::string& DESC,
        Information_Model::ElementType type);

    /**
     * @brief This method creates an instance of a polymorfed Information_Model:ReadableMetric 
     * class (morfed into Information_Model:DeviceElement) and adds it to the subelements map.
     * 
     * @tparam T - fundamental data type, described by Information_Model::DataTypeEnum
     * @param name 
     * @param desc 
     * @param read_cb 
     * @return std::string - nullptr on failure
     */
    template<typename T>
    std::string addReadableMetric(const std::string& name,
        const std::string& desc,
        std::function<Information_Model::DataWrapper<T>()> read_cb) {
      auto device_element_group
          = std::static_pointer_cast<DeviceElementGroupImpl>(
              device->getDeviceElementGroup());
      const std::string REF_ID
          = device_element_group->addReadableMetric(name, desc, read_cb);
      return REF_ID;
    }

    /**
     * @brief This method creates an instance of a polymorfed Information_Model:WritableMetric 
     * class (morfed into Information_Model:DeviceElement) and adds it to the subelements map.
     * 
     * @tparam T - fundamental data type, described by Information_Model::DataTypeEnum
     * @param name 
     * @param desc 
     * @param read_cb 
     * @param write_cb 
     * @return std::string - nullptr on failure
     */
    template<typename T>
    std::string addWritableMetric(const std::string& name,
        const std::string& desc,
        std::function<Information_Model::DataWrapper<T>()> read_cb,
        std::function<void(Information_Model::DataWrapper<T>)> write_cb) {
      auto device_element_group
          = std::static_pointer_cast<DeviceElementGroupImpl>(
              device->getDeviceElementGroup());
      const std::string REF_ID = device_element_group->addWritableMetric(
          name, desc, read_cb, write_cb);
      return REF_ID;
    }

    /**
     * @brief This method creates an instance of a polymorfed Information_Model:ObservableMetric 
     * class (morfed into Information_Model:DeviceElement) and adds it to the subelements map.
     * 
     * @tparam T  - fundamental data type, described by Information_Model::DataTypeEnum
     * @param name 
     * @param desc 
     * @param notify_cb 
     * @return std::string - nullptr on failure
     */
    template<typename T>
    std::string addObservableMetric(const std::string& name,
        const std::string& desc,
        std::function<Information_Model::DataWrapper<T>()> notify_cb) {
      logger_->log(HaSLL::SeverityLevel::ERROR,
          "Observable metric build is not implemented!");
      return nullptr;
    }

    /**
     * @brief This method creates an instance of a polymorfed Information_Model:Function
     * class (morfed into Information_Model:DeviceElement) and adds it to the subelements map.
     * 
     * @param name 
     * @param desc 
     * @return std::string - nullptr on failure
     */
    std::string addFunction(const std::string& name, const std::string& desc);

    /**
   * @brief This method returns a pointer with full ownership rights.
   * @attention If this pointer is not saved by the caller, it will be cleaned
   * up by the
   * Garbadge collector.
   *
   * @return std::unique_ptr<Information_Model::Device>
   */
    // std::unique_ptr<Information_Model::Device> getDevice();  //bearbeitet
    std::shared_ptr<Information_Model::Device> getDevice();

   private:
    std::shared_ptr<Information_Model::Device> device;
    std::shared_ptr<HaSLL::Logger> logger_;
  };   // namespace Model_Factory
}   // namespace Model_Factory

#endif   //_DEVICE_FACTORY_HPP