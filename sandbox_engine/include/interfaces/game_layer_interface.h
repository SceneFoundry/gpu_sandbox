#pragma once
#include "renderer_interface.h"

class IGameLayer {
public:
	virtual void onInit() = 0;
	virtual void onUpdate(float deltaTime) = 0;
	virtual void onRender(ISandboxRenderer::FrameContext& frame) = 0;
	virtual ~IGameLayer() = default;
};