// vk_descriptor_reg.h
#pragma once
#include "vk_descriptor_req.h"
#include <vulkan/vulkan.h>
#include <unordered_map>
#include <string>
#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/vulkan_descriptor.h"
#include <memory>
#include <vector>

class DescriptorRegistry {
public:
    DescriptorRegistry(VkSandboxDevice& device);
    ~DescriptorRegistry();

    // 1) Call once per system, before init()
    void registerSystem(
        const std::string& name,
        const DescriptorRequirement& req);

    // 2) After all systems registered, build everything:
    void build(uint32_t maxFramesInFlight);

    // 3) Pull back the sandbox‐layout wrappers so you can build your pipeline
    //    layouts in each RenderSystem::init()
    const std::vector<std::unique_ptr<VkSandboxDescriptorSetLayout>>&
        getDescriptorSetLayouts(const std::string& systemName) const;

    // 4) Pull back the raw VkDescriptorSet handles for binding at draw time
    //    [frame][setIndex]
    const std::vector<std::vector<VkDescriptorSet>>&
        getDescriptorSets(const std::string& systemName) const;

private:
    VkSandboxDevice&                                  m_device;
    std::unique_ptr<VkSandboxDescriptorPool>  m_pool;

    // pooled by (setIndex, type) to sum counts:
    struct PoolSizeKey { uint32_t setIndex; VkDescriptorType type; };
    std::vector<VkDescriptorPoolSize>          m_poolSizes;

    // for each system:
    struct Entry {
        DescriptorRequirement                  requirement;
        std::vector<std::unique_ptr<VkSandboxDescriptorSetLayout>> layouts;
        std::vector<std::vector<VkDescriptorSet>>
            sets;     // [frame][setIndex]
    };

    std::unordered_map<std::string, Entry>     m_entries;
};