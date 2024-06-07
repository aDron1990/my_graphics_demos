add_library(Camera STATIC "Camera.hpp" "Camera.cpp")
target_link_libraries(Camera PRIVATE glm)
target_include_directories(Camera PUBLIC "./")