#include "framework.h"
#include "application.h"
#include "impact.h"
#include "bred/gpu/bred_approach.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/shader.h"
#include "bred/graphics3d/camera.h"
#include "bred/graphics3d/model.h"
#include "bred/graphics3d/scene.h"
#include "bred/user/user/graphics3d.h"
#include "app-graphics3d/continuum/global_ubo.h"
#include "point_light_system.h"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <cassert>
#include <map>
#include <stdexcept>


namespace SceneFoundry_gpu_sandbox
{


   //struct PointLightPushConstants {
   //   glm::vec4 position{};
   //   glm::vec4 color{};
   //   float radius;
   //};


   point_light_system::point_light_system()
   {


   }


   void point_light_system::initialize_point_light_system(::graphics3d::engine * pengine)
      //context* pvkcdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout)
      //: m_pgpucontext{ pvkcdevice }
   {

      m_pengine = pengine;
      //createPipelineLayout(globalSetLayout);
      //createPipeline(renderPass);

      ødefer_construct(m_pmodelDummy);

      // ::graphics3d::model::Builder builderDummy;

      m_pmodelDummy.initialize_dummy_model(
         pengine->m_pgpucontextCompositor2->m_pgpurenderer,
         6);

   }


   point_light_system::~point_light_system()
   {

      //vkDestroyPipelineLayout(m_pgpucontext->logicalDevice(), pipelineLayout, nullptr);

   }



   void point_light_system::on_prepare(::gpu::context * pgpucontext)//(VkDescriptorSetLayout globalSetLayout) 
   {

      auto prenderer = pgpucontext->m_pgpurenderer;

      m_pshader = prenderer->create_shader(
         "matter://shaders/point_light.vert",
         "matter://shaders/point_light.frag",
         {::gpu::shader::e_descriptor_set_slot_global,
         ::gpu::shader::e_descriptor_set_slot_local},
         nullptr,
         ::gpu_properties<point_light2>(),
         pgpucontext->input_layout<::graphics3d::Vertex>(),
         ::gpu::shader::e_flag_clear_default_bindings_and_attributes_descriptions
      );
      

      //VkPushConstantRange pushConstantRange{};
      //pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
      //pushConstantRange.offset = 0;
      //pushConstantRange.size = sizeof(PointLightPushConstants);

      //std::vector<VkDescriptorSetLayout> descriptorSetLayouts{ globalSetLayout };

      //VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
      //pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
      //pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
      //pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
      //pipelineLayoutInfo.pushConstantRangeCount = 1;
      //pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
      ////pipelineLayoutInfo.pPushConstantRanges = nullptr;
      //if (vkCreatePipelineLayout(m_pgpucontext->logicalDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
      //   VK_SUCCESS) {
      //   throw ::exception(error_failed, "failed to create pipeline layout!");
      //}
   }

   //void point_light_system::createPipeline(VkRenderPass renderPass) {
   //   assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

   //   PipelineConfigInfo pipelineConfig{};
   //   pipeline::defaultPipelineConfigInfo(pipelineConfig);
   //   pipelineConfig.attributeDescriptions.clear();
   //   pipelineConfig.bindingDescriptions.clear();
   //   pipelineConfig.renderPass = renderPass;
   //   pipelineConfig.pipelineLayout = pipelineLayout;

   //   // Construct paths using PROJECT_ROOT_DIR
   //   std::string vertShaderPath = "matter://Shaders/SpirV/point_light.vert.spv";
   //   std::string fragShaderPath = "matter://Shaders/SpirV/point_light.frag.spv";

   //   m_ppipeline = øallocate pipeline();

   //   m_ppipeline->initialize_pipeline(
   //      m_pgpucontext,
   //      vertShaderPath.c_str(),
   //      fragShaderPath.c_str(),
   //      pipelineConfig
   //   );
   //}


   void point_light_system::on_render(::gpu::context * pgpucontext, ::graphics3d::scene* pscene)
   {
      // sort lights
      std::map<float, ::collection::index> sorted;
      for (auto& kv : pscene->m_mapObjects) {
         auto& obj = kv.element2();

         ::cast < ::graphics3d::point_light > ppointlight = obj;
         if (ppointlight == nullptr) continue;

         // calculate distance
         auto offset = m_pengine->m_pcamera->GetPosition() - obj->m_transform.translation;
         float disSquared = glm::dot(offset, offset);
         sorted[disSquared] = obj->m_iId;
      }

      m_pshader->bind();

      //auto properties = point_light_properties();

      // iterate through sorted lights in reverse order
      for (auto it = sorted.rbegin(); it != sorted.rend(); ++it) {
         // use game obj id to find light object
         auto& obj = pscene->m_mapObjects[it->second];
         ::cast < ::graphics3d::point_light > ppointlight = obj;
         //PointLightPushConstants push{};
         m_pshader->set_vec4("position", glm::vec4(obj->m_transform.translation, 1.f));
         m_pshader->set_vec4("color", glm::vec4(obj->m_color, ppointlight->m_pointlightcomponent.lightIntensity));
         m_pshader->set_float("radius", obj->m_transform.scale.x);

         m_pshader->push_properties();

         auto pcommandbuffer = pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

         m_pmodelDummy->bind(pcommandbuffer);

         m_pmodelDummy->draw(pcommandbuffer);

         m_pmodelDummy->unbind(pcommandbuffer);


         //auto pcommandbuffer = pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

         ////vkCmdPushConstants(
         ////   frameInfo.commandBuffer,
         ////   pipelineLayout,
         ////   VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
         ////   0,
         ////   sizeof(PointLightPushConstants),
         ////   &push);
         ////vkCmdDraw(frameInfo.commandBuffer, 6, 1, 0, 0);

         //pcommandbuffer->draw(6);

         //m_pshader->draw();

      }

      m_pshader->unbind();

   }


   void point_light_system::on_update(::gpu::context * pcontext, ::graphics3d::scene* pscene)
   {

      auto dt = m_pengine->dt();

      auto& globalubo = pscene->global_ubo();

      auto rotateLight = glm::rotate(glm::mat4(1.f), 0.5f * dt, { 0.f, -1.f, 0.f });

      int lightIndex = 0;

      for (auto& kv : pscene->m_mapObjects)
      {

         auto& obj = kv.element2();

         ::cast < ::graphics3d::point_light > ppointlight = obj;

         if (ppointlight == nullptr) continue;

         assert(lightIndex < MAX_LIGHTS && "Point lights exceed maximum specified");

         // update light position
         ppointlight->m_transform.translation =
            glm::vec3(rotateLight * glm::vec4(ppointlight->m_transform.translation, 1.f));

         // copy light to ubo
         globalubo["pointLights"][lightIndex]["position"] =
            glm::vec4(ppointlight->m_transform.translation, 1.f);
         globalubo["pointLights"][lightIndex]["color"] =
            glm::vec4(obj->m_color, ppointlight->m_pointlightcomponent.lightIntensity);

         lightIndex += 1;

      }

      globalubo["numLights"] = lightIndex;

   }


} // namespace SceneFoundry_gpu_sandbox


