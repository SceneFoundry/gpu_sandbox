#pragma once
#include "interfaces/entity_interface.h"
#include "interfaces/window_input_interface.h"
#include "renderer_interface.h"
#include <memory>
#include <vector>

class SandboxScene {
public:
	SandboxScene(IWindowInput* input);      // pass input so your Player can read it
	void init();                     // load models, spawn entities
	void update(float dt);           // advance all entities
	void render(ISandboxRenderer::FrameContext& frame);    // draw calls
private:
	IWindowInput* m_pInput;           // raw pointer is OK since engine owns it
	std::vector<std::shared_ptr<IEntity>> m_entities;
};