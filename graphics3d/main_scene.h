// From continuum (V0idsEmbrace@Twitch)
// by camilo on 2025-05-07 02:18 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/graphics3d/cube_map.h"
#include "bred/graphics3d/scene.h"


namespace SceneFoundry_gpu_sandbox
{


   class main_scene :
      virtual public ::app_consumer < application, ::graphics3d::scene >
   {
   public:


      //::pointer< ::graphics3d::sky_box> m_Skybox;


      ::pointer < simple_render_system >		m_psimplerendersystem;
      ::pointer < point_light_system >			m_ppointlightsystem;

      string_map < ::pointer < ::graphics3d::sky_box > > m_mapSkybox;

      main_scene();
      ~main_scene() override;

      
      void on_initialize_scene() override;

      virtual ::graphics3d::sky_box * get_skybox();

      ::pointer < ::graphics3d::camera > get_default_camera() override;


      void on_load_scene(::gpu::context* pgpucontext) override;


      void on_update_global_ubo(::gpu::context* pgpucontext) override;
      void on_render(::gpu::context * pgpucontext) override;


   };


} // namespace SceneFoundry_gpu_sandbox



