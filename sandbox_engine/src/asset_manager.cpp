// asset_manager.cpp
#include "asset_manager.h"

#include <json.hpp>
#include <fstream>
#include <spdlog/spdlog.h>


using json = nlohmann::json;

AssetManager::AssetManager(VkSandboxDevice& device) : m_device(device) {

}

AssetManager::~AssetManager()
{

}
void AssetManager::preloadGlobalAssets() {
    std::ifstream in(PROJECT_ROOT_DIR "/sandbox_game/res/scene_assets/default_scene_assets.json");
    if (!in.is_open()) {
        throw std::runtime_error("Failed to open model list JSON.");
    }

    json modelJson;
    in >> modelJson;

    for (const auto& entry : modelJson["models"]) {
        const std::string name = entry["name"];
        const std::string type = entry.value("type", "obj");
        const std::string path = std::string(PROJECT_ROOT_DIR) + "/res/models/" + entry["path"].get<std::string>();

        try {
            if (type == "obj") {
                auto model = loadObjModel(name, path, false);
                spdlog::info("[AssetManager] Successfully loaded OBJ model '{}' from '{}'", name, path);
            }
            else if (type == "gltf") {
                uint32_t flags = entry.value("flags", 0);  // Optional flags
                float scale = entry.value("scale", 1.0f);   // Optional scale
                auto model = loadGLTFmodel(name, path, flags, scale);
                spdlog::info("[AssetManager] Successfully loaded glTF model '{}' from '{}'", name, path);
            }
            else {
                spdlog::warn("[AssetManager] Unknown model type '{}' for asset '{}'", type, name);
            }
        }
        catch (const std::exception& e) {
            spdlog::error("[AssetManager] Failed to load model '{}': {}", name, e.what());
        }
    }
    for (const auto& entry : modelJson["cubemaps"]) {
        const std::string name = entry["name"];
        const std::string path = std::string(PROJECT_ROOT_DIR) + "/res/textures/" + entry["path"].get<std::string>();

        // Optional format string to VkFormat
        std::string fmtStr = entry.value("format", "VK_FORMAT_R32G32B32A32_SFLOAT");
        VkFormat format = VK_FORMAT_R32G32B32A32_SFLOAT; // fallback

        // Simple hardcoded format mapping
        if (fmtStr == "VK_FORMAT_R16G16B16A16_SFLOAT") format = VK_FORMAT_R16G16B16A16_SFLOAT;
        else if (fmtStr == "VK_FORMAT_R32G32B32A32_SFLOAT") format = VK_FORMAT_R32G32B32A32_SFLOAT;

        try {
            auto cubemap = loadCubemap(
                name,
                path,
                format,
                VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
                VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
            );
            spdlog::info("[AssetManager] Successfully loaded cubemap '{}' from '{}'", name, path);
        }
        catch (const std::exception& e) {
            spdlog::error("[AssetManager] Failed to load cubemap '{}': {}", name, e.what());
        }
    }
}


std::shared_ptr<VkSandboxOBJmodel> AssetManager::loadObjModel(
    const std::string& name,
    const std::string& filepath,
    bool isSkybox
) {
    // 1) cache check
    if (auto it = m_objModelCache.find(name); it != m_objModelCache.end())
        return it->second;

    // 2) load
    auto model = VkSandboxOBJmodel::createModelFromFile(m_device, filepath, isSkybox);

    // 3) cache & return
    m_objModelCache[name] = model;
    return model;
}


std::shared_ptr<vkglTF::Model> AssetManager::loadGLTFmodel(
    const std::string& name,
    const std::string& filepath,
    uint32_t gltfFlags,
    float scale
) {
    if (auto it = m_gltfModelCache.find(name); it != m_gltfModelCache.end())
        return it->second;

    auto model = std::make_shared<vkglTF::Model>();
    model->loadFromFile(filepath, &m_device, m_device.graphicsQueue(), gltfFlags, scale);

    m_gltfModelCache[name] = model;
    return model;
}

std::shared_ptr<VkSandboxTexture> AssetManager::loadCubemap(
    const std::string& name,
    const std::string& ktxFilename,
    VkFormat format,
    VkImageUsageFlags usageFlags,
    VkImageLayout initialLayout)
{
    if (auto it = m_textures.find(name); it != m_textures.end())
        return it->second;

    auto tex = std::make_shared<VkSandboxTexture>();
    tex->m_pDevice = &m_device;
    try {
        tex->KtxLoadCubemapFromFile(
            name,
            ktxFilename,
            format,
            &m_device,
            m_device.graphicsQueue(),
            usageFlags,
            initialLayout
        );
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Failed to load HDR cubemap '" + name + "': " + e.what());
    }

    registerTextureIfNeeded(name, tex, m_textures, m_textureIndexMap, m_textureList);
    return tex;
}


// Getters
//------------------------------------------------------------------------------
std::shared_ptr<VkSandboxOBJmodel> AssetManager::getOBJModel(const std::string& name) const {
    auto it = m_objModelCache.find(name);
    if (it != m_objModelCache.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}

std::shared_ptr<vkglTF::Model> AssetManager::getGLTFmodel(const std::string& name) const {
    auto it = m_gltfModelCache.find(name);
    if (it != m_gltfModelCache.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}


std::shared_ptr<VkSandboxTexture> AssetManager::getTexture(const std::string& name) const
{
    auto it = m_textures.find(name);
    if (it == m_textures.end())
        throw std::runtime_error("Texture not found: " + name);
    return it->second;
}

//------------------------------------------------------------------------------
std::shared_ptr<VkSandboxTexture> AssetManager::getTexture(size_t index) const
{
    if (index >= m_textureList.size())
        throw std::runtime_error("Texture index out of range: " + std::to_string(index));
    return m_textureList[index];
}

//------------------------------------------------------------------------------
size_t AssetManager::getTextureIndex(const std::string& name) const
{
    auto it = m_textureIndexMap.find(name);
    if (it == m_textureIndexMap.end())
        throw std::runtime_error("Texture not found in index map: " + name);
    return it->second;
}

//------------------------------------------------------------------------------
const std::vector<std::shared_ptr<VkSandboxTexture>>& AssetManager::getAllTextures() const
{
    return m_textureList;
}

// Helpers
bool AssetManager::hasTexture(const std::string& name) const {
    return m_textures.find(name) != m_textures.end();
}

void AssetManager::registerTextureIfNeeded(
    const std::string& name,
    const std::shared_ptr<VkSandboxTexture>& tex,
    std::unordered_map<std::string, std::shared_ptr<VkSandboxTexture>>& textures,
    std::unordered_map<std::string, size_t>& textureIndexMap,
    std::vector<std::shared_ptr<VkSandboxTexture>>& textureList)
{
    if (textures.find(name) == textures.end()) {
        textures[name] = tex;
        textureList.push_back(tex);
        textureIndexMap[name] = textureList.size() - 1;
    }
}