#pragma once
#include "interfaces/render_system_i.h"
#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/vulkan_pipeline.h"
#include "vulkan_wrapper/vulkan_descriptor.h"
#include <vulkan/vulkan.h>

// STD
#include <memory>
#include <vector>


class SkyboxIBLrenderSystem : public IRenderSystem {
public:
    SkyboxIBLrenderSystem(VkSandboxDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
    ~SkyboxIBLrenderSystem();

    SkyboxIBLrenderSystem(const SkyboxIBLrenderSystem&) = delete;
    SkyboxIBLrenderSystem& operator=(const SkyboxIBLrenderSystem&) = delete;

    void init(
        VkSandboxDevice& device,
        VkRenderPass            renderPass,
        VkDescriptorSetLayout   globalSetLayout,
        VkSandboxDescriptorPool& descriptorPool)override;

    // Call this inside your scene render loop, after global descriptors are bound
    void render(FrameInfo& frameInfo) override;

    inline void setCubemapTexture(const VkDescriptorImageInfo& cubemapInfo) {
        m_skyboxImageInfo = cubemapInfo;
    }
private:
    void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
    void createPipeline(VkRenderPass renderPass);


    void createSkyboxDescriptorSetLayout();
    void allocateAndWriteSkyboxDescriptorSet();

    VkDescriptorSetLayout skyboxLayout;
    VkSandboxDevice& m_device;
    std::unique_ptr<VkSandboxPipeline> m_pipeline;
    VkPipelineLayout pipelineLayout;
    VkDescriptorImageInfo m_skyboxImageInfo{};
    std::unique_ptr<VkSandboxDescriptorSetLayout> m_skyboxSetLayout;
    VkDescriptorSet m_skyboxDescriptorSet = VK_NULL_HANDLE;

    VkSandboxDescriptorPool* m_descriptorPool = nullptr;
};
