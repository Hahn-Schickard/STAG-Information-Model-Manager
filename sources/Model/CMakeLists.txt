#@+ ======================== User TARGET NAME configuration =============================
set(THIS Model)
#@- =========================== END OF USER CONFIGURATION ===============================

set(TARGET ${PROJECT_NAME}_${THIS})

#@+ =========================== User TARGET configuration ===============================
set(THIS_INCLUDES_DIR ${INCLUDES_DIR}/Model)
file(GLOB THIS_INCLUDES ${THIS_INCLUDES_DIR}/*.hpp)
file(GLOB SOURCEFILES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

INCLUDE_DIRS_AND_FILES("${THIS_INCLUDES_DIRS}" THIS_INCLUDES)

add_library(${TARGET} OBJECT)
target_sources(${TARGET}
    PUBLIC
        ${THIS_INCLUDES}
    PRIVATE
        ${SOURCEFILES}
)

target_link_libraries(${TARGET} 
    PUBLIC
        Information_Model::Information_Model
        Event_Model::Event_Model                     
)
#@- =========================== END OF USER CONFIGURATION ===============================

target_compile_features(${TARGET} INTERFACE cxx_std_17)

target_include_directories(${TARGET}
    PUBLIC
        $<BUILD_INTERFACE:${THIS_INCLUDES_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
)

PRINT_TARGET_PROPERTIES(${TARGET})

INSTALL_TARGET(${TARGET})
INSTALL_HEADERS(HEADERS "${THIS_INCLUDES}")
