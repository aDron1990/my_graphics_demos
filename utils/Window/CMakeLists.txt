add_library(Window STATIC "Window.hpp" "detail/GlfwWindow.hpp" "detail/GlfwWindow.cpp")
target_link_libraries(Window PRIVATE glfw glad)
target_include_directories(Window PUBLIC "./")