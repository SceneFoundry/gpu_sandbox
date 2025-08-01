#pragma once
#include "renderer_i.h"
#include <vulkan/vulkan.h>



struct IModel {
public:
	virtual ~IModel() = default;
	virtual void bind(VkCommandBuffer cmd) {};

	// Issue the draw call
	virtual void draw(VkCommandBuffer cmd) {};
};

