#pragma once



#include "bred/gpu/properties.h"
#include "bred/graphics3d/scene_system.h"
#include <glm/glm.hpp>


namespace SceneFoundry_gpu_sandbox
{


   struct point_light2
   {

      ::glm::vec4 position;
      ::glm::vec4 color;
      float radius;

   };


   class point_light_system :
      virtual public ::graphics3d::scene_system
   {
   public:


      ::pointer < ::graphics3d::engine >     m_pengine;

      ::pointer < ::gpu::shader >            m_pshader;
      //::pointer < ::graphics3d::engine >        m_pengine;
      ::graphics3d::model<::graphics3d::Vertex> m_pmodelDummy;

      point_light_system();
      ~point_light_system();

      
      void initialize_point_light_system(::graphics3d::engine * pengine);


      void on_update(::gpu::context* pgpucontext, ::graphics3d::scene * pscene) override;
      void on_render(::gpu::context* pgpucontext, ::graphics3d::scene * pscene) override;
      

      //void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
      //void createPipeline(VkRenderPass renderPass);

      void on_prepare(::gpu::context* pgpucontext) override;

      //VkPipelineLayout pipelineLayout;

   };


}  // namespace SceneFoundry_gpu_sandbox


BEGIN_GPU_PROPERTIES(::SceneFoundry_gpu_sandbox::point_light2)
GPU_PROPERTY("position", ::gpu::e_type_seq4)
GPU_PROPERTY("color", ::gpu::e_type_seq4)
GPU_PROPERTY("radius", ::gpu::e_type_float)
END_GPU_PROPERTIES()
