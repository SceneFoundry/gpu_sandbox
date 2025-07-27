#pragma once
#include <memory>
#include <cstdint>
#include <vulkan/vulkan.h>
#include <vector>
#include <glm/glm.hpp>
#include "frame_info.h"

class ISandboxRenderer {
public:
	struct FrameContext {
		std::vector<VkCommandBuffer> graphicsCommandBuffers;
		VkCommandBuffer primaryGraphicsCommandBuffer = VK_NULL_HANDLE;
		VkFence frameFence = VK_NULL_HANDLE;
		uint32_t frameIndex = 0;

		bool isValid() const { return primaryGraphicsCommandBuffer != VK_NULL_HANDLE; }
	};

	
	virtual ~ISandboxRenderer() = default;

	virtual void renderSystems(FrameInfo& frame) = 0;

	virtual FrameContext beginFrame() = 0;
	virtual void beginSwapChainRenderPass(FrameContext& frame) = 0;
	virtual void endSwapChainRenderPass(FrameContext& frame) = 0;
	virtual void endFrame() = 0;

	virtual void waitDeviceIdle() = 0;

	struct GlobalUbo {
		glm::mat4 view;
		glm::mat4 proj;
	};
	
};