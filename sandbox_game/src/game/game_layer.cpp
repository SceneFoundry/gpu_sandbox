// game_layer.cpp
#include "game/game_layer.h"
#include <spdlog/spdlog.h>

MyGameLayer::MyGameLayer(std::shared_ptr<IWindowInput> input, AssetManager& assets)
    : m_windowInput(std::move(input))
    , m_assetManager(assets)
{
}

void MyGameLayer::onInit()
{
    spdlog::info("MyGameLayer::onInit");
    m_scene = std::make_unique<SandboxScene>(m_windowInput, m_assetManager);
    m_scene->loadSceneFile("default_scene"); // TODO: Eventually specify which scene file to load in a better way than this probably via UI 
    m_scene->init();
}

void MyGameLayer::onUpdate(float dt)
{
    m_scene->update(dt);
}


IScene& MyGameLayer::getSceneInterface() {
    return *m_scene;
}
