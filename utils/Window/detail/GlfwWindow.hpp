#pragma once

#include "Window.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <functional>

class GlfwWindow : public Window
{
public:

    GlfwWindow(const WindowParams& params);
    void display() const noexcept override;
    void update() const noexcept override;
    bool isClose() noexcept override;
    std::tuple<int, int> getFrameBufferSize() const noexcept override;

private:

    void checkAndSetInstance();
    void initGlfw();
    void createWindow(const WindowParams& params);
    void createContext(const WindowParams& params);

private:

    static GlfwWindow* instance;
    using WindowHandlePtr = std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>>; 
    WindowHandlePtr windowHandlePtr;

};