// IGameObject.h
#pragma once
#include "transform_component.h"
#include "renderer_i.h"           // for FrameContext
#include "interfaces/model_i.h"
#include <memory>

struct IModel;

struct IGameObject {
    virtual ~IGameObject() = default;

    /// Called once at spawn or scene init.
    virtual void onInit() {}

    /// Called each frame before render.
    virtual void onUpdate(float deltaTime) {}

    /// Every object must expose its Transform.
    virtual TransformComponent& getTransform() = 0;

    virtual std::shared_ptr<IModel> getModel() const = 0;
};
