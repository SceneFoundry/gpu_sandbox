#include "engine.h"
#include "spdlog/spdlog.h"

#include <thread>
#include <chrono>


SandboxEngine::SandboxEngine() {

}


void SandboxEngine::run() {
	while (!glfwWindowShouldClose(m_window.getGLFWwindow())) {
		glfwPollEvents();

		auto commandBuffer = m_renderer.beginFrame();
		m_renderer.beginSwapChainRenderPass(commandBuffer);
		m_renderer.endSwapChainRenderPass(commandBuffer);
		m_renderer.endFrame();
	}
	m_renderer.waitDeviceIdle();
}