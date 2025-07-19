#include "engine.h"
#include "spdlog/spdlog.h"

#include <thread>
#include <chrono>


Engine::Engine() {
	initialize();
}
void Engine::initialize() {
	
	_instanceHandle = _vkInstance.instance();
	_surface = _window.createSurface(_instanceHandle);
	_device = std::make_unique<SandboxDevice>(_instanceHandle, _surface);
}

void Engine::run() {
	while (!glfwWindowShouldClose(_window.getGLFWwindow())) {
		glfwPollEvents();
	}
	vkDeviceWaitIdle(_device->device());
}