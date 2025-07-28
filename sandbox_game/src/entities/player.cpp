#include "entities/player.h"
#include <glm/gtc/matrix_transform.hpp>
#include "key_codes.h"

SandboxPlayer::SandboxPlayer(IWindowInput* input)
    : m_pInput(input)
    , m_camera(glm::vec3(0.f, 0.f, 3.f))
{
}

void SandboxPlayer::onInit() {  

}

void SandboxPlayer::onUpdate(float dt) {
    double dx, dy;
    m_pInput->getMouseDelta(dx, dy);
    m_controller.mouseCallback(glm::vec2(dx, dy));
    m_controller.update(dt, m_pInput, m_transform);


    m_camera.setPosition(m_transform.translation);
    m_camera.setRotation(m_transform.rotation);


    int w, h;
    m_pInput->getFramebufferSize(w, h);
    float aspect = static_cast<float>(w) / static_cast<float>(h);
    m_camera.updateProjection(aspect, 0.1f, 300.f);
}

TransformComponent& SandboxPlayer::getTransform() {
    return m_transform;
}

std::shared_ptr<IModel> SandboxPlayer::getModel() const {
    return nullptr; 
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

