// vulkan_renderer.h
#pragma once
#include <memory>
#include "interfaces/renderer_i.h"
#include "interfaces/render_system_i.h"
#include "interfaces/asset_provider_i.h"
#include "render_systems/obj_render_system.h"
#include "render_systems/gltf_render_system.h"
#include "render_systems/skybox_ibl_rs.h"
#include "render_systems/point_light_rs.h"
#include "window.h"
#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/vulkan_swapchain.h"
#include "vulkan_wrapper/vulkan_descriptor.h"
#include "vulkan_wrapper/vulkan_buffer.h"
#include <vector>
#include <array>

class sandbox_renderer : public ISandboxRenderer
{
public:

	static constexpr size_t FrameCount =
		sandbox_swap_chain::MAX_FRAMES_IN_FLIGHT;


	sandbox_renderer(VkSandboxDevice& device, SandboxWindow& window);
	sandbox_renderer(const sandbox_renderer&) = delete;
	sandbox_renderer& operator=(const sandbox_renderer&) = delete;
	~sandbox_renderer() override;
	


	FrameContext beginFrame() override;
	
	void endFrame(FrameContext& frame) override;
	void beginSwapChainRenderPass(FrameContext& frame)override;
	void endSwapChainRenderPass(FrameContext& frame)override;

	void initializeSystems(IAssetProvider& assets);
	void initSkyboxSystem();
	void renderSystems(FrameInfo& frame)override;

	void waitDeviceIdle() override;

	void updateSystems(FrameInfo& frame, GlobalUbo& ubo, float deltaTime)override;
	
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

	inline const std::vector<VkDescriptorSet>& getGlobalDescriptorSet() const {
		return m_globalDescriptorSets;
	}
	inline const std::vector<::pointer<sandbox_buffer>>& getUboBuffers() const {
		return m_uboBuffers;
	}


	::pointer<VkSandboxDescriptorPool>                      m_pool;
private:

	std::vector<VkCommandBuffer>					    m_commandBuffers;
	VkCommandPool										   m_commandPool = VK_NULL_HANDLE;
	uint32_t								         m_currentImageIndex = 0;
	int												 m_currentFrameIndex = 0;
	bool										       m_bIsFrameStarted = false;

	::pointer<sandbox_descriptor_set_layout>		  m_globalLayout;

	VkSandboxDevice&											m_device;
	SandboxWindow&											    m_window;
	std::vector<::pointer<IRenderSystem>>				   m_systems;

	::pointer<sandbox_swap_chain>					     m_swapchain;
	std::shared_ptr<sandbox_swap_chain>					  m_oldSwapchain;
	VkInstance												  m_instance = VK_NULL_HANDLE;
	
	uint32_t								      m_width{ 0 }, m_height{ 0 };
	std::vector<::pointer<sandbox_buffer>>			m_uboBuffers;
	std::vector<VkDescriptorSet>				  m_globalDescriptorSets;
	std::vector<VkFence>							    m_inFlightFences;

	void createGlobalDescriptorObjects();
	void allocateGlobalDescriptors();
	

	void createSwapChain();
	void createCommandBuffers();
	void freeCommandBuffers();
	void recreateSwapchain();


};