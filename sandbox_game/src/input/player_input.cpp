// player_input.cpp
#include "input/player_input.h"

SandboxMNKController::SandboxMNKController(float moveSpeed, float mouseSensitivity)
    : m_moveSpeed(moveSpeed), m_mouseSensitivity(mouseSensitivity), m_yaw(-90.f), m_pitch(0.f)
{
}

void SandboxMNKController::mouseCallback(glm::vec2 delta) {
    m_mouseDelta = delta;
}

void SandboxMNKController::update(float dt, std::shared_ptr<IWindowInput> input, TransformComponent& transform) {

    float pitchDeg = glm::degrees(transform.rotation.x);
    float yawDeg = glm::degrees(transform.rotation.y);

    glm::vec3 front;
    front.x = cos(glm::radians(yawDeg)) * cos(glm::radians(pitchDeg));
    front.y = sin(glm::radians(pitchDeg));
    front.z = sin(glm::radians(yawDeg)) * cos(glm::radians(pitchDeg));
    front = glm::normalize(front);

    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.f, 1.f, 0.f)));
    glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);

    glm::vec3 dir(0.0f);
    if (input->isKeyPressed(SandboxKey::W)) dir += front;
    if (input->isKeyPressed(SandboxKey::S)) dir -= front;
    if (input->isKeyPressed(SandboxKey::A)) dir -= right;
    if (input->isKeyPressed(SandboxKey::D)) dir += right;
    if (input->isKeyPressed(SandboxKey::Q)) dir -= up;
    if (input->isKeyPressed(SandboxKey::E)) dir += up;

    if (glm::length(dir) > 0.0f)
        transform.translation += glm::normalize(dir) * m_moveSpeed * dt;

    // Mouse look
    m_yaw += m_mouseDelta.x * m_mouseSensitivity;
    m_pitch -= m_mouseDelta.y * m_mouseSensitivity;
    m_pitch = glm::clamp(m_pitch, -89.f, 89.f);

    transform.rotation = glm::vec3(
        glm::radians(m_pitch),
        glm::radians(m_yaw),
        0.f
    );

    m_mouseDelta = glm::vec2(0.f);
}
