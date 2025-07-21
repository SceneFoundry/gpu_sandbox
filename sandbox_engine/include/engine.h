#pragma once
#include <memory>
#include "window.h"
#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/vulkan_instance.h"
#include "vulkan_wrapper/vulkan_renderer.h"


class SandboxEngine {
public:
    static constexpr uint32_t WIDTH = 1440;
    static constexpr uint32_t HEIGHT = 810;

    SandboxEngine();
    ~SandboxEngine() = default;

    void run();

private:
    SandboxWindow                       m_window{ 1440, 810, "A vulkan place" };
    VkSandboxInstance                   m_vkinstance{};
    VkSandboxDevice                     m_device{ m_vkinstance, m_window };
    VkSandboxRenderer                   m_renderer{ m_device, m_window };
    
    VkSurfaceKHR                        m_surface = VK_NULL_HANDLE;
    VkInstance                          m_vkinstance_handle= VK_NULL_HANDLE;


};
