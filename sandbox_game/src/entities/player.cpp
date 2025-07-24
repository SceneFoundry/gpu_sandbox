#include "entities/player.h"
#include <glm/gtc/matrix_transform.hpp>


SandboxPlayer::SandboxPlayer(IWindowInput* input)
    : m_pInput(input)
{
}

void SandboxPlayer::onInit() {
    // Lock & hide the cursor
    m_pInput->lockCursor(true);

    // Compute initial projection
    int w, h;
    m_pInput->getFramebufferSize(w, h);
    float aspect = w > 0 && h > 0 ? float(w) / float(h) : 1.0f;
    m_proj = glm::perspective(m_fovY, aspect, m_nearZ, m_farZ);

    // Flip Y for Vulkan clip space
    m_proj[1][1] *= -1.0f;

    // Compute initial view
    glm::vec3 forward;
    forward.x = cos(m_pitch) * sin(m_yaw);
    forward.y = sin(m_pitch);
    forward.z = cos(m_pitch) * cos(m_yaw);
    m_view = glm::lookAt(m_position, m_position + forward, { 0,1,0 });
}

void SandboxPlayer::onUpdate(float dt) {
    // 1) Mouse look
    double dx, dy;
    m_pInput->getMouseDelta(dx, dy);
    m_yaw += float(dx) * m_mouseSensitivity;
    m_pitch += float(-dy) * m_mouseSensitivity;
    m_pitch = glm::clamp(m_pitch, glm::radians(-89.0f), glm::radians(89.0f));

    // 2) Movement
    glm::vec3 forward;
    forward.x = cos(m_pitch) * sin(m_yaw);
    forward.y = sin(m_pitch);
    forward.z = cos(m_pitch) * cos(m_yaw);
    forward = glm::normalize(forward);

    glm::vec3 right = glm::normalize(glm::cross(forward, { 0,1,0 }));

    if (m_pInput->isKeyPressed(SandboxKey::W)) m_position += forward * m_moveSpeed * dt;
    if (m_pInput->isKeyPressed(SandboxKey::S)) m_position -= forward * m_moveSpeed * dt;
    if (m_pInput->isKeyPressed(SandboxKey::A)) m_position -= right * m_moveSpeed * dt;
    if (m_pInput->isKeyPressed(SandboxKey::D)) m_position += right * m_moveSpeed * dt;

    // 3) Handle window resize (recompute projection)
    int w, h;
    m_pInput->getFramebufferSize(w, h);
    if (w > 0 && h > 0) {
        float aspect = float(w) / float(h);
        m_proj = glm::perspective(m_fovY, aspect, m_nearZ, m_farZ);
        m_proj[1][1] *= -1.0f;
    }

    // 4) Recompute view
    m_view = glm::lookAt(m_position, m_position + forward, { 0,1,0 });
}

void SandboxPlayer::onRender(ISandboxRenderer::FrameContext& frame) {
    // You *could* push your view/proj into a uniform or push‑constant here,
    // but in a data‑driven design you’d instead expose getViewMatrix()/getProjectionMatrix()
    // and let your RenderSystem bind them when drawing meshes.
}