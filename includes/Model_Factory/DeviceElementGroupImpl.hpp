#ifndef _DEVICE_ELEMENT_GROUP_HPP
#define _DEVICE_ELEMENT_GROUP_HPP

#include "DeviceElement.hpp"
#include "DeviceElementGroup.hpp"
#include "Logger.hpp"
#include "ReadableMetricImpl.hpp"
#include "WritableMetricImpl.hpp"

#include <exception>
#include <memory>
#include <unordered_map>

namespace Model_Factory {
  /**
 * @brief This class is an implementation of
 * Information_Model::DeviceElementGroup
 * It contains all of the virtual method implementations and the building
 * mechanism
 * for Information_Model::DeviceElementGroup instances.
 * @author Dovydas Girdvainis
 * @date 18.07.2019
 */
  class DeviceElementGroupImpl : public Information_Model::DeviceElementGroup {
   private:
    std::shared_ptr<Information_Model::DeviceElement> findSubelement(
        const std::string& REF_ID);

   public:
    DeviceElementGroupImpl(const std::string& refId,
        const std::string& name,
        const std::string& desc);
    /**
   * @brief This method creates an instance of Information_Model:DeviceElement
   * class and
   * adds it to DeviceElementGroupImpl: DeviceElementGroupImpl::subelements
   * vector
   *
   * @param NAME
   * @param DESC
   * @param type
   * @return std::string Reference ID of DeviceElement within
   * DeviceElementGroupImpl: DeviceElementGroupImpl::subelements vector
   * @deprecated This method will be removed in the next release
   */
    std::string addDeviceElement(const std::string& name,
        const std::string& desc,
        Information_Model::ElementType type);

    /**
     * @brief This method creates an instance of a polymorfed Information_Model:DeviceElementGroup
     * class (morfed into Information_Model:DeviceElement) and adds it to the subelements map.
     * 
     * @param name 
     * @param desc 
     * @return std::string 
     */
    std::string addSubgroup(const std::string& name, const std::string& desc);

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
      const std::string REF_ID = generate_Reference_ID();

      logger_->log(HaSLL::SeverityLevel::TRACE,
          "Building a readable metric: {} with id {}.",
          name,
          REF_ID);
      try {
	std::pair<std::string, std::shared_ptr<DeviceElement>> element_pair(
	    REF_ID,
	    std::make_shared<ReadableMetricImpl<T>>(
	        REF_ID, name, desc, read_cb));
	subelements.insert(element_pair);
	return REF_ID;
      } catch(std::exception& e) {
	logger_->log(HaSLL::SeverityLevel::ERROR,
	    "Failed to build readable metric: {}:{}. Error: {}",
	    name,
	    REF_ID,
	    e.what());
	return nullptr;
      }
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
      const std::string REF_ID = generate_Reference_ID();

      logger_->log(HaSLL::SeverityLevel::TRACE,
          "Building a writable metric: {} with id {}.",
          name,
          REF_ID);
      try {
	std::pair<std::string, std::shared_ptr<DeviceElement>> element_pair(
	    REF_ID,
	    std::make_shared<WritableMetricImpl<T>>(
	        REF_ID, name, desc, read_cb, write_cb));
	subelements.insert(element_pair);
	return REF_ID;
      } catch(std::exception& e) {
	logger_->log(HaSLL::SeverityLevel::ERROR,
	    "Failed to build readable metric: {}:{}. Error: {}",
	    name,
	    REF_ID,
	    e.what());
	return nullptr;
      }
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
     * @brief Get the current subelements of this group
     * 
     * @return std::vector<std::shared_ptr<DeviceElement>> 
     */
    std::vector<std::shared_ptr<DeviceElement>> getSubelements();

    /**
     * @brief Get a specified subelement
     * 
     * @throw std::runtime_error() if element does not exist.
     * 
     * @param REF_ID 
     * @return std::shared_ptr<DeviceElement> 
     */
    std::shared_ptr<DeviceElement> getSubelement(const std::string& REF_ID);

   private:
    void incrementElementId();
    std::string generate_Reference_ID();
    unsigned int getNumericElementId();

    std::unordered_map<std::string,
        std::shared_ptr<Information_Model::DeviceElement>>
        subelements;
    std::shared_ptr<HaSLL::Logger> logger_;
    unsigned int elementId;
  };
}   // namespace Model_Factory

#endif   //_DEVICE_ELEMENT_GROUP_HPP