#pragma once
#include "interfaces/game_object_i.h"
#include "interfaces/window_input_i.h"
#include "input/player_input.h"
#include "interfaces/camera_i.h"
#include "transform_component.h"
#include "camera/camera.h"
#include "interfaces/renderer_i.h"

#include "window.h"

#include <glm/glm.hpp>
#include <memory>

class SandboxPlayer : public IGameObject
{
public:
    SandboxPlayer(std::shared_ptr<IWindowInput> input);

	void onInit() override;
	void onUpdate(float deltaTime) override;

    TransformComponent& getTransform() override;

    std::shared_ptr<IModel> getModel() const override;
    SandboxCamera& getCamera();

 

private:
    std::shared_ptr<IWindowInput>       m_pInput;
    TransformComponent m_transform;
    SandboxCamera m_camera;
    SandboxMNKController m_controller;

    // Configuration
    float m_mouseSensitivity = 0.0025f;
    float m_moveSpeed = 30.0f;

};