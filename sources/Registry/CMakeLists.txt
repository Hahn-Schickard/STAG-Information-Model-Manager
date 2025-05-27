cmake_minimum_required(VERSION 3.6) 


#@+ ======================== User MODULE NAME configuration ============================
set(THIS Registry)
#@- =========================== END OF USER CONFIGURATION ===============================

set(MODULE ${PROJECT_NAME}_${THIS})


list(APPEND THIS_INCLUDES_DIRS
            ${INCLUDES_DIR}/Registry
)

file(GLOB sources_list "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

INCLUDE_DIRS_AND_FILES("${THIS_INCLUDES_DIRS}" THIS_INCLUDES)

add_library(${MODULE})                

target_sources(${MODULE} PRIVATE 
                       ${THIS_INCLUDES}
                       ${sources_list}
)

target_link_libraries(${MODULE} PUBLIC
                              Technology_Adapter_Interface::Technology_Adapter_Interface
                              Data_Consumer_Adapter_Interface::Data_Consumer_Adapter_Interface
                              HaSLL::HaSLL
)

target_include_directories(${MODULE} INTERFACE
                           $<BUILD_INTERFACE:${INCLUDES_DIR}/Registry/>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
)

set_target_properties(${MODULE} PROPERTIES
                              CXX_STANDARD 17
                              CXX_STANDARD_REQUIRED ON
)

PRINT_TARGET_PROPERTIES(${MODULE})

target_compile_features(${MODULE} INTERFACE cxx_std_17)

install(
    TARGETS ${MODULE}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    FILES ${THIS_INCLUDES}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)
