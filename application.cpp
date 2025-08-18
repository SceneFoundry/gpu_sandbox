#include "framework.h"
#include "application.h"
#include "main_frame.h"
#include "document.h"
#include "impact.h"
#include "pane_impact.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_system_options.h"
#include "aura/graphics/write_text/font.h"
#include "acme/handler/request.h"
#include "aura/user/user/plain_edit.h"
#include "aura/user/user/still.h"
#include "apex/database/stream.h"
#include "berg/user/user/tab_impact.h"
#include "berg/platform/session.h"
#include "berg/user/user/document_manager.h"
#include "berg/user/user/user.h"
#include "berg/user/user/single_document_template.h"


__IMPLEMENT_APPLICATION_RELEASE_TIME(SceneFoundry_gpu_sandbox);
IMPLEMENT_APPLICATION_FACTORY(SceneFoundry_gpu_sandbox);


namespace SceneFoundry_gpu_sandbox
{


   application::application()
   {

      m_pmainscene = nullptr;
      m_bAbsoluteMousePosition = false;
      m_ppaneimpact = nullptr;
      m_bGpu = true;
      //m_bImaging = false;
      //preempt(15_s);
      //m_bImaging = true; // for showing application icon
      
      //m_bImaging = false; // showing application icon may use innate_ui icon?

      //m_bNetworking = false;

      //m_ppaneimpact = nullptr;

      m_strAppId = "app-graphics3d/continuum";

      m_strAppName = "app-graphics3d/continuum";

      m_strBaseSupportId = "SceneFoundry_gpu_sandbox";

      m_bLicense = false;
      
      m_pfilesystemoptions->m_b_iCloudContainer = true;
      m_pfilesystemoptions->m_str_iCloudContainerIdentifier = "iCloud.app-simple";


   }


   application::~application()
   {

   }


   void application::init_instance()
   {


      factory()->add_factory_item <::SceneFoundry_gpu_sandbox::document >();
      factory()->add_factory_item <::SceneFoundry_gpu_sandbox::main_frame >();
      factory()->add_factory_item <::SceneFoundry_gpu_sandbox::impact >();
      factory()->add_factory_item <::SceneFoundry_gpu_sandbox::pane_impact >();

      ::core::application::init_instance();

      add_impact_system(
         "main", __initialize_new ::user::single_document_template(
         "main",
         ::type < document >(),
         ::type < main_frame >(),
         ::type < pane_impact >()));
      
      add_impact_system(
         "impact", __initialize_new::user::single_document_template(
            "impact",
            ::type < document >(),
            ::type < main_frame >(),
            ::type < impact >()));

#if defined(APPLE_IOS)

      m_pathApplicationText = "icloud://iCloud.app-simple/Documents/application/application.txt";
      
#else
      
      m_pathApplicationText = "dropbox-app://application.txt";
      
#endif

      datastream()->get("skybox", m_strSkybox);

      m_straSkybox.add("rosendal");
      m_straSkybox.add("SpaceSkybox");

      if (!m_straSkybox.contains(m_strSkybox))
      {

         m_strSkybox = m_straSkybox.first();

      }

   }


   void application::term_application()
   {

      ::berg::application::term_application();

   }




