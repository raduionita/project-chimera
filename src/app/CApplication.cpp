#include "app/CApplication.hpp"
#include "app/CEditWindow.hpp"

#include "uix/CLoop.hpp"
#include "uix/CEvent.hpp"
#include "uix/CSurface.hpp"
#include "uix/CPanel.hpp"
#include "uix/CLayout.hpp"
#include "uix/CButton.hpp"
#include "uix/CPainter.hpp"
#include "uix/CFrame.hpp"

#include <glo/CBuffer.hpp>
#include <glo/CArray.hpp>
#include <glo/CLayout.hpp>
#include <glo/CShader.hpp>

namespace app {
  void CApplication::onInit() {
    log::nfo << "app::CApplication::onInit()::" << this << log::end;
  
    mMain = new app::CEditWindow;
    
    auto pLayout  = new uix::CBoxLayout(uix::ELayout::VERTICAL);
    
    auto pSurface = pLayout->add(new uix::CSurface(mMain, uix::EWindow::VISIBLE), uix::ELayout::ADJUST);
    auto pPanel   = pLayout->add(new uix::CPanel(mMain, uix::EWindow::VISIBLE), uix::ELayout::ADJUST);
    auto pButton  = new uix::CButton(pPanel, "RESIZE", {50,50,90,40});
  
    pPanel->style()->background(uix::SColor{33,33,33});
    
    attach(this,    uix::EEvent::KEYDOWN,     &app::CApplication::onKeydown);
    attach(pPanel,  uix::EEvent::COMMAND,     &app::CApplication::onCommand);
    attach(pButton, uix::EEvent::LBUTTONDOWN, &app::CApplication::onClick);
    attach(pSurface,uix::EEvent::RESIZE,      &uix::CRender::onResize);
    
    mMain->layout(pLayout);
    mMain->title(pSurface->version());
    mMain->show();
    
    pSurface->current();
    
    GLfloat2 vertices[] = {{-0.5f,-0.5f},{+0.5f,-0.5f},{+0.5f,+0.5f},{-0.5f,+0.5f}};
    GLuint   indices [] = {0,1,2, 2,3,0};
  
    glo::CVertexArray  vao;
    glo::CVertexBuffer vbo{vertices, 4 * 2 * sizeof(GLfloat)};
    glo::CVertexLayout vlo;
    vlo.push({GL_FLOAT, 2});
    vao.buffer(vbo, vlo);
    glo::CIndexBuffer  ibo{indices, 6};
  
    glo::CShader prg{"../../res/shaders/simple/color.glsl"};
    
    // loop setup
    mLoop = new uix::CGameLoop([this](){
      // tick/update  
      log::nfo << "  L::TICK" << log::end;
    }, [pSurface,this](){
      // draw/render
      log::nfo << "  L::DRAW" << log::end;
      
      pSurface->current();
      pSurface->clear();
      
      // draw stuff
      
      
      pSurface->swap();
    });
  }
  
  void CApplication::onFree() {
    log::nfo << "app::CApplication::onFree()::" << this << log::end;
    
    DELETE(mMain);
  }
  
  void CApplication::onKeydown(uix::CEvent* pEvent) {
    log::nfo << "app::CApplication::onKeydown(CEvent*)::" << this << " K:" << pEvent->key() << log::end;
    
    switch (pEvent->key()) {
      case 'Q'      : quit(0); break;
      case VK_ESCAPE: quit(0); break;
      case VK_F5    : break;
      case VK_F11   : mMain->fullscreen(); break;
    }
  }
  
  void CApplication::onClick(uix::CEvent* pEvent) {
    log::nfo << "app::CApplication::onClick(CEvent*)::" << this << " B:" << int(pEvent->button()) << " X:" << pEvent->clientX() << " Y:" << pEvent->clientY() << log::end;
  
    quit(0);
  }
  
  void CApplication::onCommand(uix::CEvent* pEvent) {
    log::nfo << "app::CApplication::onCommand(CEvent*)::" << this << " S:" << int(pEvent->state()) << log::end;
    
  }
}

DECLARE_APPLICATION(app::CApplication);
