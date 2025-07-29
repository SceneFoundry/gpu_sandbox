// sandbox_renderer/include/IRenderSystem.h
#pragma once
#include <vulkan/vulkan.h>
//#include "common/render_data.h"
#include "vulkan_wrapper/vulkan_device.h"
#include "renderer_i.h"
#include "frame_info.h"

struct IRenderSystem {
public:
    virtual ~IRenderSystem() = default;

    // Called once in initialize()
    //virtual void createPipelineLayout(VkDevice device) = 0;
    virtual void init(
        VkSandboxDevice& device,
        VkRenderPass            renderPass,
        VkDescriptorSetLayout   globalSetLayout,
        VkDescriptorPool        descriptorPool) 
    {};

    virtual void update(FrameInfo& frame, GlobalUbo& ubo) {
        // Default empty implementation
    }

    // Called each frame inside renderScene()
    virtual void render(FrameInfo& frame) {}


};