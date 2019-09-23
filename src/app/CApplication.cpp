#include "app/CApplication.hpp"
#include "cym/uix/CFrame.hpp"
#include "cym/uix/CSurface.hpp"
#include "cym/uix/CPanel.hpp"
#include "cym/uix/CLayout.hpp"

namespace app {
  void CApplication::onInit() {
    log::nfo << "app::CApplication::onInit()::" << this << log::end;
    
         mFrame   = new uix::CFrame();
    auto pLayout  = dynamic_cast<uix::CBoxLayout*>(mFrame->layout(new uix::CBoxLayout(uix::EHint::VERTICAL)));
         mSurface = dynamic_cast<uix::CSurface*>(pLayout->add(new uix::CSurface(mFrame, uix::EHint::VISIBLE), uix::EHint::ADJUST));
    auto pPanel   = dynamic_cast<uix::CPanel*>(pLayout->add(new uix::CPanel(mFrame, uix::EHint::VISIBLE), uix::EHint::ADJUST));
    
    mFrame->layout(pLayout);
    mFrame->title("frame");
    mFrame->show();
    
    mSurface->current();
    mSurface->clear();
    mSurface->swap();
  
    attach(mFrame, uix::EEvent::LBUTTONDOWN, &CApplication::onClick);
    attach(mFrame, uix::EEvent::KEYDOWN, &CApplication::onKeydown);
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
      // game.update();
      
      nNxtTicks += cJumpTime;
      nLoops++;
    }
    
    fInterp = float(::GetTickCount() + cJumpTime - nNxtTicks) / float(cJumpTime);
    
    // quit(0);
    
    // game.render(fInterp); 
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
}
