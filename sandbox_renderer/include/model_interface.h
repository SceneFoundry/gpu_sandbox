#pragma once
#include "renderer_interface.h"




struct IModel {
public:
	virtual ~IModel() = default;
	virtual void bind(ISandboxRenderer::FrameContext& ctx) = 0;
	virtual void draw(ISandboxRenderer::FrameContext& ctx) = 0;
};

