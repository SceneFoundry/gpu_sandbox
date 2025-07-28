#pragma once
#include "renderer_i.h"
#include <glm/gtc/matrix_transform.hpp>
#include "transform_component.h"
#include "interfaces/camera_i.h"

class IEntity {
public:

	virtual void onInit() {};
	virtual void onUpdate(float dt) {};
	virtual void onRender(ISandboxRenderer::FrameContext& frame) {};
	virtual TransformComponent& getTransform() = 0;
	virtual ~IEntity() = default;
};