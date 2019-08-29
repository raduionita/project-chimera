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
    
    uix::CCanvas* pWindow = new uix::CCanvas(uix::CCanvas::SOptions{});
    
    pWindow->title(reinterpret_cast<LPCSTR>(::glGetString(GL_VERSION)));
  }
  
  void CApplication::onTick(int nDelta) {
    //std::cout << "app::CApplication::onTick()::" << this << " DELTA:" << nDelta << std::endl; 
  }
  
  void CApplication::onExit() {
    std::cout << "app::CApplication::onInit()::" << this << std::endl;
  }
}
