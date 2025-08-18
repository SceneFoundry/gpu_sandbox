#pragma once
#include <memory>
#include "window.h"
#include "vulkan_wrapper/vulkan_device.h"
#include "vulkan_wrapper/vulkan_instance.h"
#include "vulkan_wrapper/vulkan_renderer.h"
#include "interfaces/game_layer_i.h"
#include "interfaces/camera_i.h"
#include "interfaces/window_input_i.h"
#include "common/glfw_input.h"
#include "asset_manager.h"



class SandboxEngine {
public:
    static constexpr uint32_t WIDTH = 1440;
    static constexpr uint32_t HEIGHT = 810;

    SandboxEngine();
    ~SandboxEngine() = default;

    void initialize();

    void initLayer(IGameLayer* game);

    void run(::pointer<IGameLayer> game);
private:
    SandboxWindow                       m_window{ WIDTH, HEIGHT, "A vulkan place" };
    sandbox_instance                   m_vkinstance{};
    VkSandboxDevice                     m_device{ m_vkinstance, m_window };
    AssetManager                        m_assetManager{ m_device };
    sandbox_renderer                   m_renderer{ m_device, m_window };
 
    VkSurfaceKHR                        m_surface = VK_NULL_HANDLE;
    VkInstance                          m_vkinstance_handle= VK_NULL_HANDLE;

    std::shared_ptr<IWindowInput>       m_windowInput;

public:
    std::shared_ptr<IWindowInput> getInputSharedPtr() {
        return m_windowInput;
    }
    AssetManager& getAssetManager() { return m_assetManager; }

    ISandboxRenderer& renderer();
    void toggleCursorLock();
    void setupInputCallbacks();
    void processInput();

    bool m_cursorLocked = true;


};
