cmake_minimum_required(VERSION 3.6)

set(THIS Unit_Tests_Runner)

file(GLOB BuildingAndRegistrationFacadeTestSuite "${CMAKE_CURRENT_LIST_DIR}/DeviceBuilderTestSuite/*")
file(GLOB ModelManagerTestSuite "${CMAKE_CURRENT_LIST_DIR}/DeviceBuilderTestSuite/*")
file(GLOB TechnologyManagerTestSuite "${CMAKE_CURRENT_LIST_DIR}/ModelImlementationTestSuite/*")

find_package(GTest REQUIRED)

add_executable(${THIS})
target_sources(${THIS} PRIVATE 
                       "testRunner.cpp"
                       ${BuildingAndRegistrationFacadeTestSuite}
                       ${ModelManagerTestSuite}
                       ${TechnologyManagerTestSuite}
)

target_link_libraries(${THIS} PUBLIC
                              GTest::GTest
                              Information_Model::Information_Model
                              Building_And_Registration_Facade
                              Model_Manager
                              Technology_Manager
)

add_test(
    NAME ${THIS}
    COMMAND ${THIS}
)

set_target_properties(${THIS} PROPERTIES
                              CXX_STANDARD 17
)
