#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(set = 2, binding = 0) uniform sampler2D materialSampler;
layout(set = 2, binding = 1) uniform sampler2D normalSampler;

layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec3 inViewVec;
layout(location = 4) in vec3 inLightVec;
layout(location = 5) in vec4 inTangent;
layout(location = 6) in vec4 inLightColor;

layout(location = 0) out vec4 outFragColor;

layout(constant_id = 0) const bool  ALPHA_MASK = false;
layout(constant_id = 1) const float ALPHA_MASK_CUTOFF = 0.0;

void main()
{
    vec4 texColor = texture(materialSampler, inUV) * inColor;

    if (ALPHA_MASK && texColor.a < ALPHA_MASK_CUTOFF) {
        discard;
    }

    vec3 N = normalize(inNormal);
    vec3 T = normalize(inTangent.xyz);
    vec3 B = cross(N, T) * inTangent.w;
    mat3 TBN = mat3(T, B, N);
    vec3 sampledNormal = texture(normalSampler, inUV).xyz * 2.0 - 1.0;
    N = normalize(TBN * sampledNormal);

    vec3 L = normalize(inLightVec);
    vec3 V = normalize(inViewVec);
    vec3 R = reflect(-L, N);

    vec3 lightCol = inLightColor.rgb * inLightColor.a;

    float NdotL = max(dot(N, L), 0.0);
    float RdotV = pow(max(dot(R, V), 0.0), 32.0);

    vec3 ambient  = 0.05 * texColor.rgb;
    vec3 diffuse  = texColor.rgb * NdotL * lightCol;
    vec3 specular = RdotV * lightCol;

    vec3 result = ambient + diffuse + specular;
    outFragColor = vec4(result, texColor.a);
}