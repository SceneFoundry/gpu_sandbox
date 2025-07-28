#pragma once
#include "interfaces/game_layer_i.h"
#include "interfaces/window_input_i.h"
#include "interfaces/renderer_i.h"
#include "entities/player.h"
#include "scene/scene.h"
#include "interfaces/registry_i.h"
#include <iostream>
#include <memory>

class MyGameLayer : public IGameLayer {
public:

    MyGameLayer(IWindowInput* input, AssetManager& assets);
    

    void onInit() override;
    void onUpdate(float dt) override;

    IScene& getSceneInterface() override;
private:
    std::unique_ptr<SandboxScene> m_scene;
    IWindowInput* m_windowInput;
    AssetManager& m_assetManager;

};