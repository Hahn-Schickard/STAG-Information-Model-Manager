cmake_minimum_required(VERSION 3.6)

set(THIS Unit_Tests_Runner)

file(GLOB Device_Test_Suite "${CMAKE_CURRENT_LIST_DIR}/Device_Tests/*")
file(GLOB Device_Builder_Test_Suite "${CMAKE_CURRENT_LIST_DIR}/Device_Builder_Tests/*")
file(GLOB Model_Event_Source_Tests "${CMAKE_CURRENT_LIST_DIR}/Model_Event_Source_Tests/*")

#@+ ====================== User TEST_SUITES configuration ==========================
list(APPEND TEST_SUITES
                       ${Device_Test_Suite}
                       ${Device_Builder_Test_Suite}
                       ${Model_Event_Source_Tests}
)
#@- ========================= END OF USER CONFIGURATION ============================

find_package(GTest REQUIRED)

add_executable(${THIS})
target_sources(${THIS} PRIVATE
                       "testRunner.cpp"
                       ${TEST_SUITES}
)

#@+ ==================== User TEST_DEPENDCIES configuration =======================
list(APPEND TEST_DEPENDCIES
                              Model_Manager
                              Device_Builder
)
#@- ========================= END OF USER CONFIGURATION ===========================

target_link_libraries(${THIS} PUBLIC
                              ${TEST_DEPENDCIES}
                              GTest::gtest
)

add_test(
    NAME ${THIS}
    COMMAND ${THIS}
)

set_target_properties(${THIS} PROPERTIES
                              CXX_STANDARD 17
)
