#pragma once
#include <string>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vulkan/vulkan.h>
#include <vector>



class SandboxWindow {

public:
	SandboxWindow(int w, int h, std::string name);
	~SandboxWindow();

	GLFWwindow* getGLFWwindow() const { return m_pwindow; }
	VkExtent2D  getExtent()      const { return { uint32_t(m_width), uint32_t(m_height) }; }

	// only surface creation now:
	VkSurfaceKHR createSurface(VkInstance instance) const;
private:
	void initWindow();
	static void framebufferResizeCallback(GLFWwindow*, int, int);

	int          m_width, m_height;
	bool         m_bFramebufferResized = false;
	std::string  m_window_name;
	GLFWwindow* m_pwindow = nullptr;



};