#include "app/CApplication.hpp"
#include "cym/uix/CFrame.hpp"

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
    
    uix::CFrame* pWindow = new uix::CFrame(nullptr);
    pWindow->move(0,0);
    pWindow->size(400,300);
    pWindow->title("test");
    pWindow->show();
    
  }
  
  void CApplication::onTick(int nDelta) {
    //sys::cout << "app::CApplication::onTick()::" << this << " DELTA:" << nDelta << sys::endl; 
  }
  
  void CApplication::onExit() {
    std::cout << "app::CApplication::onInit()::" << this << std::endl;
  }
}
