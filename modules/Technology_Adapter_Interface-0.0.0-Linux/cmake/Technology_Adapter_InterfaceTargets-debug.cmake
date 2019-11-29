#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Technology_Adapter_Interface::Technology_Adapter" for configuration "Debug"
set_property(TARGET Technology_Adapter_Interface::Technology_Adapter APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Technology_Adapter_Interface::Technology_Adapter PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libTechnology_Adapter.so"
  IMPORTED_SONAME_DEBUG "libTechnology_Adapter.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS Technology_Adapter_Interface::Technology_Adapter )
list(APPEND _IMPORT_CHECK_FILES_FOR_Technology_Adapter_Interface::Technology_Adapter "${_IMPORT_PREFIX}/lib/libTechnology_Adapter.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
