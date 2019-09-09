#include "cym/uix/CLoop.hpp"

namespace cym { namespace uix {
  CLoop::CLoop() {
    log::nfo << "uix::CLoop::CLoop()::" << this << log::end;
  }
  
  CLoop::~CLoop() {
    log::nfo << "uix::CLoop::~CLoop()::" << this << log::end;
  }
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CLoop::init(int) { return true; }
  
  bool CLoop::exec(int nMode/*=0*/) {
    log::nfo << "uix::CLoop::exec(int)::" << this << log::end;
    init();
    while (mRunning) { tick(); }
    exit();
    return true;
  }
  
  bool CLoop::tick(int) { return true; }
  
  bool CLoop::quit(int nCode/*=0*/) {
    log::nfo << "uix::CLoop::quit(int)::" << this << log::end;
    mRunning = false;
    return nCode;
  }
  
  bool CLoop::exit(int) { return true; }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CGameLoop::exec(int nMode/*=0*/) {
    log::nfo << "uix::CGameLoop::exec(int)::" << this << log::end;
    mRunning = init();
    MSG sMsg{0};
    while (mRunning) {
      DWORD nCurTicks = ::GetTickCount();
      DWORD nEndTicks = nCurTicks + 1000 / mFPS; // 33ms (30fps)
      // allowed to last max 33ms = 1frame out of 30?! or out of 31
      while (nCurTicks < nEndTicks) {
        if (::PeekMessage(&sMsg, NULL, 0, 0, PM_REMOVE)) {
          if (WM_QUIT == sMsg.message) {
            mRunning = false;
            break;
          } else {
            ::TranslateMessage(&sMsg);
            ::DispatchMessage(&sMsg);
          }
          nCurTicks = ::GetTickCount();
        } else {
          break;
        }
      }
      // process frame
      tick(nCurTicks);
    }
    return exit();
    
    
    DWORD     nNextTick = ::GetTickCount(); // ms since app start
    DWORD     nCurrTick;
    int       nLoops;
    const int cMaxLoops = 10;
    const int cSkipTime = 1000 / mFPS; // 1s/30  ~ 33ms
    float     fInterp; // interpolation // for view_pos = pos + (speed * interp)
    while (mRunning) {
      // handle events
      
      nLoops = 0;
      nCurrTick = ::GetTickCount(); // should this be inside the loop
      while (nNextTick < nCurrTick && nLoops < cMaxLoops) {
        // update
        nNextTick += cSkipTime;
        nLoops++;
      }
      // interp = float(::GetTickCount() + cSkipTime - nNextTick) / float(cSkipTime)
      // render(interp) // 
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
  }
}}
