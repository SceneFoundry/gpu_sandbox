// vertex.vert
#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projection;
    mat4 view;
} ubo;

layout(push_constant) uniform PushConstants {
    mat4 model;
} push;

void main() {
    // Transform to clip‑space
    gl_Position = ubo.projection * ubo.view * push.model * vec4(inPosition, 1.0);
    // Pass color straight through
    fragColor = inColor;
}