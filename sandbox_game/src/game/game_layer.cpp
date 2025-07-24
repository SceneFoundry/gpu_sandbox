// game_layer.cpp
#include "game/game_layer.h"
#include <spdlog/spdlog.h>

MyGameLayer::MyGameLayer(IWindowInput* input, AssetManager& assets)
    : m_windowInput(input)
    , m_assetManager(assets)
    , m_scene(input, assets)           // ← pass both here
{
}



void MyGameLayer::onInit()
{
    // e.g. reset your player’s position / state
    spdlog::info("MyGameLayer::onInit");
    m_scene.loadSceneFile("default_scene");
    m_scene.init();
}

void MyGameLayer::onUpdate(float dt)
{
    spdlog::info("MyGameLayer::onUpdate: dt = {}", dt);
    m_scene.update(dt);
}
void MyGameLayer::onRender(ISandboxRenderer::FrameContext& frame) {
    m_scene.render(frame);
}
