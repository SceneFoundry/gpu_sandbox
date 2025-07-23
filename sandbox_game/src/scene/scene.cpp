#include "scene/scene.h"
#include "player/player.h"

SandboxScene::SandboxScene(IWindowInput* input)
	: m_pInput(input)
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