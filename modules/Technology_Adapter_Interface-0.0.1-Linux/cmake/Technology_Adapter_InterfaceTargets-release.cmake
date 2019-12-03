#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Technology_Adapter_Interface::Abstraction_Factory" for configuration "Release"
set_property(TARGET Technology_Adapter_Interface::Abstraction_Factory APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Technology_Adapter_Interface::Abstraction_Factory PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libAbstraction_Factory.so"
  IMPORTED_SONAME_RELEASE "libAbstraction_Factory.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS Technology_Adapter_Interface::Abstraction_Factory )
list(APPEND _IMPORT_CHECK_FILES_FOR_Technology_Adapter_Interface::Abstraction_Factory "${_IMPORT_PREFIX}/lib/libAbstraction_Factory.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
