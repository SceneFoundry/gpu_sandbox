#include "framework.h"
#include "pane_impact.h"
#include "application.h"
#include "impact.h"
#include "document.h"
//#include "switcher_impact.h"
//#include "render.h"
//#include "slide_show.h"
//#include "hello_multiverse.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/handler/request.h"
#include "acme/handler/topic.h"
#include "aura/user/user/system.h"
#include "aura/user/user/plain_edit.h"
#include "aura/user/user/check_box.h"
#include "berg/user/user/single_document_template.h"
#include "berg/user/form/document.h"
#include "berg/user/user/tab_pane.h"
//#include "app-core/gcom/gcom/slide.h"
//#include "app-core/gcom/image_show.h"
//#include "app-core/yee/yee_task.h"


#ifdef _DEBUG
//#define DEBUG_GCOM 1
#define DEBUG_GCOM 0
#else
#define DEBUG_GCOM 0
#endif

namespace SceneFoundry_gpu_sandbox
{


   pane_impact::pane_impact()
   {

      //m_pimpactLastBase = nullptr;
      //m_pimpactLastImpact = nullptr;
      m_prollfps = nullptr;
      m_pimpactdataTopic = nullptr;

   }


   pane_impact::~pane_impact()
   {

   }



   void pane_impact::install_message_routing(::channel * pchannel)
   {

      ::userex::pane_tab_impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_impact::on_message_create);

   }


   void pane_impact::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      get_app()->m_ppaneimpact = this;

      set_tab("Options", APP_OPTIONS_IMPACT);
      //set_tab("gcom", GCOM_IMPACT);
      set_tab("hello_multiverse", MAIN_IMPACT);
      set_tab("switcher", MAIN_SWITCHER_IMPACT);
      set_tab("Font", FONTSEL_IMPACT);
      set_tab("Color", COLORSEL_IMPACT);
#if 1
      set_tab("Open", FILEMANAGER_IMPACT);
#endif

#if DEBUG_GCOM

      set_current_tab_by_id(GCOM_IMPACT);
      set_current_tab_by_id(MAIN_IMPACT);
      set_current_tab_by_id(MAIN_SWITCHER_IMPACT);

#else

      set_current_tab_by_id(MAIN_IMPACT);

