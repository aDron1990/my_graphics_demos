cmake_minimum_required(VERSION 3.10)
project(my_graphics_demos CXX C)

option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)

set(ASSIMP_NO_EXPORT ON)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL_PDB OFF)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_OBJ_IMPORTER ON)
set(ASSIMP_BUILD_GLTF_IMPORTER ON)

find_package(Vulkan REQUIRED)

add_subdirectory("libraries/glad")
add_subdirectory("libraries/glfw")
add_subdirectory("libraries/glm")
add_subdirectory("libraries/assimp")
add_subdirectory("libraries/imgui")

add_subdirectory("utils/Window")
add_subdirectory("utils/Shader")
add_subdirectory("utils/Camera")
add_subdirectory("utils/VertexBuffer")

include_directories("./")
add_subdirectory("Triangle/")
add_subdirectory("Monkey/")