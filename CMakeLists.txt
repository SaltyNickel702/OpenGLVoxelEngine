cmake_minimum_required(VERSION 3.31)

project(GraphicsTest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.c")

add_executable(out ${SOURCES})


include_directories("D:/Libraries/GLAD/include")
include_directories("D:/Libraries/GLFW/include")

target_link_libraries(out "D:/Libraries/GLFW/lib-mingw-w64/libglfw3.a")