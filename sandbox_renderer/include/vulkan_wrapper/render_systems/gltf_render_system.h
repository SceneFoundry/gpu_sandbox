#pragma once
#include "interfaces/render_system_i.h"
#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/vulkan_pipeline.h"
#include <vulkan/vulkan.h>
#include "vulkan_wrapper/vulkan_gltf.h"
#include "interfaces/game_object_i.h"
// STD
#include <memory>
#include <vector>



class GltfRenderSystem : public IRenderSystem {
public:
	GltfRenderSystem(VkSandboxDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
	~GltfRenderSystem();

	GltfRenderSystem(const GltfRenderSystem&) = delete;
	GltfRenderSystem& operator=(const GltfRenderSystem&) = delete;

	void init(
		VkSandboxDevice& device,
		VkRenderPass            renderPass,
		VkDescriptorSetLayout   globalSetLayout,
		VkDescriptorPool        descriptorPool)override;

	void render(FrameInfo& frame) override;
private:
	void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
	void createPipeline(VkRenderPass renderPass);

	VkSandboxDevice& m_device;

	VkDescriptorSetLayout m_globalSetLayout;
	VkDescriptorSetLayout m_textureSetLayout;

	std::unique_ptr<VkSandboxPipeline> m_opaquePipeline;
	std::unique_ptr<VkSandboxPipeline> m_maskPipeline;
	std::unique_ptr<VkSandboxPipeline> m_blendPipeline;
	VkPipelineLayout m_pipelineLayout;
};

