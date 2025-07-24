// main.cpp
#include <memory>
#include "engine.h"
#include "game/game_layer.h"
#include "asset_manager.h"


int main()
{
    SandboxEngine engine;
    // 1) Initialize engine subsystems
    engine.initialize();

    // 2) Construct game layer with input interface and asset manager
    IWindowInput* input   = engine.getInputInterface();
    AssetManager& assets = engine.getAssetManager();

    auto gameLayer = std::make_unique<MyGameLayer>(input, assets);

    // 3) Initialize the game layer
    engine.initLayer(gameLayer.get());

    // 4) Enter main loop
    engine.run(std::move(gameLayer));
    
    return 0;
}