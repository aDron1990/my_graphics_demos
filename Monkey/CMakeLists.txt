add_executable(Monkey sources/main.cpp sources/shaders.hpp)
target_link_libraries(Monkey PRIVATE glfw glm glad assimp)
target_link_libraries(Monkey PRIVATE Window Shader VertexBuffer Camera)

set_property(
    TARGET Monkey
    PROPERTY
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_custom_command(TARGET Monkey PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_SOURCE_DIR}/resources" "${CMAKE_BINARY_DIR}/Monkey/$<CONFIG>/resources")