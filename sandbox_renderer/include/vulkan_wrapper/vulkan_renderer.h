// vulkan_renderer.h
#pragma once
#include <memory>
#include "renderer_interface.h"
#include "window.h"
#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/vulkan_swapchain.h"


class VkSandboxRenderer : public ISandboxRenderer
{
public:
	VkSandboxRenderer(VkSandboxDevice& device, SandboxWindow& window);
	VkSandboxRenderer(const VkSandboxRenderer&) = delete;
	VkSandboxRenderer& operator=(const VkSandboxRenderer&) = delete;
	~VkSandboxRenderer() override;
	


	FrameContext beginFrame() override;
	
	void endFrame() override;
	void beginSwapChainRenderPass(FrameContext& frame)override;
	void endSwapChainRenderPass(FrameContext& frame)override;



	void waitDeviceIdle() override;
	
	// Inline helpers
	inline VkRenderPass getSwapChainRenderPass() const { return m_swapchain->getRenderPass(); }
	inline float getAspectRatio() const { return m_swapchain->extentAspectRatio(); }
	inline bool isFrameInProgress() const { return m_bIsFrameStarted; }

	inline VkCommandBuffer getCurrentCommandBuffer() const {
		assert(m_bIsFrameStarted && "Cannot get command buffer when frame not in progress");
		return m_commandBuffers[m_currentFrameIndex];
	}

	inline 	int getFrameIndex() const {
		assert(m_bIsFrameStarted && "Cannot get frame index when frame not in progress");
		return m_currentFrameIndex;
	}
private:

	std::vector<VkCommandBuffer> m_commandBuffers;
	VkCommandPool m_commandPool = VK_NULL_HANDLE;
	uint32_t m_currentImageIndex = 0;
	int m_currentFrameIndex = 0;
	bool m_bIsFrameStarted = false;

	// vulkan handles
	VkSandboxDevice& m_device;
	SandboxWindow& m_window;

	std::unique_ptr<VkSandboxSwapchain> m_swapchain;
	std::shared_ptr<VkSandboxSwapchain> m_oldSwapchain;
	VkInstance m_instance = VK_NULL_HANDLE;
	//VkSurfaceKHR m_surface = VK_NULL_HANDLE;
	uint32_t     m_width{ 0 }, m_height{ 0 };

	void createSwapChain();
	void createCommandBuffers();
	void freeCommandBuffers();
	void recreateSwapchain();

};