#pragma once


#include "apex/platform/app_consumer.h"
#include "core/user/userex/pane_tab_impact.h"


namespace SceneFoundry_gpu_sandbox
{


   class CLASS_DECL_SCENEFOUNDRY_GPU_SANDBOX pane_impact :
      virtual public ::app_consumer < application, ::userex::pane_tab_impact, ::user::form_callback >
   {
   public:


      ::user::split_impact *                          m_ptopviewLast;
      //::app_core_hello_multiverse::impact_base *      m_pimpactLastBase;
      //::app_core_hello_multiverse::impact *           m_pimpactLastImpact;
      ::user::impact_data *                           m_pimpactdataTopic;
      string                                          m_strTopicTitle;


      ::user::plain_edit *                            m_prollfps;
      address_array_base < ::user::check_box * >      m_checkptraBilbo;


      pane_impact();
      ~pane_impact() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      // void assert_ok() const override;

      // void dump(dump_context & dumpgpucontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
      void on_change_cur_sel() override;

      //virtual string prepare_menu_impact();

      ///void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual string get_impact_options_main_body();
      virtual string get_bilbo_html();


      //void create_options_body(::user::interaction * pparent);


   };


} // namespace SceneFoundry_gpu_sandbox