#endif

   }


   void pane_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_impact::_001OnNcDraw(pgraphics);

   }


   void pane_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_impact::_001OnDraw(pgraphics);

   }


   void pane_impact::on_change_cur_sel()
   {

      ::userex::pane_tab_impact::on_change_cur_sel();
      string strId = get_impact_id();
      string_array stra;
      m_prollfps = nullptr;
      m_checkptraBilbo.erase_all();

      stra.explode("->:<-", strId);

      if (get_impact_id() == GCOM_IMPACT
         || get_impact_id() == MAIN_IMPACT
         || get_impact_id() == MAIN_SWITCHER_IMPACT
         || stra.contains(::as_string((int)GCOM_IMPACT))
         || stra.contains(::as_string((int)MAIN_IMPACT))
         || stra.contains(::as_string((int)MAIN_SWITCHER_IMPACT)))
      {

         auto ptabpaneFileManager = get_tab_by_id(FILEMANAGER_IMPACT);

         if (ptabpaneFileManager != nullptr && ptabpaneFileManager->m_pplaceholder != nullptr)
         {

            ptabpaneFileManager->m_pplaceholder->hide();

         }

         auto ptabpaneFontSel = get_tab_by_id(FONTSEL_IMPACT);

         if (ptabpaneFontSel != nullptr && ptabpaneFontSel->m_pplaceholder != nullptr)
         {

            ptabpaneFontSel->m_pplaceholder->hide();

         }

         auto ptabpaneColorSel = get_tab_by_id(COLORSEL_IMPACT);

         if (ptabpaneColorSel != nullptr && ptabpaneColorSel->m_pplaceholder != nullptr)
         {

            ptabpaneColorSel->m_pplaceholder->hide();

         }

         //if (m_pimpactdata->m_pplaceholder)
         //{

         //   m_pimpactdata->m_pplaceholder->get_typed_child(m_pimpactLastBase);

         //   m_pimpactdata->m_pplaceholder->get_typed_child(m_pimpactLastImpact);

         //}

         if (get_impact_id() == GCOM_IMPACT)
         {

            auto ptabpane = get_tab_by_id(GCOM_IMPACT);

            auto pchild = ptabpane->m_pplaceholder->get_child_by_id("hello_multiverse_gcom");

            //::pointer < impact_base >  pimpactbase = pchild;

            //m_pimpactLastBase = pimpactbase;
            //m_pimpactdataTopic = m_pimpactdata;
            //m_strTopicTitle = ptabpane->m_straTitle.implode(" ");

         }
         else if (get_impact_id() == MAIN_IMPACT)
         {

            auto ptabpaneMain = get_tab_by_id(MAIN_IMPACT);

            m_pimpactdataTopic = m_pimpactdata;

            m_strTopicTitle = ptabpaneMain->m_straTitle.implode(" ");

            //m_pimpactLastImpact = ptabpaneMain->m_pplaceholder->get_typed_child<::app_core_hello_multiverse::impact>();

         }
         else if (get_impact_id() == MAIN_SWITCHER_IMPACT)
         {

            auto ptabpaneMainSwitcher = get_tab_by_id(MAIN_SWITCHER_IMPACT);

            //m_pimpactLastBase->set_need_layout();
            m_pimpactdataTopic = m_pimpactdata;
            m_strTopicTitle = ptabpaneMainSwitcher->m_straTitle.implode(" ");

            //m_pimpactLastImpact = ptabpaneMainSwitcher->m_pplaceholder->get_typed_child<::app_core_hello_multiverse::impact>();

         }
         else if (stra.contains(::as_string((int)MAIN_IMPACT))
                  && stra.contains(::as_string((int)MAIN_SWITCHER_IMPACT)))
         {

      /*      if (m_pimpactLastBase)
            {

               m_pimpactLastBase->set_need_layout();

            }*/

         }

      }
      else if (get_impact_id() == FONTSEL_IMPACT)
      {

         auto pinteractionFont = get_font_interaction();

         //if (m_pimpactLastImpact != nullptr && ::is_set(pinteractionFont))
         //{

         //   pinteractionFont->set_sel_by_name(m_pimpactLastImpact->m_prender->m_phellomultiverse->m_strFont);

         //   pinteractionFont->ensure_sel_visible();

         //}

      }
      else if (get_impact_id() == COLORSEL_IMPACT)
      {

         auto pinteractionColor = get_color_interaction();

         //if (m_pimpactLastImpact != nullptr && ::is_set(pinteractionColor))
         //{

         //   pinteractionColor->set_sel_color(m_pimpactLastImpact->m_prender->m_phellomultiverse->get_foreground_hls());

         //}

      }

      if (m_pimpactdataOld != nullptr && m_pimpactdataOld->id() == FONTSEL_IMPACT)
      {

         auto pinteractionFont = get_font_interaction();

         //if (m_pimpactLastImpact != nullptr && ::is_set(pinteractionFont))
         //{

         //   string strHoverFont = m_pimpactLastImpact->m_prender->m_phellomultiverse->m_strFontHover;

         //   if (strHoverFont.has_character())
         //   {

         //      m_pimpactLastImpact->m_prender->m_phellomultiverse->m_strFontHover.empty();

         //      if (strHoverFont != m_pimpactLastImpact->m_prender->m_phellomultiverse->m_strFontSel)
         //      {

         //         m_pimpactLastImpact->set_need_layout();

         //      }

         //   }

         //}

      }

   }


   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch (pimpactdata->id().as_int())
      {
         //case GCOM_IMPACT:
         //{

         //   create_impact < gcom >(pimpactdata);

         //}

         //break;
      case MAIN_IMPACT:
      {

         auto prequest = m_pusersystem->m_prequest;

         auto & payloadFile = prequest->m_payloadFile;

         auto papp = get_app();

         information() << "pane_impact::on_create_impact MAIN_IMPACT";

         get_app()->impact_system("impact")->open_document_file(papp, payloadFile, true, pimpactdata->m_pplaceholder);

      }
      break;
      case MAIN_SWITCHER_IMPACT:
      {

         //create_impact < switcher_impact >(
         //   get_app()->impact_system("impact")->get_document(),
         //   pimpactdata->m_pplaceholder);

         //get_app()->impact_system("impact")->get_document()->id_update_all_impacts(id_update_render);

      }
      break;
      }

      ::userex::pane_tab_impact::on_create_impact(pimpactdata);

   }


   void pane_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

