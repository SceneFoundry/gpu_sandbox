#pragma once
#include "interfaces/window_input_i.h"

#include "interfaces/scene_i.h"
#include "interfaces/entity_i.h"
#include "entities/player.h"
#include "asset_manager.h"
#include "entities/game_object.h"
#include <memory>
#include <vector>
#include <string>
#include <fstream>

class SandboxScene : public IScene {
public:
	SandboxScene(IWindowInput* input, AssetManager& assetManager);      // pass input so your Player can read it
	void init() override;                 // load models, spawn entities
	void update(float dt) override;        // advance all entities

	void loadSceneFile(const std::string& fileName);

	std::unordered_map<unsigned int, std::shared_ptr<IGameObject>>&
		getGameObjects() override { return m_gameObjects; }


	std::pair<glm::mat4, glm::mat4> getMainCameraMatrices()const;
private:
	IWindowInput* m_pInput;           // raw pointer is OK since engine owns it
	AssetManager& m_assetManager;

	ICamera& getCamera() override;

	std::vector<std::shared_ptr<SandboxPlayer>> m_players;
	std::unordered_map<unsigned int, std::shared_ptr<IGameObject>>  m_gameObjects;
	glm::vec3 m_initialCameraPosition{ 0.f };
	glm::vec3 m_initialCameraRotation{ 0.f };

};