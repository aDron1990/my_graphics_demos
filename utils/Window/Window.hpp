#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <tuple>

class Window
{
public:

    virtual std::tuple<int, int> getFrameBufferSize() const noexcept = 0;
    virtual void display() const noexcept = 0;
    virtual void update() const noexcept = 0;
    virtual bool isClose() noexcept = 0;
    virtual ~Window() = default; 

};

struct WindowParams
{
    size_t width;
    size_t height;
    std::string title;
};

using WindowPtr = std::unique_ptr<Window>;
WindowPtr createWindow(const WindowParams& params);