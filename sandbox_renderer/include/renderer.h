#pragma once
#include <memory>

class Renderer {
public:
	Renderer() = default;
	~Renderer() = default;

	void initialize();
	void renderFrame();
private:
	//std::unique_ptr<Instance> vulkan_instance;
};