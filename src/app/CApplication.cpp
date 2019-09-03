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
    auto pPanel    = new uix::CPanel(pWindow, uix::EHint::VISIBLE);
    pPanel->size(200,100);
    pWindow->move(0,0);
    pWindow->size(400,200);
    pWindow->title("frame");
    pWindow->center();
    
  }
  
  void CApplication::onTick(int nDelta) {
    //sys::cout << "app::CApplication::onTick()::" << this << " DELTA:" << nDelta << sys::endl; 
  }
  
  void CApplication::onExit() {
    std::cout << "app::CApplication::onInit()::" << this << std::endl;
  }
}
