#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/vulkan_obj.h"
#include "vulkan_wrapper/vulkan_gltf.h"
#include "vulkan_wrapper/vulkan_texture.h"

class AssetManager {
public:
	AssetManager(VkSandboxDevice& device);
	~AssetManager();
	void preloadGlobalAssets();
	std::shared_ptr<VkSandboxOBJmodel> loadObjModel(const std::string& name, const std::string& filepath, bool isSkybox = false);
	std::shared_ptr<vkglTF::Model> loadGLTFmodel(const std::string& name, const std::string& filepath, uint32_t gltfFlags = 0u, float scale = 1.f);
	std::shared_ptr<VkSandboxTexture> loadCubemap(
		const std::string& name,
		const std::string& ktxFilename,
		VkFormat format,
		VkImageUsageFlags usageFlags,
		VkImageLayout initialLayout
	);
	
	using OBJmodelHandle = std::shared_ptr<VkSandboxOBJmodel>;
	using GLTFmodelHandle = std::shared_ptr<vkglTF::Model>;
	//using TextureHandle  = std::shared_ptr<VulkanTexture>;
	//using ShaderHandle = std::shared_ptr<ShaderModule>;

	std::shared_ptr<VkSandboxOBJmodel> getOBJModel(const std::string& name) const;
	std::shared_ptr<vkglTF::Model> getGLTFmodel(const std::string& name) const;

	// name → texture lookup
	std::shared_ptr<VkSandboxTexture> getTexture(const std::string& name) const;

	// index → texture lookup
	std::shared_ptr<VkSandboxTexture> getTexture(size_t index) const;

	// name → index lookup
	size_t getTextureIndex(const std::string& name) const;

	// all textures in load order
	const std::vector<std::shared_ptr<VkSandboxTexture>>& getAllTextures() const;

	// Helpers
	bool hasTexture(const std::string& name) const;

private:
	std::unordered_map<std::string, OBJmodelHandle> m_objModelCache;
	std::unordered_map<std::string, GLTFmodelHandle> m_gltfModelCache;

	std::unordered_map<std::string, std::shared_ptr<VkSandboxTexture>>  m_textures; // name → texture
	std::unordered_map<std::string, size_t>                      m_textureIndexMap; // name → index
	std::vector<std::shared_ptr<VkSandboxTexture>>                   m_textureList; // index → texture

	VkSandboxDevice&			m_device;
	VkQueue						m_transferQueue;


	static void registerTextureIfNeeded(
		const std::string& name,
		const std::shared_ptr<VkSandboxTexture>& tex,
		std::unordered_map<std::string, std::shared_ptr<VkSandboxTexture>>& textures,
		std::unordered_map<std::string, size_t>& textureIndexMap,
		std::vector<std::shared_ptr<VkSandboxTexture>>& textureList);



};