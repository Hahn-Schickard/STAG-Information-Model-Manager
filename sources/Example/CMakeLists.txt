#@+ ======================== User TARGET NAME configuration ============================
set(THIS Example)
#@- =========================== END OF USER CONFIGURATION ===============================
set(TARGET ${PROJECT_NAME}_${THIS})
#@+ =========================== User TARGET configuration ===============================
file(GLOB SOURCEFILES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
add_executable(${TARGET})
target_sources(${TARGET}
    PRIVATE
        ${SOURCEFILES}
)
target_link_libraries(${TARGET}
    PRIVATE 
        Technology_Adapter_Interface::Technology_Adapter_Interface
        Event_Model::Event_Model
        ${PROJECT_NAME}_Manager
)
#@- =========================== END OF USER CONFIGURATION ===============================

IMPORT_TARGET_DLLS(${TARGET})
