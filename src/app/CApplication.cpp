#include "app/CApplication.hpp"

namespace app {
  void CApplication::onInit() {
    log::dbg << "app::CApplication::onInit()::" << this << log::end;
  
    mMain = new app::CEditWindow;
  }
  
  void CApplication::onIdle(int nElapsed/*=0*/) {
    log::dbg << "app::CApplication::onIdle("<< nElapsed <<"ms)::" << this << log::end;
    // interpolation // for view_pos = pos + (speed * interp)
    float            fInterp; 
    int              nLoops{0};
    static const int cMaxLoops{10};
    static const int cTicksPerSec{25};             // 
    static const int cJumpTime{1000/cTicksPerSec}; // 
    // this should be outside while(mRunning)
    static DWORD     nNxtTicks{::GetTickCount()};  // ms since app start
    
    // game.inputs();
    
    // the update loop
    while (nNxtTicks < ::GetTickCount() && nLoops < cMaxLoops) {
      log::nfo << "app::CApplication::onIdle("<< nElapsed <<"ms)::" << this << " LOOP:" << nLoops << log::end;
      // game.update(timer);
      
      nNxtTicks += cJumpTime;
      nLoops++;
    }
    
    fInterp = float(::GetTickCount() + cJumpTime - nNxtTicks) / float(cJumpTime);
    
    // mSurface->current();
    // mSurface->clear();
    //
    // // game.render(fInterp);
    //
    // mSurface->swap();
  }
  
  void CApplication::onFree() {
    log::nfo << "app::CApplication::onFree()::" << this << log::end;
    
    DELETE(mMain);
  }
}

DECLARE_APPLICATION(app::CApplication);
