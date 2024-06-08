#include "GlfwWindow.hpp"

#include <cassert>
#include <stdexcept>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

WindowPtr createWindow(const WindowParams& params)
{
    return std::unique_ptr<Window> { new GlfwWindow{params} };
}

GlfwWindow* GlfwWindow::instance = nullptr; 

GlfwWindow::GlfwWindow(const WindowParams& params)
    : windowHandlePtr{nullptr, [](GLFWwindow*){}}
{
    checkAndSetInstance();
    initGlfw();
    createWindow(params);
    createContext(params);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(windowHandlePtr.get(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void GlfwWindow::checkAndSetInstance()
{
    assert(instance == nullptr);
    instance = this;
}

void GlfwWindow::initGlfw()
{
    if (!glfwInit())
        throw std::runtime_error("Failed to init GLFW");
}

void GlfwWindow::createWindow(const WindowParams& params)
{
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow((int)params.width, (int)params.height, params.title.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error{"Failed to create window"};
    }
    windowHandlePtr = WindowHandlePtr{window, [](GLFWwindow* window)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }};
}

void GlfwWindow::createContext(const WindowParams& params)
{
    glfwMakeContextCurrent(windowHandlePtr.get());
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        windowHandlePtr.reset();
        throw std::runtime_error{"Failed to create context"};
    }
}

void GlfwWindow::display() const noexcept
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(windowHandlePtr.get());
}

void GlfwWindow::update() const noexcept
{
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

bool GlfwWindow::isClose() noexcept
{
    return glfwWindowShouldClose(windowHandlePtr.get());
}

std::tuple<int, int> GlfwWindow::getFrameBufferSize() const noexcept
{
    int width, height;
    glfwGetWindowSize(windowHandlePtr.get(), &width, &height);
    return std::tuple<int, int>{width, height};
}