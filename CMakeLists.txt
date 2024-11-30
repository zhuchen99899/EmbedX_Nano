cmake_minimum_required (VERSION 3.20)

set(__PROJ_NAME__ "exAssertExample")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output)
SET(CMAKE_BUILD_TYPE "Debug")


project(${__PROJ_NAME__} LANGUAGES C)


add_subdirectory(exLib) # exLib.a

#file(GLOB MAIN_SRC  CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/example/exLog_example/*.c")
file(GLOB MAIN_SRC  CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/example/exAssert_example/*.c")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE "${MAIN_SRC}")

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/example/exLog_example")


target_link_libraries(${PROJECT_NAME} PRIVATE "exLib")# exLib.a







