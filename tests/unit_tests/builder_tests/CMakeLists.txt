cmake_minimum_required(VERSION 3.6)

set(THIS Model_Manager_Test_Suite)

include_directories(${PROJECT_SOURCE_DIR}/includes/Utilities/)

file(GLOB Model_Implementation_Test_Suite "${CMAKE_CURRENT_LIST_DIR}/ModelImlementationTestSuite/*")
file(GLOB Device_Builder_Test_Suite "${CMAKE_CURRENT_LIST_DIR}/DeviceBuilderTestSuite/*")
file(GLOB Model_Manager_Test_Suite_HEADERS "${CMAKE_CURRENT_LIST_DIR}/*.hpp")

add_executable(${THIS} 
               ${Model_Implementation_Test_Suite}
               ${Device_Builder_Test_Suite}
               ${Model_Manager_Test_Suite_HEADERS}
)

target_link_libraries(${THIS} PUBLIC    
                              Information_Modeler::Information_Model_Interface
                              Model_Factory
                              gtest_main
)

add_test(
    NAME ${THIS}
    COMMAND ${THIS}
)

if(CLANG_TIDY_EXE)               
    set_target_properties(
        ${THIS} PROPERTIES
        CMAKE_CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}"
)
endif() 

if(WIN32)
    add_custom_command(TARGET ${THIS} POST_BUILD 
                        COMMAND ${CMAKE_COMMAND} -E copy_directory 
                            "${CMAKE_BINARY_DIR}/bin/"
                            $<TARGET_FILE_DIR:${THIS}> 
                        COMMENT "Copying shared library files from ${CMAKE_BINARY_DIR}/bin directory to ${CMAKE_CURRENT_BINARY_DIR} directory."
                            VERBATIM) 
endif()