#pragma once
#include "interfaces/game_layer_interface.h"
#include "interfaces/window_input_interface.h"
#include "renderer_interface.h"
#include "entities/player.h"
#include "scene/scene.h"
#include <iostream>


class MyGameLayer : public IGameLayer {
public:

    MyGameLayer(IWindowInput* input, AssetManager& assets);
    

    void onInit() override;
    void onUpdate(float dt) override;
    void onRender(ISandboxRenderer::FrameContext& frame) override;

private:
    SandboxScene m_scene;
    IWindowInput* m_windowInput;
    AssetManager& m_assetManager;
};