#pragma once
#include <string>
#include <vector>

#include "vulkan_device.h"

struct pipeline_configuration_information {
	pipeline_configuration_information() = default;
	pipeline_configuration_information(const pipeline_configuration_information&) = delete;
	pipeline_configuration_information& operator=(const pipeline_configuration_information&) = delete;


	std::vector<VkVertexInputBindingDescription> bindingDescriptions{};
	std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
	VkPipelineViewportStateCreateInfo viewportInfo;
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
	VkPipelineRasterizationStateCreateInfo rasterizationInfo;
	VkPipelineMultisampleStateCreateInfo multisampleInfo;
	VkPipelineColorBlendAttachmentState colorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo colorBlendInfo;
	VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
	std::vector<VkDynamicState> dynamicStateEnables;
	VkPipelineDynamicStateCreateInfo dynamicStateInfo;
	VkPipelineLayout pipelineLayout = nullptr;
	VkRenderPass renderPass = nullptr;
	uint32_t subpass = 0;
	VkSpecializationInfo* fragSpecInfo = nullptr;

	// Push constant ranges
	std::vector<VkPushConstantRange> pushConstantRanges;

	// Descriptor set layouts if needed
	std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
};

class sandbox_pipeline {
public:
	sandbox_pipeline(
		VkSandboxDevice& device,
		const std::string& vertFilepath,
		const std::string& fragFilepath,
		const pipeline_configuration_information& configInfo);
	~sandbox_pipeline();

	sandbox_pipeline(const sandbox_pipeline&) = delete;
	void operator=(const sandbox_pipeline&) = delete;

	void bind(VkCommandBuffer commandBuffer);

	static void defaultPipelineConfigInfo(pipeline_configuration_information& configInfo);
	static void defaultSkyboxConfigInfo(pipeline_configuration_information& configInfo);

	// Getters
	VkPipeline getPipeline() const { return m_graphicsPipeline; }
	VkPipelineLayout getPipelineLayout() const { return m_pipelineLayout; }
private:
	static std::vector<char> readFile(const std::string& filepath);

	void createGraphicsPipeline(
		const std::string& vertFilepath,
		const std::string& fragFilepath,
		const pipeline_configuration_information& configInfo);

	void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

	VkSandboxDevice& m_device;
	VkPipeline m_graphicsPipeline;
	VkPipelineLayout m_pipelineLayout;
	VkShaderModule m_vertShaderModule;
	VkShaderModule m_fragShaderModule;
};