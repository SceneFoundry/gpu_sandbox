// main.cpp
#include <memory>
#include "engine.h"
#include "game/game_layer.h"
#include "asset_manager.h"


int main()
{
    SandboxEngine engine;

    std::shared_ptr<IWindowInput> windowInput = engine.getInputSharedPtr();
    AssetManager& assetManager = engine.getAssetManager();

    auto gameLayer = øcreate_pointer<MyGameLayer>(windowInput, assetManager);

    engine.initLayer(gameLayer.get());

    engine.run(std::move(gameLayer));
    
    return 0;
}