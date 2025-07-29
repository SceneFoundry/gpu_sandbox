#version 450

layout (location = 0) in vec3 fragColor;
layout (location = 1) in vec3 fragPosWorld;
layout (location = 2) in vec3 fragNormalWorld;

layout (location = 0) out vec4 outColor;

struct PointLight {
    vec4 position;  // xyz = world-space position, w = unused
    vec4 color;     // xyz = RGB, w = intensity
};

layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projection;
    mat4 view;
    vec4 ambientLightColor;  // w = ambient intensity
    vec4 viewPos;            // xyz = camera pos
    PointLight pointLights[10];
    int numLights;
} ubo;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
} push;

void main(){
    vec3 N = normalize(fragNormalWorld);
    vec3 V = normalize(ubo.viewPos.xyz - fragPosWorld);

    vec3 lighting = ubo.ambientLightColor.rgb * ubo.ambientLightColor.w;
    for(int i=0;i<ubo.numLights;++i){
        PointLight Ld = ubo.pointLights[i];
        vec3 L = Ld.position.xyz - fragPosWorld;
        float d2 = dot(L,L);
        float att = 1.0/(d2 + 1.0);
        vec3  Di = normalize(L);
        float Nl = max(dot(N,Di),0.0);
        vec3 rad = Ld.color.xyz * Ld.color.w;
        lighting += rad * Nl * att;
        vec3 H = normalize(Di + V);
        float Nh = max(dot(N,H),0.0);
        lighting += rad * pow(Nh,64.0) * att;
    }
    outColor = vec4(lighting * fragColor, 1.0);
}