#include "cym/uix/CApplication.hpp"
#include "cym/uix/CConsole.hpp"

namespace cym { namespace uix {
  CApplication* CApplication::sInstance{nullptr};
  
  CApplication::CApplication(HINSTANCE hHandle/*=::GetModuleHandle(NULL)*/, int nCmdShow/*=0*/) : CObject(), mHandle{hHandle} {
    log::nfo << "uix::CApplication::CApplication()::" << this << " INSTANCE:" << mHandle << log::end;
    assert(!sInstance && "CApplication::sIntastace already defined.");
    mConsole  = new CConsole(this, nCmdShow);
    sInstance = this;
  }
  
  CApplication::CApplication(const CApplication&) {
    log::nfo << "uix::CApplication::CApplication(CApplication&)::" << this << log::end;
  }
    
  CApplication::~CApplication() {
    log::nfo << "uix::CApplication::~CApplication()::" << this << log::end;
  }
  
  CApplication& CApplication::operator =(const CApplication& that) {
    if (this != &that) {
      
    }
    return *this;
  }
  
  CApplication::operator HINSTANCE() {
    return mHandle;
  }
  
  CApplication::operator const HINSTANCE() const {
    return mHandle;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CApplication::init() {
    log::nfo << "uix::CApplication::init()::" << this << log::end;
    
    onInit();
    return true;
  }
  
  bool CApplication::tick(int nElapsed/*=0*/) {
    // log::dbg << "uix::CApplication::tick("<< nElapsed <<")::" << this << log::end;
    onTick(nElapsed);
    return true;
  }
  
  bool CApplication::free() {
    log::nfo << "uix::CApplication::free()::" << this << log::end;
    onFree();
    return true;
  }
  
  bool CApplication::exec(int nMode/*=0*/) {
    log::nfo << "uix::CApplication::exec()::" << this << log::end;
    try {
      mRunning = init();
      // prepare
      MSG       sMsg;
      DWORD     nPrvTicks;
      DWORD     nCurTicks;
      DWORD     nNxtTicks;
      const int cTPS{25};
      const int cJumpTime{1000/cTPS}; // 1s/25 ~ 40ms = how many jumps in 1 sec 
      const int cMaxLoops{5};
      int       nLoops;
      // the run loop
      while (mRunning) {
        nCurTicks = nPrvTicks = ::GetTickCount();
        nNxtTicks = nCurTicks + cJumpTime; // current_ms_count + fraction_of_a_sec_ms
        nLoops    = 0;
        // the message loop // allowed to last max 40ms // AND // max of 10 events
        while (nCurTicks < nNxtTicks && nLoops < cMaxLoops) { 
          if (::PeekMessage(&sMsg, NULL, 0, 0, PM_REMOVE)) {
            if (WM_QUIT == sMsg.message) {
              mRunning = false;
              break;
            } else {
              ::TranslateMessage(&sMsg);
              ::DispatchMessage(&sMsg);
            }
            nCurTicks = ::GetTickCount();
            nLoops++;
          } else { break; }
        }
        // tick
        mRunning && tick(::GetTickCount() - nPrvTicks);
      }
      
      mRunning = !free();
      
      return (int)(sMsg.wParam);
    } catch (CException& ex) {
      log::err << ex << log::end;
      return -1;
    }
  }
  
  bool CApplication::quit(int nCode/*=0*/) {
    log::nfo << "uix::CApplication::quit(int)::" << this << log::end;
    return !(mRunning = false);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CApplication* CApplication::instance() { return (!sInstance) ? sInstance = new CApplication : sInstance; }
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CApplication::onInit()    { }
  void CApplication::onTick(int) { }
  void CApplication::onFree()    { }
}}
