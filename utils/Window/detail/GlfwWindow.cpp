#include "GlfwWindow.hpp"

#include <cassert>
#include <stdexcept>

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
        windowHandlePtr.reset();
        throw std::runtime_error{"Failed to create context"};
    }
}

void GlfwWindow::display() const noexcept
{
    glfwSwapBuffers(windowHandlePtr.get());
}

void GlfwWindow::update() const noexcept
{
    glfwPollEvents();
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