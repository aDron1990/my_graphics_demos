file(GLOB sources "./*.cpp" "./*.h")
add_library(imgui STATIC 
${sources}
"./misc/cpp/imgui_stdlib.h"
"./misc/cpp/imgui_stdlib.cpp"
"./backends/imgui_impl_opengl3_loader.h"
"./backends/imgui_impl_opengl3.h"
"./backends/imgui_impl_opengl3.cpp"
"./backends/imgui_impl_glfw.h"
"./backends/imgui_impl_glfw.cpp"
)
target_link_libraries(imgui PRIVATE glfw Vulkan::Vulkan)
target_include_directories(imgui PUBLIC "./")