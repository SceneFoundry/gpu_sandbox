#pragma once
#include "interfaces/window_input_i.h"
#include "GLFW/glfw3.h"

class GLFWWindowInput : public IWindowInput {
public:
    explicit GLFWWindowInput(GLFWwindow* window);

    void lockCursor(bool lock) override;
    void setCursorCallback(void (*callback)(double, double)) override;
    void getFramebufferSize(int& width, int& height) const override;
    bool isKeyPressed(SandboxKey key) const override;
    bool isMouseButtonPressed(int button) const override;
    void getMouseDelta(double& dx, double& dy) override;

private:
    int mapKeyToGLFW(SandboxKey key) const;
    static void cursorPosCallbackStatic(GLFWwindow* window, double x, double y);
    GLFWwindow* m_pwindow;

    mutable double m_lastX = 0.0;
    mutable double m_lastY = 0.0;
    mutable bool m_firstMouse = true;

    void (*m_cursorCallback)(double, double) = nullptr;
};