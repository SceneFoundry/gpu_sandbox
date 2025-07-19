#pragma once
#include <memory>
#include "window.h"
#include "vulkan_wrapper/vulkan_device.h"
#include "instance.h"

class Engine {
public:
    static constexpr uint32_t WIDTH = 1440;
    static constexpr uint32_t HEIGHT = 810;

    Engine();
    ~Engine() = default;

    void initialize();
    void run();

private:
    SandboxWindow              _window{ 1440, 810, "App Name" };
    SandboxInstance            _vkInstance;
    VkSurfaceKHR               _surface = VK_NULL_HANDLE;
    std::unique_ptr<SandboxDevice> _device;
    VkInstance                 _instanceHandle = VK_NULL_HANDLE;
    //

};
