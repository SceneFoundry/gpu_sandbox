#pragma once

#include <vulkan/vulkan.h>
#include "vulkan_wrapper/vulkan_device.h"

class VkSandboxImage {
public:
    VkSandboxImage() = default;
    ~VkSandboxImage();

    VkSandboxImage(const VkSandboxImage&) = delete;
    VkSandboxImage& operator=(const VkSandboxImage&) = delete;

    void create(
        VkSandboxDevice* device,
        uint32_t width,
        uint32_t height,
        VkFormat format,
        VkImageUsageFlags usage,
        VkImageAspectFlags aspectMask,
        VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT,
        VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL,
        VkMemoryPropertyFlags memoryProperties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
    );

    void destroy();

    VkImage getImage() const { return m_image; }
    VkImageView getImageView() const { return m_imageView; }
    VkFormat getFormat() const { return m_format; }
    uint32_t getWidth() const { return m_width; }
    uint32_t getHeight() const { return m_height; }

private:
    VkSandboxDevice* m_pDevice = nullptr;

    uint32_t m_width = 0;
    uint32_t m_height = 0;
    VkFormat m_format = VK_FORMAT_UNDEFINED;

    VkImage m_image = VK_NULL_HANDLE;
    VkDeviceMemory m_memory = VK_NULL_HANDLE;
    VkImageView m_imageView = VK_NULL_HANDLE;
};