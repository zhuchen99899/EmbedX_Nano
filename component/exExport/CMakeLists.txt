set(LIB_NAME "exExport")


set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/")
file(GLOB_RECURSE EXPORT_C_FILES "${SRC_DIR}*.c")

message("--------------------------------")
message("${EXPORT_C_FILES}")
message("--------------------------------")

# 构建静态库
add_library(${LIB_NAME} STATIC "") # exExport.a

target_sources(${LIB_NAME} PUBLIC "${EXPORT_C_FILES}")



target_include_directories(${LIB_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/section_sort")

target_link_libraries(${LIB_NAME} PUBLIC "exLib")# exLib.a

