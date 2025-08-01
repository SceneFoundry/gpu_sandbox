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