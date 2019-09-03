#include "app/CApplication.hpp"
#include "cym/uix/CFrame.hpp"
#include "cym/uix/CSurface.hpp"

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
    auto pSurface = new uix::CSurface(pWindow, {}, uix::EHint::VISIBLE);
    pSurface->size(200,100);
    pWindow->move(0,0);
    pWindow->size(400,200);
    pWindow->title("frame");
    pWindow->center();
    
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
