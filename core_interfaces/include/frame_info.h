#pragma once
// frame_info.h
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include "interfaces/camera_i.h"
#include "interfaces/scene_i.h"
#include "interfaces/game_object_i.h"


struct IGameObject;
struct IScene;

struct PointLight {
    glm::vec4 position{};
    glm::vec4 color{};
};

struct GlobalUbo {
    glm::mat4 projection{ 1.f };
    glm::mat4 view{ 1.f };
    glm::mat4 inverseView{ 1.f };
    glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, 0.02f };
    glm::vec4 lightDirection;
    glm::vec4 viewPos;
    PointLight pointLights[10];
    int numLights = 0;
    int _pad0 = 0, _pad1 = 0, _pad2 = 0;
};

//struct FrameInfo {
//    int frameIndex;
//    float frameTime;
//    VkCommandBuffer commandBuffer;
//    const ICamera& camera;
//    VkDescriptorSet globalDescriptorSet;
//    VkDescriptorSet textureDescriptorSet;
//    VkDescriptorSet skyboxDescriptorSet;
//    std::unordered_map<uint32_t, std::unique_ptr<IGameObject>>& gameObjects;
//    IScene* scene;
//};

struct FrameInfo {
    int frameIndex;
    float frameTime;
    VkCommandBuffer commandBuffer;
    //const ICamera& camera;
    VkDescriptorSet globalDescriptorSet;
    std::unordered_map<unsigned int, std::shared_ptr<IGameObject>>& gameObjects;
    //IScene& scene;
};
