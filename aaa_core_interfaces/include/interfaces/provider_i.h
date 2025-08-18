#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include "vulkan_wrapper/vulkan_texture.h"
#include <optional>
struct IProvider {
	virtual VkDescriptorImageInfo getCubemapDescriptor(const std::string& name) const = 0;
	//virtual const std::vector<std::shared_ptr<sandbox_texture>>& getAllTextures() const {}
};