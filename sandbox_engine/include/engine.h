#pragma once
#include <memory>
#include "window.h"
#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/vulkan_instance.h"
#include "vulkan_wrapper/vulkan_renderer.h"
#include "interfaces/game_layer_i.h"
#include "interfaces/camera_i.h"
#include "common/glfw_input.h"
#include "render_scene_data.h"
#include "asset_manager.h"



class SandboxEngine {
public:
    static constexpr uint32_t WIDTH = 1440;
    static constexpr uint32_t HEIGHT = 810;

    SandboxEngine();
    ~SandboxEngine() = default;

    
    // initialize subsystems
    void initialize();

    // Prepare the game layer (calls onInit)
    void initLayer(IGameLayer* game);

    // Main loop
    void run(std::unique_ptr<IGameLayer> game);
private:
    SandboxWindow                       m_window{ WIDTH, HEIGHT, "A vulkan place" };
    VkSandboxInstance                   m_vkinstance{};
    VkSandboxDevice                     m_device{ m_vkinstance, m_window };
    VkSandboxRenderer                   m_renderer{ m_device, m_window };
    AssetManager                        m_assetManager{m_device}; 

    VkSurfaceKHR                        m_surface = VK_NULL_HANDLE;
    VkInstance                          m_vkinstance_handle= VK_NULL_HANDLE;

    std::unique_ptr<IWindowInput>       m_windowInput;

public:
    // Getters
    IWindowInput* getInputInterface() const { return m_windowInput.get(); }
    AssetManager& getAssetManager() { return m_assetManager; }
    ISandboxRenderer& renderer();



};
