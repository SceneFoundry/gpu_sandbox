// IGameObject.h
#pragma once
#include "transform_component.h"
#include "renderer_i.h"           // for FrameContext
#include "interfaces/model_i.h"
#include <memory>
#include <optional>
#include <glm/vec3.hpp>

struct IModel;


struct PointLightComponent
{
    float lightIntensity = 1.0f;
};


struct IGameObject {
    virtual ~IGameObject() = default;

    /// Called once at spawn or scene init.
    virtual void onInit() {}

    /// Called each frame before render.
    virtual void onUpdate(float deltaTime) {}

    /// Every object must expose its Transform.
    virtual TransformComponent& getTransform() = 0;

    virtual std::shared_ptr<IModel> getModel() const = 0;

    // Optional extension interface:
    // Optional extensions
    virtual glm::vec3 getColor() const { return glm::vec3(1.f); }
    virtual const PointLightComponent* getPointLight() const { return nullptr; }
    virtual uint32_t getId() const { return 0; }
};