//      if (ptopic->user_interaction() && ptopic->user_interaction()->is_ascendant(m_pformdocumentMenu, true))
//      {
//
//         if (ptopic->id() == ::id_load_form_data)
//         {
//
//            ::user::impact * pimpact = m_pformdocumentMenu->get_impact(0);
//
//            string str;
//
//            auto puiRollFps = pimpact->get_child_by_id("roll_fps");
//
//            m_prollfps = dynamic_cast <::user::plain_edit *> (puiRollFps);
//
//            str = m_pimpactLastBase->get_document()->payload(m_pimpactLastBase->get_impact_prefix() + "fps_text");
//
//            if (m_prollfps != nullptr)
//            {
//
//               m_prollfps->set_text(str, ::e_source_database);
//
//               m_prollfps->add_handler(this);
//
//            }
//
//            if (m_pimpactLastBase->id() == "hello_multiverse_gcom")
//            {
//
//               string strCheck = "wallpaper.checkbox";
//
//               ::pointer<::user::interaction>pcheck = pimpact->get_child_by_id(strCheck);
//
//               if (pcheck)
//               {
//
//                  bool bEnableWallpaper = m_pimpactLastBase->get_document()->payload(
//                          m_pimpactLastBase->get_impact_prefix() + "wallpaper").get_bool();
//
//                  pcheck->set_check(bEnableWallpaper, ::e_source_sync);
//
//                  pcheck->add_handler(this);
//
//               }
//
//            }
//
//            if (m_pimpactLastImpact == m_pimpactLastBase)
//            {
//
//               if (!m_pimpactLastImpact->is_alternate())
//               {
//
////                  ::pointer<::user::plain_edit>pedit = pimpact->get_child_by_id("yee_address");
////
////                  if (pedit)
////                  {
////
////                     pedit->set_text(m_pimpactLastImpact->m_prender->m_strYeeNew, ::e_source_initialize);
////
////                     pedit->add_handler(this);
////
////                     pedit = pimpact->get_child_by_id("yee_brightness");
////
////                     pedit->set_text(m_pimpactLastImpact->m_prender->m_strYeeNewBrightness, ::e_source_initialize);
////
////                     pedit->add_handler(this);
////
////                  }
//
//               }
//
//               int iIndex = 1;
//
//               for (auto & pslide : m_pimpactLastImpact->m_prender->m_pslideshow->slideshow()->m_slidea)
//               {
//
//                  string strId;
//
//                  strId = "slide" + ::as_string(iIndex) + ".checkbox";
//
//                  ::pointer<::user::check_box>pcheck = pimpact->get_child_by_id(strId);
//
//                  if (pcheck)
//                  {
//
//                     pcheck->add_handler(this);
//
//                     m_checkptraBilbo.add(pcheck);
//
//                     m_checkptraBilbo.last()->set_check(pslide->m_bEnable ? ::e_check_checked : ::e_check_unchecked, ::e_source_sync);
//
//                     iIndex++;
//
//                  }
//
//               }
//
//            }
//
//            ptopic->m_bOk = true;
//
//            ptopic->m_bRet = true;
//
//            return;
//
//         }
//         else if (ptopic->id() == ::id_after_change_text)
//         {
//
//            if (ptopic->user_interaction()->id() == "yee_address" && ptopic->m_actioncontext.is_user_source())
//            {
//
//               ::pointer<::user::plain_edit>pedit = ptopic->user_interaction();
//
//               string strAddress;
//
//               pedit->get_text(strAddress);
//
//               m_pimpactLastImpact->m_prender->m_pyeetask->m_strYeeNew = strAddress;
//
//               m_pimpactLastImpact->get_document()->payload(m_pimpactLastImpact->get_impact_prefix() + "yee_address") = strAddress;
//
//               m_pimpactLastImpact->get_document()->save_document();
//
//               //               m_pimpactLastImpact->m_prender->start_yee();
//
//            }
//            if (ptopic->user_interaction()->id() == "yee_brightness" && ptopic->m_actioncontext.is(::e_source_user))
//            {
//
//               ::pointer<::user::plain_edit>pedit = ptopic->user_interaction();
//
//               string strBrightness;
//
//               pedit->get_text(strBrightness);
//
//               m_pimpactLastImpact->m_prender->m_pyeetask->m_strYeeNewBrightness = strBrightness;
//
//               m_pimpactLastImpact->get_document()->payload(m_pimpactLastImpact->get_impact_prefix() + "yee_brightness") = strBrightness;
//
//               m_pimpactLastImpact->get_document()->save_document();
//
//               //               m_pimpactLastImpact->m_prender->start_yee();
//
//            }
//            else if (m_prollfps != nullptr && ptopic->user_interaction()->id() == "roll_fps" && !ptopic->m_actioncontext.is(::e_source_initialize)
//                  && !ptopic->m_actioncontext.is(::e_source_database))
//            {
//
//               try
//               {
//
//                  string str;
//
//                  double d = m_prollfps->get_payload()["real"].as_double();
//
//                  if (m_pimpactLastBase != nullptr)
//                  {
//
//
//                     {
//
//                        string str;
//
//                        m_prollfps->get_text(str);
//
//                        m_pimpactLastBase->get_document()->payload(m_pimpactLastBase->get_impact_prefix() + "fps_text") = str;
//
//                        if (m_pimpactLastImpact)
//                        {
//
//                           m_pimpactLastImpact->get_document()->save_document();
//
//                        }
//
//                     }
//
//                     {
//
//                        ::payload v;
//
//                        v = d;
//
//                        m_pimpactLastBase->get_document()->payload(m_pimpactLastBase->get_impact_prefix() + "fps") = v;
//
//                        if (m_pimpactLastImpact)
//                        {
//
//                           m_pimpactLastImpact->get_document()->save_document();
//
//                        }
//
//                     }
//
//                     m_pimpactLastBase->m_frequencyFramesPerSecond = d;
//
//                     m_pimpactLastBase->m_timeRoll.Now();
//
//                  }
//                  //if(fabs(d) < 0.0000000001)
//                  //{
//                  //   m_prollspf->set_text("",::e_source_initialize);
//                  //}
//                  //else
//                  //{
//                  //   m_prollspf->set_text(as_string(1.0/d),::e_source_initialize);
//                  //}
//               }
//               catch (...)
//               {
//               }
//
//               ptopic->m_bRet = true;
//               return;
//
//
//            }
//            //else if(ptopic->user_interaction_id() == "roll_spf" && !ptopic->m_context.is_source(::e_source_initialize))
//            //{
//
//            //   try
//            //   {
//            //      string str;
//            //      m_prollspf->get_text(str);
//            //      double d = atof(str);
//            //      if(fabs(d) < 0.0000000001)
//            //      {
//            //         m_prollfps->set_text("",::e_source_initialize);
//            //      }
//            //      else
//            //      {
//            //         m_pflagview->m_frequencyFramesPerSecond = 1.0/ d;
//            //         m_pflagview->m_dwRoll= ::time::now();
//            //         m_prollfps->set_text(as_string(1.0 / d),::e_source_initialize);
//            //      }
//            //   }
//            //   catch(...)
//            //   {
//            //   }
//
//            //}
//
//
//         }
//         else if (ptopic->id() == ::id_set_check && ptopic->user_interaction() != nullptr)
//         {
//
//            string strCheck = ptopic->user_interaction()->id();
//
//            if (strCheck == "wallpaper.checkbox")
//            {
//
//               ::pointer<::user::check>pcheck = ptopic->user_interaction();
//
//               bool bEnableWallpaper = pcheck->echeck() == ::e_check_checked;
//
//               m_pimpactLastBase->get_document()->payload(m_pimpactLastBase->get_impact_prefix() + "wallpaper") = bEnableWallpaper;
//
//               //auto pgcom = m_pimpactLastBase->cast < gcom >();
//
//               //if (pgcom)
//               //{
//
//               //   pgcom->enable_wallpaper(bEnableWallpaper);
//
//               //}
//
//               //ptopic->m_bRet = true;
//
//               return;
//
//            }
//            else if (strCheck.case_insensitive_begins_eat("slide") && strCheck.case_insensitive_ends_eat(".checkbox"))
//            {
//
//               if (ptopic->user_interaction() && ptopic->m_actioncontext.is_user_source())
//               {
//
//                  int iCheck = atoi(strCheck);
//
//                  ::pointer<::user::check>pcheck = ptopic->user_interaction();
//
//                  if (m_pimpactLastImpact != nullptr && pcheck.is_set())
//                  {
//
//                     auto pslideshow = m_pimpactLastImpact->m_prender->m_pslideshow->slideshow();
//
//                     auto pslide = pslideshow->m_slidea[iCheck - 1];
//
//                     pslide->enable(pcheck->echeck() == ::e_check_checked);
//
//                     m_pimpactLastImpact->get_document()->payload(m_pimpactLastImpact->get_impact_prefix() + m_pimpactLastImpact->get_slide_id(pslide)) = pslide->m_bEnable;
//
//                     m_pimpactLastImpact->get_document()->save_document();
//
//                  }
//
//                  ptopic->m_bRet = true;
//
//                  return;
//
//               }
//
//            }
//
//         }
//
//      }
//      else
//      {
//
////         auto pimpactLastImpact = m_pimpactLastImpact;
////
////         auto pfontimpact = m_pfontimpact.m_p;
////
////         auto puserinteractionTopic = ptopic->user_interaction();
////
////         auto pfontinteraction = get_font_interaction();
//
//      //   if (m_pimpactLastImpact != nullptr && m_pfontimpact != nullptr && ptopic->user_interaction() == get_font_interaction())
//      //   {
//
//      //      if (ptopic->id() == ::id_after_change_cur_sel)
//      //      {
//
//      //         string strFont = get_font_interaction()->get_sel_by_name();
//
//      //         if (strFont.has_character())
//      //         {
//
//      //            //m_pimpactLastImpact->m_prender->m_phellomultiverse->m_strFontHover = strFont;
//
//      //            //m_pimpactLastImpact->m_prender->m_phellomultiverse->m_strFontSel = strFont;
//
//      //            //m_pimpactLastImpact->get_document()->payload(m_pimpactLastImpact->get_impact_prefix() + "font") = strFont;
//
//      //            //m_pimpactLastImpact->get_document()->save_document();
//
//      //            //m_pimpactLastImpact->set_need_layout();
//
//      //         }
//
//      //      }
//      //      else if (ptopic->id() == ::id_after_change_cur_hover)
//      //      {
//
//      //         string strFont = get_font_interaction()->get_hover_by_name();
//
//      //         if (strFont.has_character())
//      //         {
//
//      //            //m_pimpactLastImpact->m_prender->m_phellomultiverse->m_strFontHover = strFont;
//
//      //            //m_pimpactLastImpact->set_need_layout();
//
//      //         }
//
//      //      }
//
//      //   }
//      //   else if (ptopic->user_interaction() == get_color_interaction())
//      //   {
//
//
//      //      /*if (ptopic->id() == ::id_after_change_cur_sel
//      //            || ptopic->id() == ::id_after_change_cur_hover)
//      //      {
//
//      //         m_pimpactLastImpact->m_prender->m_phellomultiverse->set_foreground_hls(get_color_interaction()->get_sel_color());
//
//      //         if (ptopic->id() == ::id_after_change_cur_sel)
//      //         {
//
//      //            m_pimpactLastImpact->get_document()->payload(m_pimpactLastImpact->get_impact_prefix() + "color") = m_pimpactLastImpact->m_prender->m_phellomultiverse->get_foreground_hls();
//
//      //            m_pimpactLastImpact->get_document()->save_document();
//
//      //         }
//
//      //         m_pimpactLastImpact->set_need_redraw();
//
//      //      }*/
//
//      //   }
//
//      //}

      ::userex::pane_tab_impact::handle(ptopic, phandlercontext);

   }


   string pane_impact::get_impact_options_main_body()
   {

      string strMainBody;

      auto papp = get_app();

      //if (m_pimpactLastBase == nullptr && m_pimpactLastImpact == nullptr)
      //{

      //   strMainBody = papp->file()->as_string("matter://home.html");

      //}
      //else
      {

         strMainBody = papp->file()->as_string("matter://menu_impact.partial.html");

      }

      string strBilbo = get_bilbo_html();

      strMainBody.find_replace("***bilbo***", strBilbo);

      return strMainBody;

   }


   string pane_impact::get_bilbo_html()
   {

      string strBilbo;

      //if (m_pimpactLastImpact == m_pimpactLastBase)
      //{

      //   if (!m_pimpactLastImpact->is_alternate())
      //   {

      //      get_app()->add_yee_bulb_html(strBilbo);

      //   }

      //   int i = 1;

      //   //auto pslideshow = m_pimpactLastImpact->m_prender->m_pslideshow->slideshow();

      //   //for (auto & pslide : pslideshow->m_slidea)
      //   //{

      //   //   ::file::path path = pslide->m_strPath;

      //   //   string strName = path.title();

      //   //   string strId = "slide" + ::as_string(i) + ".checkbox";

      //   //   strBilbo += "<input type=\"checkbox\" id=\"" + strId + "\" />" + strName + "<br/>";

      //   //   i++;

      //   //}

      //}
      /*else if (m_pimpactLastBase->id() == "hello_multiverse_gcom")
      {

#if defined(FREEBSD) || defined(OPENBSD)

         strBilbo += "Animated Wallpaper prohibited at FreeBSD.<br/>";

#else

         string strName = "Wallpaper";

         string strId = "wallpaper.checkbox";

         strBilbo += "<input type=\"checkbox\" id=\"" + strId + "\" />" + strName + "<br/>";

#endif

      }*/

      return strBilbo;

   }


   //void pane_impact::create_options_body(::user::interaction * pparent)
   //{

   //   ::pointer <impact_base > pimpactbase = m_pimpactdata->m_pplaceholder->get_typed_child<::app_core_hello_multiverse::impact_base>();

   //   if (pimpactbase)
   //   {

   //      //pimpactbase->create_options_body(pparent);

   //      string strBilbo;

   //      if (!pimpactbase->is_alternate())
   //      {

   //         //get_app()->create_yee_bulb_options(pparent);

   //         pimpactbase->create_yee_bulb_options(pparent);

   //      }

   //      pimpactbase->create_options_body(pparent);


   //   }
   //   //         else if (m_pimpactLastBase->id() == "hello_multiverse_gcom")
   //   //         {
   //   //
   //   //#if defined(FREEBSD) || defined(OPENBSD)
   //   //
   //   //            strBilbo += "Animated Wallpaper prohibited at FreeBSD.<br/>";
   //   //
   //   //#else
   //   //
   //   //            string strName = "Wallpaper";
   //   //
   //   //            string strId = "wallpaper.checkbox";
   //   //
   //   //            strBilbo += "<input type=\"checkbox\" id=\"" + strId + "\" />" + strName + "<br/>";
   //   //
   //   //#endif
   //   //
   //   //         }
   //   //
   //   //         return strBilbo;


   ////}

   //}


} // namespace SceneFoundry_gpu_sandbox



