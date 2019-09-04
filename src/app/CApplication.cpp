#include "app/CApplication.hpp"
#include "cym/uix/CFrame.hpp"
#include "cym/uix/CSurface.hpp"
#include "cym/uix/CLayout.hpp"

namespace app {
  CApplication::CApplication() {
    std::cout << "app::CApplication::CApplication()::" << this << std::endl;
  }
  
  CApplication::~CApplication() {
    std::cout << "app::CApplication::~CApplication()::" << this << std::endl;
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void CApplication::onInit() {
    std::cout << "app::CApplication::onInit()::" << this << std::endl;
    
    auto pWindow  = new uix::CFrame(uix::EHint::VISIBLE);
    auto pLayout  = dynamic_cast<uix::CBoxLayout*>(pWindow->layout(new uix::CBoxLayout(uix::EHint::VERTICAL)));
    auto pSurface = dynamic_cast<uix::CSurface*>(pLayout->add(new uix::CSurface(pWindow, uix::EHint::VISIBLE), uix::EHint::ADJUST));
    pWindow->size(600,400);
    pWindow->layout(pLayout);
    pWindow->move(0,0);
    pWindow->title("frame");
    pWindow->center();
    
    pSurface->current();
    
    ::glClearColor(0.f,0.f,0.f,0.f);
    ::glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    pSurface->swap();
  }
  
  void CApplication::onTick(int nDelta) {
    //sys::cout << "app::CApplication::onTick()::" << this << " DELTA:" << nDelta << sys::endl; 
  }
  
  void CApplication::onExit() {
    std::cout << "app::CApplication::onInit()::" << this << std::endl;
  }
}
