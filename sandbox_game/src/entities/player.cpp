#include "entities/player.h"
#include <glm/gtc/matrix_transform.hpp>
#include "key_codes.h"
#include <spdlog/spdlog.h>

sandbox_player::sandbox_player(std::shared_ptr<IWindowInput> input)
    : m_pInput(std::move(input))
    , m_camera(glm::vec3(0.f, 0.f, 3.f))
{
}

void sandbox_player::onInit() {  

}

void sandbox_player::onUpdate(float dt) {
    if (!m_pInput) return;

    try {
        double dx = 0, dy = 0;
        m_pInput->getMouseDelta(dx, dy);
        m_controller.mouseCallback(glm::vec2(dx, dy));
        m_controller.update(dt, m_pInput, m_transform);

        m_camera.setPosition(m_transform.translation);
        m_camera.setRotation(m_transform.rotation);

        int w, h;
        m_pInput->getFramebufferSize(w, h);
        float aspect = h == 0 ? 1.0f : static_cast<float>(w) / h;
        m_camera.updateProjection(aspect, 0.1f, 300.f);
    }
    catch (const std::exception& e) {
        spdlog::error("Exception in sandbox_player::onUpdate(): {}", e.what());
    }
    catch (...) {
        spdlog::error("Unknown exception in sandbox_player::onUpdate()");
    }
}

TransformComponent& sandbox_player::getTransform() {
    return m_transform;
}

std::shared_ptr<IModel> sandbox_player::getModel() const {
    return nullptr; 
}


sandbox_camera& sandbox_player::getCamera() {
    return m_camera;
}