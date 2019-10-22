#include "app/CApplication.hpp"
#include "uix/CLoop.hpp"

namespace app {
  void CApplication::onInit() {
    log::nfo << "app::CApplication::onInit()::" << this << log::end;
  
    mMain = new app::CEditWindow;
    mLoop = new uix::CGameLoop([this](){ this->onTick(0); });
    
    // @todo: fix loop still running after window is closed!!!
  }
  
  void CApplication::onTick(int nElapsed/*=0*/) {
    log::nfo << "app::CApplication::onTick("<< nElapsed <<"ms)::" << this << log::end;
    mMain->onTick(nElapsed);
  }
  
  void CApplication::onFree() {
    log::nfo << "app::CApplication::onFree()::" << this << log::end;
    
    DELETE(mMain);
  }
}

DECLARE_APPLICATION(app::CApplication);
