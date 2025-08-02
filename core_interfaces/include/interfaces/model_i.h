#pragma once
#include "renderer_i.h"
#include <vulkan/vulkan.h>



struct IModel {
public:
	virtual ~IModel() = default;
	virtual void bind(VkCommandBuffer cmd) {};

	// Issue the draw call
	virtual void draw(VkCommandBuffer cmd) {};

	virtual void gltfDraw(
		VkCommandBuffer cmd,
		uint32_t renderFlags = 0,
		VkPipelineLayout pipelineLayout = VK_NULL_HANDLE,
		uint32_t bindImageSet = 1
	) {}
};

