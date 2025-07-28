#pragma once

#include "interfaces/entity_i.h"
#include "interfaces/model_i.h"
#include "vulkan_wrapper/vulkan_obj.h"
#include <glm/gtc/matrix_transform.hpp>

// std
#include <memory>
#include <unordered_map>



class SandboxGameObject : public IGameObject{
public:

    using id_t = unsigned int;
    using Map = std::unordered_map<id_t, SandboxGameObject>;

    static std::shared_ptr<SandboxGameObject> createGameObject() {
        static id_t currentId = 0;
        return std::make_shared<SandboxGameObject>(currentId++);
    }
    SandboxGameObject(id_t objId);


    SandboxGameObject() = default;
    SandboxGameObject(const SandboxGameObject&) = delete;
    SandboxGameObject& operator=(const SandboxGameObject&) = delete;
    SandboxGameObject(SandboxGameObject&&) = default;
    SandboxGameObject& operator=(SandboxGameObject&&) = default;

    id_t getId() const { return m_id; }
    TransformComponent& getTransform() override {
        return m_transform;
    }
    std::shared_ptr<IModel> getModel() const override {
        // m_pObjModel is std::shared_ptr<VkSandboxOBJmodel>, implicitly convertible
        return m_pObjModel;
    }


    TransformComponent m_transform;
    std::shared_ptr<VkSandboxOBJmodel> m_pObjModel;

    bool m_bIsOBJ{ false };


private:


    id_t m_id;

};