#pragma once
#include "interfaces/game_layer_i.h"
#include "interfaces/window_input_i.h"
#include "interfaces/renderer_i.h"
#include "entities/player.h"
#include "scene/scene.h"
#include <iostream>
#include <memory>

class MyGameLayer : public IGameLayer {
public:

    MyGameLayer(std::shared_ptr<IWindowInput> input, AssetManager& assets);
    

    void onInit() override;
    void onUpdate(float dt) override;

    IScene& getSceneInterface() override;
private:
    ::pointer<sandbox_scene> m_scene;
    std::shared_ptr<IWindowInput> m_windowInput;
    AssetManager& m_assetManager;

};