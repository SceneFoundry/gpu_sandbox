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

class sandbox_player : public IGameObject
{
public:
    sandbox_player(std::shared_ptr<IWindowInput> input);

	void onInit() override;
	void onUpdate(float deltaTime) override;

    TransformComponent& getTransform() override;

    std::shared_ptr<IModel> getModel() const override;
    sandbox_camera& getCamera();

 

private:
    std::shared_ptr<IWindowInput>       m_pInput;
    TransformComponent m_transform;
    sandbox_camera m_camera;
    sandbox_mnk_controller m_controller;

    // Configuration
    float m_mouseSensitivity = 0.0025f;
    float m_moveSpeed = 30.0f;

};