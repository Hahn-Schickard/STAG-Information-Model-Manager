cmake_minimum_required(VERSION 3.6) 

set(THIS Runner)

file(GLOB sources_list "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

add_executable(${THIS})

target_sources(${THIS} PRIVATE 
               ${sources_list}
)

target_link_libraries(${THIS} PUBLIC
                              Information_Model::Information_Model
                              Model_Factory
                              Model_Manager
)

PRINT_TARGET_PROPERTIES(${THIS})