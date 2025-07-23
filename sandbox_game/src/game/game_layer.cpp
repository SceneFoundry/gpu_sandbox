// game_layer.cpp
#include "game/game_layer.h"
#include <spdlog/spdlog.h>

MyGameLayer::MyGameLayer(IWindowInput* input) : m_windowInput(input), m_scene(input)
{
}


void MyGameLayer::onInit()
{
    // e.g. reset your player’s position / state
    spdlog::info("MyGameLayer::onInit");
    m_scene.init();
}

void MyGameLayer::onUpdate(float dt)
{
    // e.g. read input and move your player
    // float dx = m_input->isKeyPressed(SandboxKey::W) ? +1.f : 0.f;
    // … etc …
    spdlog::info("MyGameLayer::onUpdate: dt = {}", dt);
    m_scene.update(dt);
}
void MyGameLayer::onRender(ISandboxRenderer::FrameContext& frame) {
    m_scene.render(frame);
}
