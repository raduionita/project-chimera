#include "app/CApplication.hpp"
#include "uix/CFrame.hpp"
#include "uix/CSurface.hpp"
#include "uix/CPanel.hpp"
#include "uix/CButton.hpp"
#include "uix/CLayout.hpp"
#include "uix/CPainter.hpp"
#include "uix/CEvent.hpp"

namespace app {
  void CApplication::onInit() {
    log::dbg << "app::CApplication::onInit()::" << this << log::end;
    
         mFrame   = new uix::CFrame();
    auto pLayout  = mFrame->layout(new uix::CBoxLayout(uix::ELayout::VERTICAL));
         mSurface = pLayout->add(new uix::CSurface(mFrame, uix::EWindow::VISIBLE), uix::ELayout::ADJUST);
    auto pPanel   = pLayout->add(new uix::CPanel(mFrame, uix::EWindow::VISIBLE), uix::ELayout::ADJUST);
    auto pButton  = new uix::CButton(pPanel, "CLICK", {50,50,90,40});
  
    pPanel->style()->background(uix::SColor{33,33,33});
    
    attach(mFrame,  uix::EEvent::KEYDOWN,     &CApplication::onKeydown);
    attach(pPanel,  uix::EEvent::DRAW,        &CApplication::onDraw);
    attach(pPanel,  uix::EEvent::COMMAND,     &CApplication::onCommand);
    attach(pButton, uix::EEvent::LBUTTONDOWN, &CApplication::onClick);
    attach(mSurface,uix::EEvent::RESIZE,      &uix::CSurface::onResize);
    
    mFrame->layout(pLayout);
    mFrame->title(mSurface->version());
    mFrame->show();
    
    // @todo: engine init
    // mEngine = new ngn::CEngine(mSurface)
    // OR
    // mEngine = new ngn::CEngine(mSurface->context())
    
    // @todo: loop
    // mLoop = CGameLoop(&CEngine::update,&CEngine::render)
    // OR
    // mEngine->tick(); // w/ it's own ::render() & ::update()
  }
  
  void CApplication::onTick(int nElapsed/*=0*/) {
    log::dbg << "app::CApplication::onTick("<< nElapsed <<"ms)::" << this << log::end;
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
      log::nfo << "app::CApplication::onTick("<< nElapsed <<"ms)::" << this << " LOOP:" << nLoops << log::end;
      // game.update(timer);
      
      nNxtTicks += cJumpTime;
      nLoops++;
    }
    
    fInterp = float(::GetTickCount() + cJumpTime - nNxtTicks) / float(cJumpTime);
    
    mSurface->current();
    mSurface->clear();
  
    // game.render(fInterp);

    mSurface->swap();
  }
  
  void CApplication::onFree() {
    log::nfo << "app::CApplication::onFree()::" << this << log::end;
  }
  
  void CApplication::onKeydown(uix::CEvent* pEvent) {
    log::nfo << "app::CApplication::onKeydown(CEvent*)::" << this << " K:" << pEvent->key() << log::end;
    
    switch (pEvent->key()) {
      case 'Q'      : quit(0); break;
      case VK_ESCAPE: quit(0); break;
      case VK_F5    : mSurface->reset(); break;
      case VK_F11   : mFrame->fullscreen(); break;
    }
  }
  
  void CApplication::onClick(uix::CEvent* pEvent) {
    log::nfo << "app::CApplication::onClick(CEvent*)::" << this << " B:" << int(pEvent->button()) << " X:" << pEvent->clientX() << " Y:" << pEvent->clientY() << log::end;
    quit();
  }
  
  void CApplication::onCommand(uix::CEvent* pEvent) {
    log::nfo << "app::CApplication::onCommand(CEvent*)::" << this << " S:" << int(pEvent->state()) << log::end;
  }
  
  void CApplication::onDraw(uix::CEvent* pEvent) {
    log::nfo << "app::CApplication::onDraw(CEvent*)::" << this << log::end;
    
    uix::CPainter oPainter(pEvent->target());
    
    
    oPainter.rectangle({0,0,10,30});
  }
}

DECLARE_APPLICATION(app::CApplication);
