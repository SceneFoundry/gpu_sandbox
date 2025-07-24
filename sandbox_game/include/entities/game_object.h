#pragma once

#include "interfaces/entity_interface.h"
#include "vulkan_wrapper/obj_model.h"
#include <glm/gtc/matrix_transform.hpp>

// std
#include <memory>
#include <unordered_map>



class SandboxGameObject : public IEntity{
public:

    using id_t = unsigned int;
    using Map = std::unordered_map<id_t, SandboxGameObject>;

    static SandboxGameObject createGameObject() {
        static id_t currentId = 0;
        return SandboxGameObject{ currentId++ };
    }

    SandboxGameObject(id_t objId);


    SandboxGameObject() = default;
    SandboxGameObject(const SandboxGameObject&) = delete;
    SandboxGameObject& operator=(const SandboxGameObject&) = delete;
    SandboxGameObject(SandboxGameObject&&) = default;
    SandboxGameObject& operator=(SandboxGameObject&&) = default;

    id_t getId() const { return m_id; }
    TransformComponent& getTransform() override { return m_transform; }

    //bool isRenderable() const { return m_pObjModel; }

    //std::string_view getName() const { return _name; }

    // GameObject-specific data
    TransformComponent m_transform;
    std::shared_ptr<VkSandboxOBJmodel> m_pObjModel;

    bool m_bIsOBJ{ false };


private:


    id_t m_id;

};