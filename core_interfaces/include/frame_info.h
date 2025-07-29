#pragma once
// frame_info.h
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include "interfaces/camera_i.h"
#include "interfaces/scene_i.h"
#include "interfaces/game_object_i.h"

#define MAX_LIGHTS 10
struct IGameObject;
struct IScene;

struct PointLight {
    glm::vec4 position{};
    glm::vec4 color{};
};

struct GlobalUbo {
    glm::mat4 projection{ 1.f };               // 64 bytes
    glm::mat4 view{ 1.f };                     // 64 bytes
    glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, 0.02f }; // 16 bytes
    glm::vec4 lightDirection;                  // 16 bytes, if unused, consider removing
    glm::vec4 viewPos;                         // 16 bytes
    PointLight pointLights[MAX_LIGHTS];       // 10 * 32 bytes = 320 bytes
    alignas(16) int numLights = 0;             // 4 bytes

    // Padding for alignment — keep these to align struct to multiples of 16 bytes
    alignas(16) int _pad1 = 0;                 // 4 bytes
    alignas(16) int _pad2 = 0;                 // 4 bytes
    alignas(16) int _pad3 = 0;                 // 4 bytes
};

struct FrameInfo {
    int frameIndex;
    float frameTime;
    VkCommandBuffer commandBuffer;
    const ICamera& camera;
    VkDescriptorSet globalDescriptorSet;
    std::unordered_map<unsigned int, std::shared_ptr<IGameObject>>& gameObjects;
    IScene& scene;
};
//IScene* scene;
