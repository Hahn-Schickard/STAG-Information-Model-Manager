cmake_minimum_required(VERSION 3.6) 

set(THIS Building_And_Registration_Facade)

list(APPEND PUBLIC_INCLUDES_DIRS
            ${INCLUDES_DIR}/Building_And_Registration_Facade
)

file(GLOB sources_list "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

INCLUDE_DIRS_AND_FILES("${PUBLIC_INCLUDES_DIRS}" PUBLIC_INCLUDES)

add_library(${THIS} SHARED
                    ${PUBLIC_INCLUDES}
)

target_sources(${THIS} PRIVATE 
                       ${sources_list}
)

target_link_libraries(${THIS} PUBLIC
                              Device_Building_And_Registration::Building_And_Registration_Interface
                              Information_Modeler::Information_Model_Interface
                              Model_Factory
                              Model_Manager
)

if (UNIX)
    target_link_libraries(${THIS} PUBLIC 
                                  gcov
    )
endif ()

target_include_directories(${THIS} INTERFACE
                           $<BUILD_INTERFACE:${INCLUDES_DIR}/Building_And_Registration_Facade/>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Building_And_Registration_Facade>
)

if(CLANG_TIDY_EXE)               
    set_target_properties(
        ${THIS} PROPERTIES
        CMAKE_CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}"
    )
    target_clangformat_setup(${THIS})
endif() 

PRINT_TARGET_PROPERTIES(${THIS})

add_custom_command(TARGET ${THIS} POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E make_directory 
                        ${CMAKE_BINARY_DIR}/bin
                    COMMAND ${CMAKE_COMMAND} -E copy 
                        $<TARGET_FILE:${THIS}> 
                        "${CMAKE_BINARY_DIR}/bin"
                    COMMENT "Copying shared library files from ${CMAKE_CURRENT_BINARY_DIR} directory to ${CMAKE_BINARY_DIR}/bin directory."
                        VERBATIM
)

install(
    TARGETS ${THIS}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    DIRECTORY ${PUBLIC_INCLUDES_DIRS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)