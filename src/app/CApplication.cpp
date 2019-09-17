#include "app/CApplication.hpp"
#include "cym/uix/CFrame.hpp"
#include "cym/uix/CSurface.hpp"
#include "cym/uix/CPanel.hpp"
#include "cym/uix/CLayout.hpp"

namespace app {
  void CApplication::onInit() {
    log::dbg << "app::CApplication::onInit()::" << this << log::end;
    
    auto pWindow  = new uix::CFrame();
    auto pLayout  = dynamic_cast<uix::CBoxLayout*>(pWindow->layout(new uix::CBoxLayout(uix::EHint::VERTICAL)));
    auto pSurface = dynamic_cast<uix::CSurface*>(pLayout->add(new uix::CSurface(pWindow, uix::EHint::VISIBLE), uix::EHint::ADJUST));
    auto pPanel   = dynamic_cast<uix::CSurface*>(pLayout->add(new uix::CPanel(pWindow, uix::EHint::VISIBLE), uix::EHint::ADJUST));
    pWindow->size(600,400);
    pWindow->layout(pLayout);
    // pWindow->move(0,0);
    pWindow->title("frame");
    pWindow->center();
    pWindow->show();
    pWindow->fullscreen();
    
    pSurface->current();
    
    pSurface->clear();
    
    pSurface->swap();
  }
  
  void CApplication::onTick(int nElapsed/*=0*/) {
    log::dbg << "app::CApplication::onTick("<< nElapsed <<"ms)::" << this << log::end;
    // interpolation // for view_pos = pos + (speed * interp)
    float            fInterp; 
    int              nLoops{0};
    static const int cMaxLoops{10};
    static const int cTicksPerSec{25};             // 
    static const int cJumpTime{1000/cTicksPerSec}; // 
    
    // @todo: this should be outside while(mRunning)
    DWORD            nNxtTicks{::GetTickCount()};  // ms since app start
    
    // game.inputs();
    
    while (nNxtTicks < ::GetTickCount() && nLoops < cMaxLoops) {
      log::dbg << "app::CApplication::onTick("<< nElapsed <<"ms)::" << this << " LOOP:" << nLoops << log::end;
      // game.update();
      
      nNxtTicks += cJumpTime;
      nLoops++;
    }
    
    fInterp = float(::GetTickCount() + cJumpTime - nNxtTicks) / float(cJumpTime);
    
    // quit(0);
    
    // game.render(fInterp); 
  }
  
  void CApplication::onFree() {
    log::dbg << "app::CApplication::onFree()::" << this << log::end;
  }
}
