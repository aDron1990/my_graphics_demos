cmake_minimum_required(VERSION 3.10)
project(my_graphics_demos CXX C)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED TRUE)

option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)

add_subdirectory("libraries/glad")
add_subdirectory("libraries/glfw")
add_subdirectory("libraries/glm")

include_directories("./")
add_subdirectory("Triangle/")