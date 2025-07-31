#include "scene/scene.h"
#include "entities/player.h"
#include "entities/game_object.h"

#include <json.hpp>


#include <glm/gtc/constants.hpp>
#include <spdlog/spdlog.h>


using json = nlohmann::json;

SandboxScene::SandboxScene(std::shared_ptr<IWindowInput> input, AssetManager& assetManager)
	: m_pInput(std::move(input)), m_assetManager(assetManager) 
{
}

void SandboxScene::init() {
    auto player = std::make_shared<SandboxPlayer>(m_pInput);
    
    player->getTransform().translation = m_initialCameraPosition;
    player->getTransform().rotation = m_initialCameraRotation;
    player->onInit();

    m_players.push_back(player);

}

void SandboxScene::update(float dt) {
    for (auto& player : m_players) {
        player->onUpdate(dt);
    }

    for (auto& [id, obj] : m_gameObjects) {
        obj->onUpdate(dt);
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

    if (sceneJson.contains("camera")) {
        const auto& camJson = sceneJson["camera"];

        auto pos = camJson.value("position", std::vector<float>{0.f, 0.f, 0.f});
        auto rot = camJson.value("rotation", std::vector<float>{0.f, 0.f, 0.f});

        m_initialCameraPosition = { pos[0], pos[1], pos[2] };
        m_initialCameraRotation = {
            glm::radians(rot[0]),
            glm::radians(rot[1]),
            glm::radians(rot[2])
        };

        spdlog::info("Camera position: ({}, {}, {}), rotation (deg): ({}, {}, {})",
            pos[0], pos[1], pos[2], rot[0], rot[1], rot[2]);
    }

    for (auto& objJson : sceneJson["objects"]) {

        if (objJson.value("special", "") == "lights") {
            int count = objJson.value("count", 1);
            float radius = objJson.value("radius", 4.8f);
            float height = objJson.value("height", -2.5f);
            float intensity = objJson.value("intensity", 15.8f);
            const auto& colorsJson = objJson["colors"];

            for (int i = 0; i < count; ++i) {
                float angle = i * glm::two_pi<float>() / count;
                glm::vec3 pos = {
                    radius * std::cos(angle),
                    height,
                    radius * std::sin(angle)
                };

                auto colorArray = colorsJson[i % colorsJson.size()];
                glm::vec3 color = {
                    colorArray[0],
                    colorArray[1],
                    colorArray[2]
                };

                auto light = SandboxGameObject::makePointLight(intensity, 0.1f, color);
                light->getTransform().translation = pos;

                spdlog::info("Placed point light at ({}, {}, {})", pos.x, pos.y, pos.z);

                m_gameObjects.emplace(light->getId(), std::move(light));
            }

            continue; // Skip normal parsing for this object
        }

       
        auto gameObject = SandboxGameObject::createGameObject();

        if (auto it = objJson.find("model"); it != objJson.end()) {
            const std::string modelName = it->get<std::string>();
            if (auto objModel = m_assetManager.getOBJModel(modelName)) {
                gameObject->m_pObjModel = objModel;
                gameObject->m_bIsOBJ = true;
            }
            else {
                throw std::runtime_error("OBJ model not found in cache: " + modelName);
            }
        }

        auto pos = objJson.value("position", std::vector<float>{0.f, 0.f, 0.f});
        auto rot = objJson.value("rotation", std::vector<float>{0.f, 0.f, 0.f});
        auto scl = objJson.value("scale", std::vector<float>{1.f, 1.f, 1.f});

        gameObject->m_transform.translation = { pos[0], pos[1], pos[2] };
        gameObject->m_transform.rotation = { rot[0], rot[1], rot[2] };
        gameObject->m_transform.scale = { scl[0], scl[1], scl[2] };

        spdlog::info("Loaded GameObject '{}' - Pos: ({}, {}, {}), Rot: ({}, {}, {}), Scale: ({}, {}, {})",
            objJson.value("name", "unnamed"),
            pos[0], pos[1], pos[2],
            rot[0], rot[1], rot[2],
            scl[0], scl[1], scl[2]);

        m_gameObjects.emplace(gameObject->getId(), std::move(gameObject));
    }

    spdlog::info("Scene '{}' loaded. Total objects: {}", fileName, m_gameObjects.size());
}


SandboxCamera& SandboxScene::getCamera() {
    if (m_players.empty()) {
        throw std::runtime_error("no players available to get camera from");
    }

    auto* player = dynamic_cast<SandboxPlayer*>(m_players[0].get());
    if (!player) {
        throw std::runtime_error("first player is not a SandboxPlayer");
    }

    return player->getCamera();
}