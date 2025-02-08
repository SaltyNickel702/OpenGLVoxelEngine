cmake_minimum_required(VERSION 3.31)

project(GraphicsTest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.c")

add_executable(out ${SOURCES})


include_directories(${GLAD_INCLUDE})
include_directories(${GLFW_INCLUDE})

target_link_libraries(out ${GLFW__STATIC_LIB_MINGW-W64})
