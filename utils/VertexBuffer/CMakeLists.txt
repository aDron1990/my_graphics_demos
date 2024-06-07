add_library(VertexBuffer STATIC "VertexBuffer.hpp" "VertexBuffer.cpp" "Vertex.hpp")
target_link_libraries(VertexBuffer PRIVATE glad glm)
target_include_directories(VertexBuffer PUBLIC "./")