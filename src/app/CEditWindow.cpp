#include "app/CEditWindow.hpp"
#include "uix/CPanel.hpp"
#include "uix/CButton.hpp"
#include "uix/CLayout.hpp"
#include "uix/CPainter.hpp"
#include "uix/CEvent.hpp"
#include "uix/CFrame.hpp"
#include "uix/CSurface.hpp"

#include <glo/CBuffer.hpp>
#include <glo/CArray.hpp>
#include <glo/CLayout.hpp>
#include <glo/CShader.hpp>

namespace app {
  CEditWindow::CEditWindow() {
    log::nfo << "app::CEditWindow::CEditWindow()::" << this << log::end;
  }
  
  CEditWindow::~CEditWindow() {
    log::nfo << "app::CEditWindow::~CEditWindow()::" << this << log::end;
  }
  
  void CEditWindow::onInit() {
    log::nfo << "app::CEditWindow::onInit()::" << this << log::end;
         
    auto pLayout  = layout(new uix::CBoxLayout(uix::ELayout::VERTICAL));
    
         mSurface = pLayout->add(new uix::CSurface(this, uix::EWindow::VISIBLE), uix::ELayout::ADJUST);
    auto pPanel   = pLayout->add(new uix::CPanel(this, uix::EWindow::VISIBLE), uix::ELayout::ADJUST);
    auto pButton  = new uix::CButton(pPanel, "RESIZE", {50,50,90,40});
  
    pPanel->style()->background(uix::SColor{33,33,33});
    
    attach(this,    uix::EEvent::KEYDOWN,     &app::CEditWindow::onKeydown);
    attach(pPanel,  uix::EEvent::DRAW,        &app::CEditWindow::onDraw);
    attach(pPanel,  uix::EEvent::COMMAND,     &app::CEditWindow::onCommand);
    attach(pButton, uix::EEvent::LBUTTONDOWN, &app::CEditWindow::onClick);
    attach(mSurface,uix::EEvent::RESIZE,      &uix::CRender::onResize);
    
    layout(pLayout);
    title(mSurface->version());
    show();
  
    mSurface->current();

    // init world here
  
    GLfloat2 vertices[] = {{-0.5f,-0.5f},{+0.5f,-0.5f},{+0.5f,+0.5f},{-0.5f,+0.5f}};
    GLuint   indices [] = {0,1,2, 2,3,0};
  
    glo::CVertexArray  vao;
    glo::CVertexBuffer vbo{vertices, 4 * 2 * sizeof(GLfloat)};
    glo::CVertexLayout vlo;
    vlo.push({GL_FLOAT, 2});
    vao.buffer(vbo, vlo);
    glo::CIndexBuffer  ibo{indices, 6};
  
    glo::CShader prg{"../../res/shaders/simple/color.glsl"};
  }
  
  void CEditWindow::onIdle(int nElapsed) {
    log::dbg << "app::CEditWindow::onIdle("<< nElapsed <<"ms)::" << this << log::end;
    // interpolation // for view_pos = pos + (speed * interp)
    float            fInterp; 
    int              nLoops{0};
    static const int cMaxLoops{10};
    static const int cTicksPerSec{25};             // 
    static const int cJumpTime{1000/cTicksPerSec}; // 
    // this should be outside while(mRunning)
    static DWORD     nNxtTicks{::GetTickCount()};  // ms since app start
    
    // game.inputs();
    
    // the update loop
    while (nNxtTicks < ::GetTickCount() && nLoops < cMaxLoops) {
      log::nfo << "app::CEditWindow::onIdle("<< nElapsed <<"ms)::" << this << " LOOP:" << nLoops << log::end;
      // game.update(timer);
      
      nNxtTicks += cJumpTime;
      nLoops++;
    }
    
    fInterp = float(::GetTickCount() + cJumpTime - nNxtTicks) / float(cJumpTime);
    
    mSurface->clear();
    
    // draw world here
    
    
    mSurface->swap();
  }
  
  void CEditWindow::onFree() {
    log::nfo << "app::CEditWindow::onFree()::" << this << log::end;
  }
  
  void CEditWindow::onKeydown(uix::CEvent* pEvent) {
    log::nfo << "app::CEditWindow::onKeydown(CEvent*)::" << this << " K:" << pEvent->key() << log::end;
    
    switch (pEvent->key()) {
      case 'Q'      : close(); break;
      case VK_ESCAPE: close(); break;
      case VK_F5    : mSurface->reset(); break;
      case VK_F11   : fullscreen(); break;
    }
  }
  
  void CEditWindow::onClick(uix::CEvent* pEvent) {
    log::nfo << "app::CEditWindow::onClick(CEvent*)::" << this << " B:" << int(pEvent->button()) << " X:" << pEvent->clientX() << " Y:" << pEvent->clientY() << log::end;
  
    mSurface->area({0, 0, 100, 100});
    close();
  }
  
  void CEditWindow::onCommand(uix::CEvent* pEvent) {
    log::nfo << "app::CEditWindow::onCommand(CEvent*)::" << this << " S:" << int(pEvent->state()) << log::end;
  }
  
  void CEditWindow::onDraw(uix::CEvent* pEvent) {
    log::nfo << "app::CEditWindow::onDraw(CEvent*)::" << this << log::end;
    
    uix::CPainter oPainter(pEvent->target());
    
    oPainter.rectangle({0,0,10,30});
  }
}
