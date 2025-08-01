#include "vulkan_wrapper/render_systems/skybox_ibl_rs.h"



SkyboxIBLrenderSystem::SkyboxIBLrenderSystem(VkSandboxDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout)
    : m_device{ device }
{

}


void SkyboxIBLrenderSystem::init(
	VkSandboxDevice& device,
	VkRenderPass renderPass,
	VkDescriptorSetLayout globalSetLayout,
	VkSandboxDescriptorPool& descriptorPool)
{
	assert(&device == &m_device);
	m_descriptorPool = &descriptorPool;

	createSkyboxDescriptorSetLayout();
	allocateAndWriteSkyboxDescriptorSet();

	createPipelineLayout(globalSetLayout);
	createPipeline(renderPass);
}

void SkyboxIBLrenderSystem::createSkyboxDescriptorSetLayout() {
	m_skyboxSetLayout = VkSandboxDescriptorSetLayout::Builder(m_device)
		.addBinding(
			0,
			VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			VK_SHADER_STAGE_FRAGMENT_BIT,
			1,
			0) // no binding flags needed here
		.build();
}


void SkyboxIBLrenderSystem::allocateAndWriteSkyboxDescriptorSet() {
	assert(m_descriptorPool && "Descriptor pool must be set before allocating descriptors");
	assert(m_skyboxSetLayout && "Descriptor set layout must be created before allocating");

	VkSandboxDescriptorWriter writer(*m_skyboxSetLayout, *m_descriptorPool);
	writer.writeImage(0, &m_skyboxImageInfo);
	bool success = writer.build(m_skyboxDescriptorSet);
	assert(success && "Failed to build skybox descriptor set");
}
