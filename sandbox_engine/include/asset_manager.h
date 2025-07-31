#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/vulkan_obj.h"
#include "vulkan_wrapper/vulkan_gltf.h"

class AssetManager {
public:
	AssetManager(VkSandboxDevice& device);
	~AssetManager();
	void preloadGlobalAssets();
	std::shared_ptr<VkSandboxOBJmodel> loadObjModel(const std::string& name, const std::string& filepath, bool isSkybox = false);
	std::shared_ptr<vkglTF::Model> loadGLTFmodel(const std::string& name, const std::string& filepath, uint32_t gltfFlags = 0u, float scale = 1.f);
	using OBJmodelHandle = std::shared_ptr<VkSandboxOBJmodel>;
	using GLTFmodelHandle = std::shared_ptr<vkglTF::Model>;
	//using TextureHandle  = std::shared_ptr<VulkanTexture>;
	//using ShaderHandle = std::shared_ptr<ShaderModule>;

	std::shared_ptr<VkSandboxOBJmodel> getOBJModel(const std::string& name) const;
	std::shared_ptr<vkglTF::Model> getGLTFmodel(const std::string& name) const;
private:
	std::unordered_map<std::string, OBJmodelHandle> m_objModelCache;
	std::unordered_map<std::string, GLTFmodelHandle> m_gltfModelCache;
	VkSandboxDevice&			m_device;
	VkQueue						m_transferQueue;

};