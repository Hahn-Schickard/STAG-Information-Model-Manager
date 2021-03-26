cmake_minimum_required(VERSION 3.12) 

set(THIS Device_Builder)

list(APPEND THIS_INCLUDES_DIRS
            ${INCLUDES_DIR}/Device_Builder
)
file(GLOB sources_list "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

INCLUDE_DIRS_AND_FILES("${THIS_INCLUDES_DIRS}" THIS_INCLUDES)

add_library(${THIS})

target_sources(${THIS} PRIVATE 
                       ${sources_list} 
                       ${THIS_INCLUDES}
)

target_link_libraries(${THIS} PUBLIC 
                              Technology_Adapter_Interface::Technology_Adapter_Interface
                              Information_Model::Information_Model
)

target_include_directories(${THIS} PUBLIC
                           $<BUILD_INTERFACE:${INCLUDES_DIR}/Device_Builder>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
)

set_target_properties(${THIS} PROPERTIES
                              CXX_STANDARD 17
                              CXX_STANDARD_REQUIRED ON
)

PRINT_TARGET_PROPERTIES(${THIS})

install(
    TARGETS ${THIS}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    FILES ${THIS_INCLUDES}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)