// IScene.h
#pragma once

#include <unordered_map>
#include <memory>
#include "interfaces/game_object_i.h"
#include "interfaces/camera_i.h"
#include "interfaces/renderer_i.h"   // for FrameContext

class ICamera;
struct IGameObject;

struct IScene {
    virtual ~IScene() = default;

    /// Load or spawn your objects.
    virtual void init() = 0;

    /// Advance game logic (called before render).
    virtual void update(float deltaTime) = 0;
    
    virtual ICamera& getCamera() = 0;
    /// Allow engine to pull the object map for things like editor or lighting.
    virtual std::unordered_map<unsigned int, std::shared_ptr<IGameObject>>& getGameObjects() = 0;
};
