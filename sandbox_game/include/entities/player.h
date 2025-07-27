#pragma once
#include "interfaces/game_object_i.h"
#include "interfaces/window_input_i.h"
#include "interfaces/camera_i.h"
#include "transform_component.h"
#include "camera/camera.h"
#include "interfaces/renderer_i.h"

#include "window.h"

#include <glm/glm.hpp>


class SandboxPlayer : public IGameObject, public ICamera
{
public:
    SandboxPlayer(IWindowInput* input);

	void onInit() override;
	void onUpdate(float deltaTime) override;

    TransformComponent& getTransform() override;

    std::shared_ptr<IModel> getModel() const override;

    // ICamera
    void updateView() override;
    void updateProjection(float aspectRatio, float nearZ = 0.1f, float farZ = 100.f) override;
    glm::mat4 getViewMatrix() const override;
    glm::mat4 getProjectionMatrix() const override;
private:
	IWindowInput* m_pInput;
    TransformComponent m_transform;
    SandboxCamera m_camera;


    // Configuration
    float m_mouseSensitivity = 0.0025f;
    float m_moveSpeed = 5.0f;
};