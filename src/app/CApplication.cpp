#include "app/CApplication.hpp"
#include "app/CEditWindow.hpp"

#include "uix/CLoop.hpp"
#include "uix/CEvent.hpp"
#include "uix/CSurface.hpp"
#include "uix/CPanel.hpp"
#include "uix/CLayout.hpp"
#include "uix/CButton.hpp"
#include "uix/CDialog.hpp"
#include "uix/CContext.hpp"

#include "cym/CCore.hpp"
#include "cym/CShader.hpp"
#include "cym/CTexture.hpp"
#include "cym/CModel.hpp"

#include "glm/glm.hpp"
#include "glm/CMatrix.hpp"
#include "glm/CVector.hpp"

namespace app {
  void CApplication::exec() {
    CYM_LOG_NFO( "app::CApplication::exec()::" << this);
    
// @todo: onInit
    app::CEditWindow* pMain    {new app::CEditWindow};
    
    uix::CContext*    pContext {new uix::CContext{}};
    
    uix::CButton*     pPush  {new uix::CButton{pMain,"PUSH",uix::SSize{120,40}}};
    uix::CButton*     pSave  {new uix::CButton{pMain,"SAVE",uix::SSize{120,40}}};
    uix::CPanel*      pLeft  {new uix::CPanel{pMain}};
    uix::CSurface*    pRight {new uix::CSurface{pMain, pContext}};
    
    uix::CBoxLayout*  pTopMenu {new uix::CBoxLayout{uix::ELayout::HORIZONTAL,uix::SSize{uix::AUTO,50}}};
    pTopMenu->add(pPush);
    pTopMenu->add(pSave); // @todo: on resize the second button (or TItem) runs to the right
    
    uix::CBoxLayout*  pContent {new uix::CBoxLayout{uix::ELayout::HORIZONTAL}};
    pContent->add(pLeft);
    pContent->add(pRight);
    
    uix::CBoxLayout*  pLayout  {new uix::CBoxLayout{uix::ELayout::VERTICAL}};
    pLayout->add(pTopMenu);
    pLayout->add(pContent);
    
    pMain->layout(pLayout); // pLayout->apply(pMain);
    
    
    //uix::CFileDialog* pDialog {new uix::CFileDialog{{"*.*","*.txt"}}};
    // if (pDialog->show()) {
    //   CYM_LOG_NFO( "app::CApplication::exec()::" << this << " " << pDialog->getFile());
    //   return;
    // }
    
    attach(this,     uix::CEvent::EType::KEYDOWN, &app::CApplication::onKeydown);
    
    pMain->show();
    pContext->vsync(true);
    pContext->current(pRight);
    
    cym::CCore::load();
    
    // render system flags/states
    GLCALL(::glEnable(GL_BLEND));
    GLCALL(::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    // backface culling
    GLCALL(::glDisable(GL_CULL_FACE));
    GLCALL(::glCullFace(GL_BACK));
    GLCALL(::glFrontFace(GL_CCW));
    // depth test
    GLCALL(::glEnable(GL_DEPTH_TEST));
    GLCALL(::glDepthFunc(GL_LEQUAL));
    GLCALL(::glDepthMask(GL_TRUE));
    
    auto    area {pRight->area()};
  
    CYM_LOG_NFO("app::CApplication::loop()::" << this << " pTopMenu.area " << pTopMenu->area());
    CYM_LOG_NFO("app::CApplication::loop()::" << this << " pContent.area " << pContent->area());
    CYM_LOG_NFO("app::CApplication::loop()::" << this << " pLeft.area " << pLeft->area());
    CYM_LOG_NFO("app::CApplication::loop()::" << this << " pRight.area " << pRight->area());
    CYM_LOG_NFO("app::CApplication::loop()::" << this << " pMain.area " << pMain->area());
    
    // return;
  
    auto shd {cym::CShader{"../../res/shaders/simple/perspective.hlsl"}};
    
  //auto mdl {cym::CCore::getModelManager()->load(sys::CFile{"../../res/models/ambulance/Ambulance.dae"}, cym::CModelManager::EOption::VETICES)};
    auto mdl {cym::CCore::getModelManager()->load(glm::cube{5.f})};
    auto tex {cym::CCore::getTextureManager()->load(sys::CFile{"../../res/textures/notfound.bmp"})};
    
// @todo: onTick
    cym::uint nFPS{0};
    glm::real r {0.0f};
    glm::mat4 M {1.0f};
    glm::mat4 V {glm::lookat({+0.f,+6.f,-12.f}, {0.f,0.f,0.f}, glm::Y)};
    glm::mat4 P {glm::perspective(60.f, float(area.w), float(area.h), 1.f, 1000.f)};
    // glm::mat4 P = glm::ortho(-2.0f,2.0f, -2.0f,2.0f, -1.f,+1.f);
    
    while (runs()) {
      cym::fps(nFPS);
      pMain->title("VERSION:" + std::string(pContext->version()) + " | FPS:" + std::to_string(nFPS));
  
      GLCALL(::glClearColor(0.1f,0.1f,0.1f,1.f));
      GLCALL(::glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT));
      
      glm::loop(r, 1.f, 0.f, 360.f);
      
      shd.bind(true);
      shd.uniform("u_sTexture", tex);
      shd.uniform("u_mMVP", P*V*M*glm::rotate(r,glm::Y));
      shd.uniform("u_mM", M);
      shd.uniform("u_mV", V);
      shd.uniform("u_mP", P);
      
      // vao.bind(true);
      // ibo.bind(true);
      // @todo: pRenderSystem->render(CDrawable);
      // GLCALL(::glDrawElements(GL_TRIANGLES, ibo.count(), GL_UNSIGNED_INT, GL_NULL));
      
      mdl->draw();
      
// @todo: CWindow::update()
      pContext->swap();
      poll();
    }
  
// @todo: onFree
    DELETE(pMain);
  }
  
  void CApplication::onKeydown(uix::CEvent* pEvent) {
    CYM_LOG_NFO("app::CApplication::onKeydown(CEvent*)::" << this << " K:" << pEvent->key());
    
    switch (pEvent->key()) {
      case 'Q'      : quit(0); break;
      case VK_ESCAPE: quit(0); break;
      case VK_F5    : break;
      case VK_F11   : pEvent->target()->fullscreen(); break;
    }
  }
  
  void CApplication::onClick(uix::CEvent* pEvent) {
    CYM_LOG_NFO("app::CApplication::onClick(CEvent*)::" << this << " B:" << int(pEvent->button()) << " X:" << pEvent->clientX() << " Y:" << pEvent->clientY());
  
    quit(0);
  }
  
  void CApplication::onCommand(uix::CEvent* pEvent) {
    CYM_LOG_NFO("app::CApplication::onCommand(CEvent*)::" << this << " S:" << int(pEvent->state()));
  }
}

DECLARE_APPLICATION(app::CApplication);
