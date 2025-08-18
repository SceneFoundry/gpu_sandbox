#pragma once

#include "interfaces/entity_i.h"
#include "interfaces/model_i.h"
#include "vulkan_wrapper/vulkan_obj.h"
#include <glm/gtc/matrix_transform.hpp>

// std
#include <memory>
#include <unordered_map>
#include <string>


class sandbox_game_object : public IGameObject{
public:

    using id_t = unsigned int;
    using Map = std::unordered_map<id_t, sandbox_game_object>;

    static std::shared_ptr<sandbox_game_object> createGameObject() {
        static id_t currentId = 0;
        return std::make_shared<sandbox_game_object>(currentId++);
    }

    static std::shared_ptr<sandbox_game_object> makePointLight(float intensity = 10.f, float radius = 0.1f, glm::vec3 color = glm::vec3(1.f)) {
        auto gameObj = sandbox_game_object::createGameObject();
        gameObj->m_color = color;
        gameObj->m_transform.scale.x = radius;
        gameObj->m_pointLight = std::make_unique<PointLightComponent>();
        gameObj->m_pointLight->lightIntensity = intensity;
        return gameObj;
    }

    sandbox_game_object(id_t objId);
    sandbox_game_object() = default;
    sandbox_game_object(const sandbox_game_object&) = delete;
    sandbox_game_object& operator=(const sandbox_game_object&) = delete;
    sandbox_game_object(sandbox_game_object&&) = default;
    sandbox_game_object& operator=(sandbox_game_object&&) = default;


    uint32_t getId() const override { return m_id; }

    glm::vec3 getColor() const override { return m_color; }

    PointLightComponent* getPointLight() const override {
        return m_pointLight.get();
    }

    TransformComponent& getTransform() override {
        return m_transform;
    }

    std::shared_ptr<IModel> getModel() const override {
        return m_pModel;
    }

    void setModel(const std::shared_ptr<IModel>& model) {
        m_pModel = model;
    }


    TransformComponent m_transform;
    std::shared_ptr<IModel> m_pModel;
    glm::vec3 m_color{};
    bool m_bIsOBJ{ false };
    ::pointer<PointLightComponent> m_pointLight = nullptr;

    std::string m_cubemapTextureName;
    id_t m_id;
    bool m_bIsSkybox = false;

};