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
        throw std::runtime_error("Failed to open OBJ model list JSON.");
    }

    json modelJson;
    in >> modelJson;

    for (const auto& entry : modelJson["models"]) {
        const std::string name = entry["name"];
        const std::string path = std::string(PROJECT_ROOT_DIR) + "/res/models/" + entry["path"].get<std::string>();

        try {
            auto model = loadObjModel(name, path, false);
            spdlog::info("[AssetManager] Successfully loaded OBJ model '{}' from '{}'", name, path);
        }
        catch (const std::exception& e) {
            spdlog::error("[AssetManager] Failed to load OBJ '{}': {}", name, e.what());
        }
    }
}


std::shared_ptr<VkSandboxOBJmodel> AssetManager::loadObjModel(
    const std::string& name,
    const std::string& filepath,
    bool isSkybox
) {
    // 1) cache check
    if (auto it = objModelCache.find(name); it != objModelCache.end())
        return it->second;

    // 2) load
    auto model = VkSandboxOBJmodel::createModelFromFile(m_device, filepath, isSkybox);

    // 3) cache & return
    objModelCache[name] = model;
    return model;
}



// Getters
//------------------------------------------------------------------------------
std::shared_ptr<VkSandboxOBJmodel> AssetManager::getOBJModel(const std::string& name) const {
    auto it = objModelCache.find(name);
    if (it != objModelCache.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}