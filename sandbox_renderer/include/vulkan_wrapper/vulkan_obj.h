#pragma once
#include "vulkan_wrapper/vulkan_device.h"
#include "interfaces/model_i.h"
#include "vulkan_buffer.h"
#include "interfaces/renderer_i.h"

// libs
#define GLM_FORCE_RADIANS	
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <memory>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <cstring>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

class sandbox_object_model : public IModel {
public:
    struct Vertex {
        glm::vec3 position{};
        glm::vec3 color{};
        glm::vec3 normal{};
        glm::vec2 uv{};

        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

        bool operator==(Vertex const& o) const {
            return position == o.position &&
                normal == o.normal &&
                uv == o.uv;
        }
    };

    struct SkyboxVertex {
        glm::vec3 position;
        static std::vector<VkVertexInputBindingDescription>   getBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
    };
    struct PrimitiveInfo {
        uint32_t      firstIndex;
        uint32_t      indexCount;
        int           textureIndex; // index into textures[]
        glm::mat4     modelMatrix;
    };
    struct Builder {
        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};

        void loadModel(const std::string& filepath, bool isSkybox);


        bool isSkybox{ false };

    };

    static std::shared_ptr<sandbox_object_model> createModelFromFile(
        VkSandboxDevice& device, std::string const& filepath, bool isSkybox = false);

    sandbox_object_model(VkSandboxDevice& device, Builder const& builder);
    ~sandbox_object_model();

    sandbox_object_model(sandbox_object_model const&) = delete;
    void operator=(sandbox_object_model const&) = delete;

    void bind(VkCommandBuffer cmd)override;
    void draw(VkCommandBuffer cmd)override;




    bool isSkybox() const { return m_bIsSkyboxModel; }
private:
    void createVertexBuffers(std::vector<Vertex> const& vertices);
    void createIndexBuffers(std::vector<uint32_t> const& indices);

    VkSandboxDevice& m_device;
    bool m_bHasIndexBuffer{ false };
    bool m_bIsSkyboxModel{ false };

    std::unique_ptr<sandbox_buffer> m_vertexBuffer;
    uint32_t m_vertexCount;

    std::unique_ptr<sandbox_buffer> m_indexBuffer;
    uint32_t m_indexCount;


};