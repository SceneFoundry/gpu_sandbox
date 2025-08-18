// sandbox_renderer/include/IRenderSystem.h
#pragma once
#include <vulkan/vulkan.h>
//#include "common/render_data.h"
#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/vulkan_descriptor.h"
#include "renderer_i.h"
#include "frame_info.h"


struct IRenderSystem {
public:
    virtual ~IRenderSystem() = default;


    virtual void init(
        sandbox_device& device,
        VkRenderPass            renderPass,
        VkDescriptorSetLayout   globalSetLayout,
        VkSandboxDescriptorPool& descriptorPool)
    {};   
    virtual void init(
        sandbox_device& device,
        VkRenderPass            renderPass,
        VkDescriptorSetLayout   globalSetLayout,
        VkSandboxDescriptorPool& descriptorPool,
        size_t frameCount)
    {};

    virtual void update(FrameInfo& frame, GlobalUbo& ubo) {
  
    }

    virtual void render(FrameInfo& frame) {}


};