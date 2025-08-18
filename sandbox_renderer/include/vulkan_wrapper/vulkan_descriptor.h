#pragma once

#include "vulkan_device.h"

// std
#include <memory>
#include <unordered_map>
#include <vector>


class sandbox_descriptor_set_layout
{
public:
    class Builder
    {
    public:
        Builder(VkSandboxDevice& device) : m_device{ device } {}

        Builder& addBinding(
            uint32_t binding,
            VkDescriptorType descriptorType,
            VkShaderStageFlags stageFlags,
            uint32_t count,
            VkDescriptorBindingFlags flags);

        Builder& addBinding(
            uint32_t binding,
            VkDescriptorType descriptorType,
            VkShaderStageFlags stageFlags);

        ::pointer<sandbox_descriptor_set_layout> build() const;

    private:
        VkSandboxDevice& m_device;
        std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> m_bindings{};
        std::unordered_map<uint32_t, VkDescriptorBindingFlags> m_bindingFlags{};
    };

    sandbox_descriptor_set_layout(
        VkSandboxDevice& device,
        const std::vector<VkDescriptorSetLayoutBinding>& bindingsVec,
        VkDescriptorSetLayout layout
    );
    sandbox_descriptor_set_layout(VkSandboxDevice& device, VkDescriptorSetLayout layout)
        : m_device{ device }, m_descriptorSetLayout{ layout } {
    }
    ~sandbox_descriptor_set_layout();
    sandbox_descriptor_set_layout(const sandbox_descriptor_set_layout&) = delete;
    sandbox_descriptor_set_layout& operator=(const sandbox_descriptor_set_layout&) = delete;

    VkDescriptorSetLayout getDescriptorSetLayout() const { return m_descriptorSetLayout; }

private:
    VkSandboxDevice& m_device;
    VkDescriptorSetLayout m_descriptorSetLayout;
    friend class VkcDescriptorWriter;
public:
    std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> m_bindings;
    

  
};

class VkSandboxDescriptorPool
{
public:
    class Builder
    {
    public:
        Builder(VkSandboxDevice& device) : m_device{ device } {}

        Builder& addPoolSize(VkDescriptorType descriptorType, uint32_t count);
        Builder& setPoolFlags(VkDescriptorPoolCreateFlags flags);
        Builder& setMaxSets(uint32_t count);
        ::pointer<VkSandboxDescriptorPool> build() const;

    private:
        VkSandboxDevice& m_device;
        std::vector<VkDescriptorPoolSize> m_poolSizes{};
        uint32_t m_maxSets = 1000;
        VkDescriptorPoolCreateFlags m_poolFlags = 0;
    };

    VkSandboxDescriptorPool(
        VkSandboxDevice& vkcDevice,
        uint32_t maxSets,
        VkDescriptorPoolCreateFlags poolFlags,
        const std::vector<VkDescriptorPoolSize>& poolSizes);
    ~VkSandboxDescriptorPool();
    VkSandboxDescriptorPool(const VkSandboxDescriptorPool&) = delete;
    VkSandboxDescriptorPool& operator=(const VkSandboxDescriptorPool&) = delete;

    bool allocateDescriptor(
        const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet& descriptor, uint32_t variableDescriptorCount) const;

    void freeDescriptors(std::vector<VkDescriptorSet>& descriptors) const;

    void resetPool();

    VkDescriptorPool getHandle() const { return m_descriptorPool; }


    VkSandboxDevice& m_device;
    VkDescriptorPool m_descriptorPool;
private:
 


    friend class VkcDescriptorWriter;
};

class sandbox_descriptor_writer
{
public:
    sandbox_descriptor_writer(sandbox_descriptor_set_layout& setLayout, VkSandboxDescriptorPool& pool);

    sandbox_descriptor_writer& writeBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferInfo);
    sandbox_descriptor_writer& writeImage(uint32_t binding,const VkDescriptorImageInfo* imageInfo);
    sandbox_descriptor_writer& writeImage(uint32_t binding,const VkDescriptorImageInfo* imageInfos, uint32_t count);

    bool build(VkDescriptorSet& set);
    void overwrite(VkDescriptorSet& set);

private:
    sandbox_descriptor_set_layout& m_setLayout;
    VkSandboxDescriptorPool& m_pool;
    std::vector<VkWriteDescriptorSet> m_writes;
    uint32_t m_variableDescriptorCount = 0;
};