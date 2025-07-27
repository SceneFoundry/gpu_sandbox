#pragma once
#include <string>
#include <vector>

#include "vulkan_device.h"

struct PipelineConfigInfo {
	PipelineConfigInfo() = default;
	PipelineConfigInfo(const PipelineConfigInfo&) = delete;
	PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;


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

class VkSandboxPipeline {
public:
	VkSandboxPipeline(
		VkSandboxDevice& device,
		const std::string& vertFilepath,
		const std::string& fragFilepath,
		const PipelineConfigInfo& configInfo);
	~VkSandboxPipeline();

	VkSandboxPipeline(const VkSandboxPipeline&) = delete;
	void operator=(const VkSandboxPipeline&) = delete;

	void bind(VkCommandBuffer commandBuffer);

	static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);
	static void defaultSkyboxConfigInfo(PipelineConfigInfo& configInfo);

	// Getters
	VkPipeline getPipeline() const { return m_graphicsPipeline; }
	VkPipelineLayout getPipelineLayout() const { return m_pipelineLayout; }
private:
	static std::vector<char> readFile(const std::string& filepath);

	void createGraphicsPipeline(
		const std::string& vertFilepath,
		const std::string& fragFilepath,
		const PipelineConfigInfo& configInfo);

	void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

	VkSandboxDevice& m_device;
	VkPipeline m_graphicsPipeline;
	VkPipelineLayout m_pipelineLayout;
	VkShaderModule m_vertShaderModule;
	VkShaderModule m_fragShaderModule;
};