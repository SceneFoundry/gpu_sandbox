#include "engine.h"
#include "key_codes.h"
#include "spdlog/spdlog.h"
#include "frame_info.h"
#include <thread>
#include <chrono>


SandboxEngine::SandboxEngine() {
	// Load Assets
	m_assetManager.preloadGlobalAssets();
}
void SandboxEngine::initialize() {
	m_windowInput = std::make_unique<GLFWWindowInput>(m_window.getGLFWwindow());

	//    m_renderer.registerRenderSystem(std::make_unique<SandboxObjRenderSystem>());
}
void SandboxEngine::initLayer(IGameLayer* game) {
	
	spdlog::info("Engine initialized: window and input ready");
	//game->onRegisterRenderSystems(renderer()), * this);
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
	// 1. Get scene and camera
	IScene& scene = game->getSceneInterface();
//	ICamera& cam = scene.getCamera();

	// 2. Query view/proj each frame
	//cam.updateView();
	//cam.updateProjection(m_renderer.getAspectRatio());


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
		if (!frame.isValid()) return;

		int idx = m_renderer.getFrameIndex();

		//FrameInfo info{
		// idx,
		// deltaTime,
		// frame.primaryGraphicsCommandBuffer,
		// m_renderer.getGlobalDescriptorSet()[idx],
		// scene.getGameObjects(),
		//};

		// Update game and subsystems 
		game->onUpdate(deltaTime);
		//auto& uboBuffer = m_renderer.getUboBuffers()[idx];
		//uboBuffer->writeToBuffer(&ubo);
		//uboBuffer->flush();

	
		// Render Game
		m_renderer.beginSwapChainRenderPass(frame);
		
		//m_renderer.renderSystems(info);
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