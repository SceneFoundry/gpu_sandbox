#pragma once


#include "berg/user/simple/frame_window.h"


namespace SceneFoundry_gpu_sandbox
{


   class CLASS_DECL_SCENEFOUNDRY_GPU_SANDBOX main_frame :
      virtual public ::simple_frame_window
   {
   public:


      bool                       m_bExplicitTranslucency;


      main_frame();
      ~main_frame() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpgpucontext) const override;


      ::pointer < ::experience::frame > frame_experience() override;


      //bool has_pending_graphical_update() override;


      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);


   };


} // namespace SceneFoundry_gpu_sandbox



