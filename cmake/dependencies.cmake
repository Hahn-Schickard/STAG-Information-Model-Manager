if(NOT IS_SUBMODULE_PROJECT)
#====================================== LOGGING LIBRARY DEPENDENCY ==========================================
    configure_file(SPDLogDependency.txt spdlog-download/CMakeLists.txt)
    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/spdlog-download" )
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/spdlog-download" )
    add_subdirectory("${PROJECT_SOURCE_DIR}/libs/spdlog-src"
                     "${CMAKE_BINARY_DIR}/spdlog-build")
    include_directories(${PROJECT_SOURCE_DIR}/libs/spdlog-src-src/)
    install(
        TARGETS spdlog
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/libs/spdlog-src/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
#====================================== JSON SERIALIZER DEPENDENCY ==========================================
    message(STATUS "Configuring external dependencies")
    configure_file(JsonDependency.txt json-download/CMakeLists.txt)
    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
       WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/json-download" )
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
       WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/json-download" )
    set(JSON_INCLUDES "${PROJECT_SOURCE_DIR}/libs/json-src/single_include/")
    set(JSON_BuildTests OFF CACHE INTERNAL "")
    add_subdirectory(${PROJECT_SOURCE_DIR}/libs/json-src)
#======================================== GOOGLE TEST DEPENDENCY ============================================
    option(INSTALL_GMOCK "Install Googletest's GMock?" OFF)
    option(INSTALL_GTEST "Install Googletest's GTest?" OFF)
    configure_file(GoogleTestDependency.txt googletest-download/CMakeLists.txt)
    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("${PROJECT_SOURCE_DIR}/tests/googletest-src"
                    "${CMAKE_BINARY_DIR}/googletest-build")
    if(CMAKE_VERSION VERSION_LESS 2.8.11)
        include_directories("${gtest_SOURCE_DIR}/include"
                            "${gmock_SOURCE_DIR}/include")
    endif()
else()
    message(STATUS "${PROJECT_NAME} is configured as a submodule. Skipping commond external depenencies!")
endif()
