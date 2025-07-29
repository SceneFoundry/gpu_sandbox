#include "window.h"
#include <stdexcept>
#include <iostream>


SandboxWindow::SandboxWindow(int w, int h, std::string name) : m_width{ w }, m_height{ h }, m_window_name{ name }
{
	initWindow();
}

SandboxWindow::~SandboxWindow()
{

    // GLFW
    if (m_pwindow) {
        glfwDestroyWindow(m_pwindow);
        m_pwindow = nullptr;
    }
    glfwTerminate();

  
}

void SandboxWindow::initWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	m_pwindow = glfwCreateWindow(m_width, m_height, m_window_name.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(m_pwindow, this);
	glfwSetFramebufferSizeCallback(m_pwindow, framebufferResizeCallback);
}



void SandboxWindow::createSurface(VkInstance instance, VkSurfaceKHR* surface) const {
    if (glfwCreateWindowSurface(instance, m_pwindow, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
    
}
void SandboxWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	auto pwindow = reinterpret_cast<SandboxWindow*>(glfwGetWindowUserPointer(window));
	pwindow->m_bFramebufferResized = true;
	pwindow->m_height = height;
	pwindow->m_width = width;
}