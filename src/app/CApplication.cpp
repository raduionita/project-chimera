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
  
  void CApplication::onTick(long nElapsed) {
    //sys::cout << "app::CApplication::onTick()::" << this << " DELTA:" << nDelta << sys::endl; 
  }
  
  void CApplication::onExit() {
    log::nfo << "app::CApplication::onInit()::" << this << log::end;
  }
}
