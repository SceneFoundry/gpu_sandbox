#pragma once
#include "interfaces/window_input_interface.h"
#include "renderer_interface.h"
#include "asset_manager.h"
#include "entities/game_object.h"
#include <memory>
#include <vector>
#include <string>
#include <fstream>

class SandboxScene {
public:
	SandboxScene(IWindowInput* input, AssetManager& assetManager);      // pass input so your Player can read it
	void init();                     // load models, spawn entities
	void update(float dt);           // advance all entities
	void render(ISandboxRenderer::FrameContext& frame);    // draw calls
	void loadSceneFile(const std::string& fileName);

	std::unordered_map<uint32_t, SandboxGameObject>& getGameObjects() { return m_gameObjects; }

	SandboxGameObject* getGameObject(uint32_t id) {
		auto it = m_gameObjects.find(id);
		return (it != m_gameObjects.end()) ? &it->second : nullptr;
	}
private:
	IWindowInput* m_pInput;           // raw pointer is OK since engine owns it
	std::vector<std::shared_ptr<IEntity>> m_entities;
	AssetManager& m_assetManager;

	std::unordered_map<uint32_t, SandboxGameObject> m_gameObjects;

};