   void application::on_request(::request * prequest)
   {

      if (impact_system("main")->get_document_count() == 0)
      {

         if(prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
         {

            information() << "::graphics::e_output_purpose_screen";

         }
         else
         {

            information() << "NOT ::graphics::e_output_purpose_screen";

         }

         prequest->m_egraphicsoutputpurpose = ::graphics::e_output_purpose_screen_fps;

         impact_system("main")->request(prequest);

      }

      //if (is_true("wfi_maximize"))
      //{

      //   prequest->payload("document").cast < document >()->get_typed_impact < ::user::tab_impact >()->top_level_frame()->design_window_maximize();

      //}

      informationf("finished simple_application::on_request");

   }


   string application::preferred_experience()
   {

      return ::aura::application::preferred_experience();

   }


#ifdef _DEBUG


   long long application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   long long application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


#endif


   void application::create_options_body(::user::interaction* pparent)
   {

      auto pstillTitle = create_label<::user::still>(pparent, "graphics3d continuum Options");

      ødefer_construct(pstillTitle->m_pfont);

      pstillTitle->m_pfont->create_font(e_font_sans_ui, 24_pt);

      auto playoutLine = create_line_layout(pparent, e_orientation_horizontal);

      playoutLine->m_atomMatterId = "::user::line_layout(1)";

      {

         auto pcheckbox = create_check_box<::user::check_box>(playoutLine, "");

         bool bAbsoluteMousePosition = false;

         if (datastream()->get("Absolute Mouse Position", bAbsoluteMousePosition))
         {

            pcheckbox->set_check(bAbsoluteMousePosition, ::e_source_initialize);

         }

         m_bAbsoluteMousePosition = bAbsoluteMousePosition;

         pcheckbox->check_changed(this) += [this](auto& check)
            {

               auto bAbsoluteMousePosition = check.payload().as_bool();

               datastream()->set("Absolute Mouse Position", bAbsoluteMousePosition);


            bAbsoluteMousePosition = false;
            datastream()->get("Absolute Mouse Position", bAbsoluteMousePosition);

            m_bAbsoluteMousePosition = bAbsoluteMousePosition;

               //on_change_synchronize_with_weather();

            };

         create_label<::user::still>(playoutLine, "Absolute Mouse Position");

      }


      for(int i = 0; i < m_straSkybox.size(); i++)
      {

         auto playoutSkyboxCheckbox = create_line_layout(pparent, e_orientation_horizontal);

         ::string strId;

         strId.formatf("(2)(%d)", i);

         playoutSkyboxCheckbox->m_atomMatterId = "::user::line_layout" + strId;

         auto pcheckbox = create_check_box<::user::check_box>(playoutSkyboxCheckbox, "");

         create_label<::user::still>(playoutSkyboxCheckbox, m_straSkybox[i]);

         m_checkboxaSkyBox.add(pcheckbox);

         pcheckbox->check_changed(this) += [this, i](::data::check_change& change)
            {

               if (!change.action_context().is_user_source())
               {

                  return;

               }

               auto bChecked = change.payload().as_bool();

               if (bChecked)
               {

                  for (int j = 0; j < m_straSkybox.size(); j++)
                  {

                     if (j != i)
                     {

                        m_checkboxaSkyBox[j]->set_check(e_check_unchecked, ::e_source_sync);

                     }

                  }

               }
               else
               {

                  m_checkboxaSkyBox[i]->set_check(e_check_checked, ::e_source_sync);

               }

               ::string strSkybox = m_straSkybox[i];

               datastream()->set("skybox", strSkybox);

               m_strSkybox = strSkybox;


            };

      }




      //{

      //   auto pcomponent = system()->component("wallpaper_transform");

      //   pcomponent->_001CreateForm(playoutLine);

      //}

      //m_pyeetask->m_pyee->create_yee_options_impact(pparent);

      //create_label<::user::still>(pparent, "yee color");

      //m_peditYeeColor = create_edit<::user::plain_edit>(pparent);

      //m_peditYeeColor->set_size({ 300, 25 });

      //m_peditYeeColor->add_handler(this);

      //::string strYeeColor;

      //datastream()->get("yee_color", strYeeColor);

      //m_peditYeeColor->set_text(strYeeColor, ::e_source_initialize);

      //auto pstill = øallocate ::user::still();

      //øconstruct_new(m_pedit);

      //øconstruct_new(m_pbuttonClear);

      //øconstruct_new(m_pbuttonSend);

      //øconstruct_new(m_pstillReceiver);

      //m_pstill->create_control(this, "still");

      //m_pedit->create_control(this, "edit");

      //m_pedit->add_handler(this);

      //m_pbuttonClear->create_control(this, "clear_button");

      //m_pbuttonClear->add_handler(this);

      //m_pbuttonSend->create_control(this, "send_button");

      //m_pbuttonSend->add_handler(this);

      //m_pstill->set_window_text("Enter ___new text:");

      //m_pstillReceiver->create_control(this, "still");

      //m_pstillReceiver->set_window_text("(Waiting to receive...)");

      //m_pedit->m_strEmtpyText = "Enter New Text Here";

      //string strInitialText;

      //auto papp = get_app();

      //papp->datastream()->get("last_text", strInitialText);

      //m_pedit->set_text(strInitialText, ::e_source_initialize);

      //m_pbuttonClear->set_window_text("Clear");

      //m_pbuttonSend->set_window_text("Send");

   }


   bool application::is_absolute_mouse_position()
   {

      return m_bAbsoluteMousePosition;

   }


   //::string application::graphics3d_get_implementation_name()
   //{

   //   return m_strImplementation;
   //}


} // namespace SceneFoundry_gpu_sandbox



