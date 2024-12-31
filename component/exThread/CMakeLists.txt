set(LIB_NAME "exThread")


set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/")
file(GLOB_RECURSE NANO_THREAD_C_FILES "${SRC_DIR}*.c")

message("--------------------------------")
message("${NANO_THREAD_C_FILES}")
message("--------------------------------")

# 构建静态库
add_library(${LIB_NAME} STATIC "") # exThread.a

target_sources(${LIB_NAME} PUBLIC "${NANO_THREAD_C_FILES}")

target_include_directories(${LIB_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/exNanoMutex")
target_include_directories(${LIB_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/exNanoThread")
target_include_directories(${LIB_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/exSemaphore")
target_include_directories(${LIB_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/exNanoTask")
target_include_directories(${LIB_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/exNanoTimer")

target_link_libraries(${LIB_NAME} PUBLIC "exLib")# 依赖
