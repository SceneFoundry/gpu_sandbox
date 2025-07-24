#include "engine.h"
#include "spdlog/spdlog.h"

#include <thread>
#include <chrono>


SandboxEngine::SandboxEngine() {
	// Load Assets
	m_assetManager.preloadGlobalAssets();
}
void SandboxEngine::initialize() {
	m_windowInput = std::make_unique<GLFWWindowInput>(m_window.getGLFWwindow());
}
void SandboxEngine::initLayer(IGameLayer* game) {
	
	spdlog::info("Engine initialized: window and input ready");
	game->onInit();
}

// TODO: Eventually abstract hard coded glfw calls to a native window interface which depends on the devices platform

void SandboxEngine::run(std::unique_ptr<IGameLayer> game) {
	// Frame logic
	using clock = std::chrono::high_resolution_clock;
	using duration_t = std::chrono::duration<double>;

	constexpr double TARGET_FPS = 60.0;
	constexpr double TARGET_FRAME_TIME = 1.0 / TARGET_FPS;

	auto lastTime = clock::now();

	IWindowInput* input = m_windowInput.get();

	while (!glfwWindowShouldClose(m_window.getGLFWwindow())) {
		// Poll events
		glfwPollEvents();

		// If ESC is down, request the window to close
		if (input->isKeyPressed(SandboxKey::ESCAPE)) {
			glfwSetWindowShouldClose(m_window.getGLFWwindow(), GLFW_TRUE);
		}

		// Compute delta time
		auto now = clock::now();
		double deltaTime = duration_t(now - lastTime).count();
		lastTime = now;

		// Begin recording command buffer
		ISandboxRenderer::FrameContext frame = m_renderer.beginFrame();
		m_renderer.beginSwapChainRenderPass(frame);
		// Update game and subsystems 
		game->onUpdate(deltaTime);
		// Render Game
		game->onRender(frame);
		// End recording commands
		m_renderer.endSwapChainRenderPass(frame);
		m_renderer.endFrame();

		// Frame cap sleep
		auto frameEnd = clock::now();
		double frameTime = duration_t(frameEnd - now).count();
		if (frameTime < TARGET_FRAME_TIME) {
			auto sleepDuration = std::chrono::duration<double>(TARGET_FRAME_TIME - frameTime);
			std::this_thread::sleep_for(sleepDuration);
		}
	}
	m_renderer.waitDeviceIdle();
}