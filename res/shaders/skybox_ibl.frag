#version 450 core

layout(set = 1, binding = 0) uniform samplerCube skybox;


layout(location = 0) in vec3 vDirection;
layout(location = 0) out vec4 outColor;

void main() {
      outColor = texture(skybox, normalize(vDirection));
}
