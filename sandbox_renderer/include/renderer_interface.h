#pragma once
#include <memory>
#include <cstdint>
#include <vulkan/vulkan.h>

class ISandboxRenderer {
public:
	struct FrameContext {
		VkCommandBuffer commandBuffer = VK_NULL_HANDLE;

		bool isValid() const { return commandBuffer != VK_NULL_HANDLE; }
	};

	
	virtual ~ISandboxRenderer() = default;



	virtual FrameContext beginFrame() = 0;
	virtual void beginSwapChainRenderPass(FrameContext& frame) = 0;
	virtual void endSwapChainRenderPass(FrameContext& frame) = 0;
	virtual void endFrame() = 0;

	virtual void waitDeviceIdle() = 0;

	 
private:
	
};