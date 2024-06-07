add_executable(Cube sources/main.cpp)
target_link_libraries(Cube PRIVATE glfw glm glad assimp)
target_link_libraries(Cube PRIVATE Window Shader VertexBuffer Camera)

set_property(
    TARGET Cube
    PROPERTY
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)