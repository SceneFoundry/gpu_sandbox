#pragma once
#include "interfaces/entity_interface.h"
#include "interfaces/window_input_interface.h"
#include "renderer_interface.h"

#include "window.h"

#include <glm/glm.hpp>


class SandboxPlayer : public IEntity
{
public:
    SandboxPlayer(IWindowInput* input);

	void onInit() override;
	void onUpdate(float deltaTime) override;
	void onRender(ISandboxRenderer::FrameContext& frame) override;

    // Expose camera matrices to other systems if needed
    const glm::mat4& getViewMatrix()       const { return m_view; }
    const glm::mat4& getProjectionMatrix() const { return m_proj; }

private:
	IWindowInput* m_pInput;

    // Camera state
    glm::vec3 m_position{ 0.0f, 0.0f, -5.0f };
    float     m_yaw = glm::radians(0.0f);
    float     m_pitch = glm::radians(0.0f);
    float     m_fovY = glm::radians(45.0f);
    float     m_nearZ = 0.1f;
    float     m_farZ = 300.0f;

    // Computed each frame
    glm::mat4 m_view{ 1.0f };
    glm::mat4 m_proj{ 1.0f };

    // Configuration
    float m_mouseSensitivity = 0.0025f;
    float m_moveSpeed = 5.0f;
};