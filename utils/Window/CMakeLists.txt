add_library(Window STATIC "Window.hpp" "detail/GlfwWindow.hpp" "detail/GlfwWindow.cpp")
target_link_libraries(Window PRIVATE glfw glad imgui)
target_include_directories(Window PUBLIC "./")

set_property(
    TARGET Window
    PROPERTY
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)