// vertex.vert
#version 450
layout(location = 0) in vec3 inPosition;

layout(location = 0) out vec3 fragColor;

layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projection;
    mat4 view;
} ubo;

layout(push_constant) uniform PushConstants {
    mat4 model;
} push;

void main() {
    gl_Position = ubo.projection * ubo.view * push.model * vec4(inPosition, 1.0);
    fragColor = vec3(0.0, 1.0, 0.5);  // 🔴 Hardcoded red
}