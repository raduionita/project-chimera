#include "app/CApplication.hpp"
#include "cym/uix/CFrame.hpp"
#include "cym/uix/CSurface.hpp"
#include "cym/uix/CPanel.hpp"
#include "cym/uix/CLayout.hpp"

namespace app {
  void CApplication::onInit() {
    log::nfo << "app::CApplication::onInit()::" << this << log::end;
    
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
    
    pSurface->current();
    
    pSurface->clear();
    
    pSurface->swap();
  }
  
  void CApplication::onTick() {
    // interpolation // for view_pos = pos + (speed * interp)
    float     fInterp; 
    int       nLoops;
    const int cMaxLoops{10};
    const int cTicksPerSec{25};             // 
    const int cJumpTime{1000/cTicksPerSec}; // 
    DWORD nNxtTicks = ::GetTickCount();     // ms since app start
    while (mRunning) {
      // game.inputs();
      
      nLoops = 0;
      while (nNxtTicks < ::GetTickCount() && nLoops < cMaxLoops) {
        // game.update();
        
        nNxtTicks += cJumpTime;
        nLoops++;
      }
      fInterp = float(::GetTickCount() + cJumpTime - nNxtTicks) / float(cJumpTime);
      
      // game.render(fInterp); 
    }
  }
  
  void CApplication::onFree() {
    log::nfo << "app::CApplication::onFree()::" << this << log::end;
  }
}
