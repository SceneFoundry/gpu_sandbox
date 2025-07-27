// game_layer.cpp
#include "game/game_layer.h"
#include <spdlog/spdlog.h>

MyGameLayer::MyGameLayer(IWindowInput* input, AssetManager& assets)
    : m_windowInput(input)
    , m_assetManager(assets)
{
}



void MyGameLayer::onInit()
{
    // e.g. reset your player’s position / state
    spdlog::info("MyGameLayer::onInit");
    m_scene = std::make_unique<SandboxScene>(m_windowInput, m_assetManager);
    m_scene->loadSceneFile("default_scene");
    m_scene->init();
}

void MyGameLayer::onUpdate(float dt)
{
    m_scene->update(dt);
}


IScene& MyGameLayer::getSceneInterface() {
    return *m_scene;
}
