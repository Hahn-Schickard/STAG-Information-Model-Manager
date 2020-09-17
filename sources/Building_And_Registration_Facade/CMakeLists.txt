cmake_minimum_required(VERSION 3.6) 

set(THIS Building_And_Registration_Facade)

list(APPEND THIS_INCLUDES_DIRS
            ${INCLUDES_DIR}/Building_And_Registration_Facade
)

file(GLOB sources_list "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

INCLUDE_DIRS_AND_FILES("${THIS_INCLUDES_DIRS}" THIS_INCLUDES)

add_library(${THIS})                

target_sources(${THIS} PRIVATE 
                       ${THIS_INCLUDES}
                       ${sources_list}
)

target_link_libraries(${THIS} PUBLIC
                              Device_Building_And_Registration::Device_Building_And_Registration
                              Information_Model::Information_Model
                              Model_Factory
                              Model_Manager
)

target_include_directories(${THIS} INTERFACE
                           $<BUILD_INTERFACE:${INCLUDES_DIR}/Building_And_Registration_Facade/>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Building_And_Registration_Facade>
)

target_compile_features(${THIS} PUBLIC cxx_std_17)

PRINT_TARGET_PROPERTIES(${THIS})

install(
    TARGETS ${THIS}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    FILES ${THIS_INCLUDES}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
