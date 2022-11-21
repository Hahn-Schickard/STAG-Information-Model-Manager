# Changelog
## [0.2.1] - 2022.11.21
### Changed
 - conan packaging recipe
 - gtest dependency to fuzzy v1.11
 - HaSLL dependency to fuzzy v0.3
 - Data_Consumer_Adapter_Interface dependency to fuzzy v0.1
 - Technology_Adapter_Interface dependency to fuzzy v0.1
 - `group_ref_id` param `DeviceImplementationBuilder` class
 - `group_ref_id` param `DeviceBuilder` class

### Added
 - `ExecuteFunctor` handling in `DeviceBuilder::addDeviceElement()`
 - `ExecuteFunctor` handling in `DeviceImplementationBuilder::addDeviceElement()` 
 - example Runner 

### Removed
 - redundant call to base ctor in `MetricImplementation`
 - redundant call to base ctor in `WritableMetricImplementation`
 - redundant call to base ctor in `DeviceElementGroupImplementation`

## [0.2.0] - 2022.10.19
### Added
 - `DeviceImplementation::getGroupImplementation`
 - `DeviceElementGroupImplementation::getSubgroupImplementation`
 - `MetricImplementation::linkMetaInfo`
 - `WritableMetricImplementation::linkMetaInfo`

### Removed
 - arguments `name` and desc from `DeviceElementGroupImplementation` constructor
 - arguments `ref_id`, `name`, and `desc` from `MetricImplementation` constructor
 - arguments `ref_id`, `name`, and `desc` from `WritableMetricImplementation` constructor
 - unused license mentions from Notice file
 - conan directory
 - conanfile.txt

### Fixed
 - Third Party license documentation in License file
 - missing `optional` include for DeviceBuilder.hpp
 - missing `optional` include for DeviceElementGroupImplementation.hpp 
 - missing `optional` include for WritableMetricImplementation.hpp  
 - missing `ARCHIVE DESTINATION` section for cmake install commands 

### Changed
 - Data_Consumer_Adapter_Interface to v0.1.9
 - Technology_Adapter_Interface to v0.1.9
 - HaSLL to v0.3.1
 - conan packaging layout
 - Contribution guide
 - code formatting rules
 - DeviceElementGroupImplementation.cpp to work with Information Model v0.2.1
 - DeviceImplementation.cpp to work with Information Model v0.2.1
 - DeviceImplementationBuilder.cpp to work with Information Model v0.2.1
 - MetricImplementation.cpp to work with Information Model v0.2.1
 - WritableMetricImplementation.cpp to work with Information Model v0.2.1
 - ModelRegistry.cpp to work with HaSLL v0.3.1

## [0.1.5] - 2021.08.09
### Changed
 - Data_Consumer_Adapter_Interface to 0.1.6
 - Technology_Adapter_Interface to 0.1.6
 - Device_Builder CmakeLists.txt to set correct install include path
 - install include paths to resolve potential header name collisions
 - utility/runValgring.py script to correct error counting
 - ModelRegistry to use AsyncEventSource

## [0.1.4] - 2020.11.16
### Changed
 - `DeviceImplementationBuilder` to set the `RefID` as RefID and `name` as name
 - Data_Consumer_Adapter_Interface to 0.1.4

## [0.1.3] - 2020.10.14
### Added
 - Concrete implementation of DeviceBuilder
 - `DeviceImplementationBuilder`
 - `DeviceImplementationBuilder` unit tests
 - Data_Consumer_Adapter_Interface v0.1.3 dependency
 - `getModelEventSource()` method

### Removed
 - Device_Builder dependency
 - Device_Building_And_Registration dependency
 - Direct Information_Model dependency
 - Model_Event_Handler dependency

### Changed
 - ModelManager to Model Registry
 - Technology Manager implementation to fit with 0.1.4 declaration
 - Class member field ordering for Device_Builder class definitions
 - Model Registry to implement EventSource for Data_Consumer_Adapter_Interface
 - Integration test to load proper symbols
 - TechnologyManager to ModelManager

## [0.1.2] - 2020.10.02
### Changed
 - Information_Model to 0.1.2
 - Model_Event_Handler to 0.1.2
 - Device_Builder to 0.1.2
 - Device_Building_And_Registration to 0.1.2
 - Technology_Adapter_Interface to 0.1.2
 - Building and Registration Facade to use optional parameters for `addDeviceElement()`

## [0.1.1] - 2020.09.28
### Removed
 - builder_tests directory from unit_tests
 - ModelImlementationTestSuite
 - DeviceBuilderTestSuite

### Changed
 - Information Model to 0.1.1
 - Model Event Handler to 0.1.1
 - Device Builder to 0.1.1
 - Device Building And Registration to 0.1.1
 - Technology Adapter Interface to 0.1.1
 - `getElementRefId()` to `getElementId()`

### Added
 - TechnologyManagerTestSuite placeholder directory
 - ModelManagerTestSuite placeholder directory
 - BuildingAndRegistrationFacadeTestSuite placeholder directory

## [0.1.0] - 2020.09.17
### Removed
 - modules
 - runner

### Changed
 - test case source file extensions
 - CMakeLists.txt to use Cmake 3.x best practices
 - auto generated doc style
 - utility scripts to use python
 - clang-format rules
 - tests into unit_tests
 - cmake modules

### Added
 - conan package configuration
 - License
 - Notice
 - Authors
 - Contributing
 - conan dependency handling
 - conan packaging
 - conan package integration test
 - Device Builder dependency
