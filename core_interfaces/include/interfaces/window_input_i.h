#pragma once
#include "key_codes.h"

struct IWindowInput {
	virtual ~IWindowInput() = default;


    virtual void lockCursor(bool lock) = 0;
    virtual void setCursorCallback(void (*callback)(double, double)) = 0;

    virtual void getFramebufferSize(int& width, int& height) const = 0;
    virtual void getMouseDelta(double& dx, double& dy) = 0;
    virtual bool isKeyPressed(SandboxKey key) const = 0;
    virtual bool isMouseButtonPressed(int button) const = 0;
};