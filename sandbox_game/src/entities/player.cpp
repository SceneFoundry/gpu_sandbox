#include "entities/player.h"
#include <glm/gtc/matrix_transform.hpp>
#include "key_codes.h"

SandboxPlayer::SandboxPlayer(IWindowInput* input)
    : m_pInput(input)
    , m_camera(glm::vec3(0.f, 0.f, 3.f))
{
}

void SandboxPlayer::onInit() {
    // Lock & hide the cursor
    m_pInput->lockCursor(true);


}

void SandboxPlayer::onUpdate(float dt) {
    // Compute initial projection
  // WASD movement
    if (m_pInput->isKeyPressed(SandboxKey::W))
        m_camera.move(m_camera.getForwardVector() * dt * m_moveSpeed);
    if (m_pInput->isKeyPressed(SandboxKey::S))
        m_camera.move(-m_camera.getForwardVector() * dt * m_moveSpeed);
    if (m_pInput->isKeyPressed(SandboxKey::A))
        m_camera.move(-m_camera.getRightVector() * dt * m_moveSpeed);
    if (m_pInput->isKeyPressed(SandboxKey::D))
        m_camera.move(m_camera.getRightVector() * dt * m_moveSpeed);

    // Mouse look
//    auto [dx, dy] = m_pInput->getMouseDelta();
  //  m_camera.rotate(dx * m_mouseSensitivity, dy * m_mouseSensitivity);

    // Recompute view matrix
    m_camera.updateView();
}
TransformComponent& SandboxPlayer::getTransform() {
    return m_transform;
}

std::shared_ptr<IModel> SandboxPlayer::getModel() const {
    return nullptr; // Player has no mesh
}

void SandboxPlayer::updateView() {
    m_camera.setPosition(m_transform.translation);
    m_camera.updateView();
}

void SandboxPlayer::updateProjection(float aspect, float nearZ, float farZ) {
    m_camera.updateProjection(aspect, nearZ, farZ);
}

glm::mat4 SandboxPlayer::getViewMatrix() const {
    return m_camera.getViewMatrix();
}

glm::mat4 SandboxPlayer::getProjectionMatrix() const {
    return m_camera.getProjectionMatrix();
}

