// vk_descriptor_req.h
#pragma once
#include <vector>
#include <vulkan/vulkan.h>

struct DescriptorBinding {
    uint32_t          setIndex;     // which set slot (0, 1, 2…)
    uint32_t          binding;      // binding number in that set
    VkDescriptorType  type;
    VkShaderStageFlags stages;
    uint32_t          count = 1;    // number of descriptors
};

struct DescriptorRequirement {
    // pipeline-layout’s setLayouts[]
    // e.g. if you do {set=0, binding=0, UBO}, {set=1, binding=0, sampler}
    std::vector<DescriptorBinding> bindings;
};

inline DescriptorRequirement GlobalRequirement()
{
    return DescriptorRequirement{ {
            // set=0, binding=0, one uniform buffer for the camera
            { /*setIndex=*/0, /*binding=*/0,
              VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
              VK_SHADER_STAGE_ALL_GRAPHICS,
              /*count=*/1 }
        }};
}