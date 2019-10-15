#include "app/CApplication.hpp"

namespace app {
  void CApplication::onInit() {
    log::nfo << "app::CApplication::onInit()::" << this << log::end;
  
    mMain = new app::CEditWindow;
  }
  
  void CApplication::onIdle(int nElapsed/*=0*/) {
    log::dbg << "app::CApplication::onIdle("<< nElapsed <<"ms)::" << this << log::end;
    mMain->onIdle(nElapsed);
  }
  
  void CApplication::onFree() {
    log::nfo << "app::CApplication::onFree()::" << this << log::end;
    
    DELETE(mMain);
  }
}

DECLARE_APPLICATION(app::CApplication);
