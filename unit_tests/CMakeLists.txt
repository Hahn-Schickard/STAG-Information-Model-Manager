cmake_minimum_required(VERSION 3.6)

set(THIS Unit_Tests_Runner)

file(GLOB Device_Test_Suite "${CMAKE_CURRENT_LIST_DIR}/Device_Tests/*")
file(GLOB Model_Event_Source_Tests "${CMAKE_CURRENT_LIST_DIR}/Model_Event_Source_Tests/*")

find_package(GTest REQUIRED)

add_executable(${THIS})
target_sources(${THIS} PRIVATE 
                       "testRunner.cpp"
                       ${Device_Test_Suite}
                       ${Model_Event_Source_Tests}
)

target_link_libraries(${THIS} PUBLIC
                              GTest::GTest
                              Model_Manager
)

add_test(
    NAME ${THIS}
    COMMAND ${THIS}
)

set_target_properties(${THIS} PROPERTIES
                              CXX_STANDARD 17
)
