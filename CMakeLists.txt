cmake_minimum_required (VERSION 3.20)

set(__PROJ_NAME__ "exTimer_example")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output)
SET(CMAKE_BUILD_TYPE "Debug")
set (CMAKE_EXE_LINKER_FLAGS "-Xlinker -Map=bdc.map")

project(${__PROJ_NAME__} LANGUAGES C)


add_subdirectory(exLib) # exLib.a
add_subdirectory(component/exExport)# exExport.a
add_subdirectory(component/exThread)# exThread.a
#file(GLOB MAIN_SRC  CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/example/exList_example/*.c")
#file(GLOB MAIN_SRC  CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/example/exLog_example/*.c")
#file(GLOB MAIN_SRC  CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/example/exAssert_example/*.c")
#file(GLOB MAIN_SRC  CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/example/exExport_example/*.c")
# file(GLOB MAIN_SRC  CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/example/exThreadMutex_example/*.c")
#file(GLOB MAIN_SRC  CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/example/exThreadSemaphore_example/*.c")
file(GLOB MAIN_SRC  CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/example/exTimer_example/*.c")
message("--------------------------------")
message("${MAIN_SRC}")
message("--------------------------------")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE "${MAIN_SRC}")

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/example/exTimer_example")


target_link_libraries(${PROJECT_NAME} PUBLIC "exLib")# exLib.a
target_link_libraries(${PROJECT_NAME} PUBLIC "exExport")# exExport.a
target_link_libraries(${PROJECT_NAME} PUBLIC "exThread")# exExport.a




