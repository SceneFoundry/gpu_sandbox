#pragma once


#include "core/_.h"



#if defined(_SceneFoundry_gpu_sandbox_project)
#define CLASS_DECL_SCENEFOUNDRY_GPU_SANDBOX  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_SCENEFOUNDRY_GPU_SANDBOX  CLASS_DECL_IMPORT
#endif


namespace SceneFoundry_gpu_sandbox
{

   class application;
   class pane_impact;
   class document;
   class impact;


   class main_scene;
   class simple_render_system;
   class point_light_system;


   class GlobalUbo;


} // namespace flag






