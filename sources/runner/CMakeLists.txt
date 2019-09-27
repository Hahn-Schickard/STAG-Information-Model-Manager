cmake_minimum_required(VERSION 3.6) 

set(THIS ${PROJECT_NAME}_Runner_MAIN)

file(GLOB sources_list "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

INCLUDE_DIRS_AND_FILES(PUBLIC_INCLUDES_DIRS PUBLIC_INCLUDES)
PRINT_MODULE_FILES(${THIS} ${sources_list} "${PUBLIC_INCLUDES}")

add_executable(${THIS} 
               ${PUBLIC_INCLUDES}
)

target_sources(${THIS} PRIVATE 
               ${sources_list}
)

target_link_libraries(${THIS} PUBLIC
                              Information_Modeler::Information_Model_Interface
                              Model_Factory
                              Model_Manager
)

if (UNIX)
    target_link_libraries(${THIS} PUBLIC 
                                  gcov
    )
endif ()

PRINT_TARGET_LIBS("${THIS}")

if(CLANG_TIDY_EXE)               
    set_target_properties(
        ${THIS} PROPERTIES
        CMAKE_CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}"
)
endif()   

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
    RUNTIME 
    DESTINATION ${BINS_DEST}
    COMPONENT libraries
)

install(
    DIRECTORY ${PUBLIC_INCLUDES_DIRS}
    DESTINATION ${INCLUDES_DEST}
    COMPONENT headers
)