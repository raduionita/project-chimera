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
    // log::dbg << "uix::CApplication::init()::" << this << log::end;
    onInit();
    return true;
  }
  
  bool CApplication::tick() {
    // log::dbg << "uix::CApplication::tick()::" << this << log::end;
    onTick();
    return true;
  }
  
  bool CApplication::free() {
    // log::dbg << "uix::CApplication::free()::" << this << log::end;
    onFree();
    return true;
  }
  
  bool CApplication::exec(int nMode/*=0*/) {
    try {
      log::nfo << "uix::CApplication::exec()::" << this << log::end;
      
      mRunning = init();
      
      MSG       sMsg{0};
      DWORD     nCurTicks{0};
      DWORD     nNxtTicks{0};
      const int cJumpTime{1000/mTPS}; // 1s/25 ~ 40ms = how many jumps in 1 sec 
      int       nLoop;
      while (mRunning) {
        nCurTicks = ::GetTickCount();
        nNxtTicks = nCurTicks + cJumpTime; // current_ms_count + fraction_of_a_sec_ms
        nLoop     = 0;
        // allowed to last max 40ms // AND // max of 10 events
        while (nCurTicks < nNxtTicks && nLoop < mLoops) { 
          if (::PeekMessage(&sMsg, NULL, 0, 0, PM_REMOVE)) {
            if (WM_QUIT == sMsg.message) {
              mRunning = false;
              break;
            } else {
              ::TranslateMessage(&sMsg);
              ::DispatchMessage(&sMsg);
            }
            nCurTicks = ::GetTickCount();
            nLoop++;
          } else { break; }
        }
        // tick
        mRunning = mRunning && tick();
      }
      
      mRunning = !free();
      
      return (int)(sMsg.wParam);
    } catch (sys::CException& ex) {
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
  
  void CApplication::onInit() { }
  void CApplication::onTick() { }
  void CApplication::onFree() { }
}}
