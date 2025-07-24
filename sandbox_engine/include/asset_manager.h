#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/obj_model.h"

class AssetManager {
public:
	AssetManager(VkSandboxDevice& device);
	~AssetManager();
	void preloadGlobalAssets();
	std::shared_ptr<VkSandboxOBJmodel> loadObjModel(const std::string& name, const std::string& filepath, bool isSkybox = false);
	using OBJmodelHandle = std::shared_ptr<VkSandboxOBJmodel>;
	//using TextureHandle  = std::shared_ptr<VulkanTexture>;
	//using ShaderHandle = std::shared_ptr<ShaderModule>;

	std::shared_ptr<VkSandboxOBJmodel> getOBJModel(const std::string& name) const;
private:
	std::unordered_map<std::string, OBJmodelHandle> objModelCache;
	VkSandboxDevice&			m_device;
	VkQueue						m_transferQueue;

};