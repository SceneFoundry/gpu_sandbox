#pragma once
#include "renderer_interface.h"
#include <glm/gtc/matrix_transform.hpp>

struct TransformComponent {
	glm::vec3 translation{};
	glm::vec3 scale{ 1.f };
	glm::vec3 rotation{};

	glm::mat4 mat4() const;
	glm::mat3 normalMatrix() const;
};
class IEntity {
public:

	virtual void onInit() {};
	virtual void onUpdate(float dt) {};
	virtual void onRender(ISandboxRenderer::FrameContext& frame) {};
	virtual TransformComponent& getTransform() = 0;
	virtual ~IEntity() = default;


};