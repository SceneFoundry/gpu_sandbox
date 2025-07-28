// main.cpp
#include <memory>
#include "engine.h"
#include "game/game_layer.h"
#include "asset_manager.h"


int main()
{
    SandboxEngine engine;

    IWindowInput* input   = engine.getInputInterface();
    AssetManager& assetManager = engine.getAssetManager();

    auto gameLayer = std::make_unique<MyGameLayer>(input, assetManager);

    engine.initLayer(gameLayer.get());

    engine.run(std::move(gameLayer));
    
    return 0;
}