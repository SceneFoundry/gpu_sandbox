#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 fragPosWorld;
layout(location = 2) out vec3 fragNormalWorld;

struct PointLight {
    vec4 position;
    vec4 color;
};

layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projection;
    mat4 view;
    vec4 ambientLightColor; // w is intensity
    PointLight pointLights[10];
    vec4 viewPos;  // camera position in world space
    int numLights;
} ubo;

layout(push_constant) uniform PushConstants {
    mat4 model;
    mat4 normalMatrix;
} push;

void main() {
    vec4 worldPosition = push.model * vec4(position, 1.0);
    gl_Position = ubo.projection * ubo.view * worldPosition;

    fragNormalWorld = normalize(mat3(push.normalMatrix) * normal);
    fragPosWorld = worldPosition.xyz;
    fragColor = color;
}
