#include "app/CApplication.hpp"
#include "cym/uix/CCanvas.hpp"

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
    
    auto pWindow = new uix::CFrame;
    pWindow->move(0,0);
    pWindow->size(400,300);
    pWindow->title("frame");
    pWindow->center();
    pWindow->show();
    
  }
  
  void CApplication::onTick(int nDelta) {
    //sys::cout << "app::CApplication::onTick()::" << this << " DELTA:" << nDelta << sys::endl; 
  }
  
  void CApplication::onExit() {
    std::cout << "app::CApplication::onInit()::" << this << std::endl;
  }
}
