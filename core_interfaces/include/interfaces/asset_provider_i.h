#pragma once
#include <vulkan/vulkan.h>
#include <string>

struct IRenderAssetProvider {
	virtual VkDescriptorImageInfo getCubemapDescriptor(const std::string& name) const = 0;
};