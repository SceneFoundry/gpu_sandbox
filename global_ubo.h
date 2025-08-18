#pragma once


#include "bred/user/user/graphics3d.h"


namespace SceneFoundry_gpu_sandbox
{


#define MAX_LIGHTS 10


   //struct PointLight
   //   glm::vec4 position{};  // ignore w
   // glm::vec4 color{};     // w is intensity

//BEGIN_GPU_PROPERTIES(point_light)
//GPU_PROPERTY("position", ::gpu::e_type_seq4)
//GPU_PROPERTY("color", ::gpu::e_type_seq4)
//END_GPU_PROPERTIES()

//GPU_PROPERTY("radius", ::gpu::e_type_float)

   // GlobalUbo :
   // glm::mat4 projection{ 1.f };
   // glm::mat4 view{ 1.f };
   // glm::mat4 invView{ 1.f };
   // glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, .02f };
   // PointLight pointLights[MAX_LIGHTS];
   // int numLights;
   // 3XINT PADDING


} // namespace SceneFoundry_gpu_sandbox


