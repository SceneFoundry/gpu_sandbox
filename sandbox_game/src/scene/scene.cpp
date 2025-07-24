#include "scene/scene.h"
#include "entities/player.h"
#include "entities/game_object.h"

#include <json.hpp>


#include <glm/gtc/constants.hpp>        // for glm::two_pi
#include <spdlog/spdlog.h>


using json = nlohmann::json;

SandboxScene::SandboxScene(IWindowInput* input, AssetManager& assetManager)
	: m_pInput(input), m_assetManager(assetManager)
{
}

void SandboxScene::init() {
	// Instantiate player and any NPCs
	auto player = std::make_shared<SandboxPlayer>(m_pInput);
	player->onInit();
	m_entities.push_back(player);

	// … load environment, lights, etc. …
}


void SandboxScene::update(float dt) {
	for (auto& e : m_entities) {
		e->onUpdate(dt);
	}
}

void SandboxScene::render(ISandboxRenderer::FrameContext& frame) {
	for (auto& e : m_entities) {
		e->onRender(frame);
	}
}


void SandboxScene::loadSceneFile(const std::string& fileName) {
    std::string path = std::string(PROJECT_ROOT_DIR) + "/sandbox_game/res/scenes/" + fileName + ".json";

    std::ifstream inFile(path);
    if (!inFile.is_open()) {
        throw std::runtime_error("Could not open scene file: " + path);
    }

    json sceneJson;
    inFile >> sceneJson;

    spdlog::info("Loading scene file: {} ({})", fileName, path);

    for (auto& objJson : sceneJson["objects"]) {
        // Create a new game object
        auto gameObject = SandboxGameObject::createGameObject();  // Error: use of undefined type..

        // Load model (OBJ only for now)
        if (auto it = objJson.find("model"); it != objJson.end()) {
            const std::string modelName = it->get<std::string>();
            if (auto objModel = m_assetManager.getOBJModel(modelName)) {
                gameObject.m_pObjModel = objModel;
                gameObject.m_bIsOBJ = true;
            }
            else {
                throw std::runtime_error("OBJ model not found in cache: " + modelName);
            }
        }

        // Load transform
        auto pos = objJson.value("position", std::vector<float>{0.f, 0.f, 0.f});
        auto rot = objJson.value("rotation", std::vector<float>{0.f, 0.f, 0.f});
        auto scl = objJson.value("scale", std::vector<float>{1.f, 1.f, 1.f});
        gameObject.m_transform.translation = { pos[0], pos[1], pos[2] };
        gameObject.m_transform.rotation = { rot[0], rot[1], rot[2] };
        gameObject.m_transform.scale = { scl[0], scl[1], scl[2] };

        m_gameObjects.emplace(gameObject.getId(), std::move(gameObject));
    }

    spdlog::info("Scene '{}' loaded. Total objects: {}", fileName, m_gameObjects.size());
   
}