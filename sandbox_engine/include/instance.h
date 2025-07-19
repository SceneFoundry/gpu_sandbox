#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class SandboxInstance {
public:
    SandboxInstance();               // constructs + vkCreateInstance + debug messenger
    ~SandboxInstance();              // destroys messenger + instance

    VkInstance instance() const { return m_instance; }

private:
    // validation layers we want
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    // whether to enable them (compile‑time)
#ifdef NDEBUG
    static constexpr bool enableValidationLayers = false;
#else
    static constexpr bool enableValidationLayers = true;
#endif

    VkInstance               m_instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;

    // setup / teardown
    void createInstance();
    void setupDebugMessenger();
    void destroyDebugMessenger();

    // helpers
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& ci);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT  severity,
        VkDebugUtilsMessageTypeFlagsEXT         type,
        const VkDebugUtilsMessengerCallbackDataEXT* data,
        void* userData);

    // loader wrappers
    VkResult CreateDebugUtilsMessengerEXT(
        const VkDebugUtilsMessengerCreateInfoEXT* ci,
        VkDebugUtilsMessengerEXT* messenger);
    void DestroyDebugUtilsMessengerEXT(VkDebugUtilsMessengerEXT messenger);
};