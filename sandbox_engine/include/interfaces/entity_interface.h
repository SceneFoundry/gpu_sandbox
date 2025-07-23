#pragma once
#include "renderer_interface.h"

class IEntity {
public:
	virtual void onInit() = 0;
	virtual void onUpdate(float dt) = 0;
	virtual void onRender(ISandboxRenderer::FrameContext& frame) = 0;
	virtual ~IEntity() = default;
};