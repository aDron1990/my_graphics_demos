add_library(Shader STATIC "Shader.hpp" "Shader.cpp")
target_link_libraries(Shader PRIVATE glad glm)
target_include_directories(Shader PUBLIC "./")