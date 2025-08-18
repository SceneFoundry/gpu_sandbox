#pragma once


#include "berg/user/user/document.h"


namespace SceneFoundry_gpu_sandbox
{


   class CLASS_DECL_SCENEFOUNDRY_GPU_SANDBOX document :
      public ::user::document
   {
   public:
      
      
      string_array   m_straLine;


      document();
	   ~document() override;


	   // void assert_ok() const override;
	   // void dump(dump_context & dumpgpucontext) const override;

      bool on_new_document() override;
      virtual bool on_open_document(const ::payload & payloadFile) override;

#ifdef _DEBUG
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;
#endif

      //virtual ::stream& write(::stream& stream) const override;


   };


} // namespace SceneFoundry_gpu_sandbox



