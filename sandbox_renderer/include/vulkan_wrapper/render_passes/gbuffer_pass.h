#pragma once
#include "vulkan_wrapper/render_passes/gbuffer_pass.h"


struct GBuffer {
    VkSandboxImage albedo;
    VkSandboxImage normal;
    VkSandboxImage material;
    VkSandboxImage depth;

    VkFramebuffer framebuffer = VK_NULL_HANDLE;

    void destroy(VulkanDevice* device) {
        framebuffer = VK_NULL_HANDLE; // Destroyed by swapchain system
        albedo.destroy();
        normal.destroy();
        material.destroy();
        depth.destroy();
    }
};