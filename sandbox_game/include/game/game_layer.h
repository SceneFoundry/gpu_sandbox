#pragma once
#include "interfaces/game_layer_interface.h"
#include "interfaces/window_input_interface.h"
#include "renderer_interface.h"
#include "player/player.h"
#include "scene/scene.h"
#include <iostream>


class MyGameLayer : public IGameLayer {
public:

    MyGameLayer(IWindowInput* input);  // pass input to constructor
    

    void onInit() override;
    void onUpdate(float dt) override;
    void onRender(ISandboxRenderer::FrameContext& frame) override;

private:
    SandboxScene m_scene;
    IWindowInput* m_windowInput;
};