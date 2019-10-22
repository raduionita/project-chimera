#include "uix/CLoop.hpp"
#include "uix/CApplication.hpp"

namespace uix {
  CLoop::CLoop(CApplication* pApp) : mApplication{pApp} {
    log::nfo << "uix::CLoop::CLoop(CApplication*)::" << this << log::end;
  }
  
  CLoop::~CLoop() {
    log::nfo << "uix::CLoop::~CLoop()::" << this << log::end;
  }
  
  void CLoop::init() {
    log::nfo << "uix::CLoop::init()::" << this << log::end;
  }
  
  void CLoop::done() {
    log::nfo << "uix::CLoop::done()::" << this << log::end;
  }
  
  long CLoop::elapsed() const {
    return ::GetTickCount() - mCurrTicks;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CEventLoop::CEventLoop(CApplication* pApp) : CLoop(pApp) {
    log::nfo << "uix::CEventLoop::CEventLoop(CApplication*)::" << this << log::end;
  }
  
  void CEventLoop::exec() {
    log::nfo << "uix::CEventLoop::exec()::" << this << log::end;
    init();
    DWORD     nCurTicks{::GetTickCount()};
    // the run loop
    while (mApplication->runs()) {
      if (!::HandleMessage()) {
        break;
      }
      tick();
    }
    done();
  }
  
  void CEventLoop::tick() {
    mApplication->runs() && mApplication->tick(elapsed());
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CGameLoop::CGameLoop(CApplication* pApp, int nMaxLoops/*=10*/, int nTicksPerSec/*=25*/) : CLoop(pApp), mMaxLoops{nMaxLoops}, mTicksPerSec{nTicksPerSec} {
    log::nfo << "uix::CGameLoop::CGameLoop(CApplication*)::" << this << log::end;
  }
  
  CGameLoop::CGameLoop(CApplication* pApp, TCallback&& cTick) : CLoop(pApp) {
    log::nfo << "uix::CGameLoop::CGameLoop(CApplication*, TCallback&&)::" << this << log::end;
    tick(std::move(cTick));
  }
  
  CGameLoop::CGameLoop(CApplication* pApp, TCallback&& cTick, TCallback&& cDraw) : CLoop(pApp) {
    log::nfo << "uix::CGameLoop::CGameLoop(CApplication*, TCallback&&, TCallback&&)::" << this << log::end;
    tick(std::move(cTick));
    draw(std::move(cDraw));
  }
  
  CGameLoop::CGameLoop(CApplication* pApp, TCallback&& cTick, TCallback&& cDraw, TCallback&& cRead) : CLoop(pApp) {
    log::nfo << "uix::CGameLoop::CGameLoop(CApplication*, TCallback&&, TCallback&&, TCallback&&)::" << this << log::end;
    tick(std::move(cTick));
    draw(std::move(cDraw));
    read(std::move(cRead));
  }
  
  CGameLoop::~CGameLoop() {
    log::nfo << "uix::CGameLoop::~CGameLoop()::" << this << log::end;
    DELETE(mRead);
    DELETE(mTick);
    DELETE(mDraw);
  }
  
  void CGameLoop::exec() {
    log::nfo << "uix::CGameLoop::exec()::" << this << log::end;
    
    init();
    
    DWORD     nNxtTicks = mCurrTicks = ::GetTickCount();
    float     fInterp;
    int       iLoop     {0};
    const int kJumpTime {1000 / mTicksPerSec}; 
    
    // the run loop
    while (mApplication->runs()) {
      if (!::HandleMessage() || !mApplication->runs()) {
        break;
      }
  
      read();
  
      iLoop = 0;
      // the update loop
      while (nNxtTicks < ::GetTickCount() && iLoop++ < mMaxLoops) {
        
        tick();
        
        nNxtTicks += kJumpTime;
      }
      
      // fInterp = float(::GetTickCount() + kJumpTime - nNxtTicks) / float(kJumpTime);
      
      draw();
    }
    
    done();
  }
  
  void CGameLoop::read() {
    log::dbg << "uix::CGameLoop::read()::" << this << log::end;
    if (mRead) (*mRead)();
  }
  
  void CGameLoop::tick() {
    log::dbg << "uix::CGameLoop::tick()::" << this << log::end;
    if (mTick) (*mTick)();
  }
  
  void CGameLoop::draw() {
    log::dbg << "uix::CGameLoop::draw(float)::" << this << log::end;
    if (mDraw) (*mDraw)();
  }
  
  void CGameLoop::tick(TCallback&& cTick) {
    log::dbg << "uix::CGameLoop::tick(void(*)())::" << this << log::end;
    DELETE(mTick);
    mTick = new std::function<void()>{std::move(cTick)};
  }
  
  void CGameLoop::draw(TCallback&& cDraw) {
    log::dbg << "uix::CGameLoop::tick(void(*)())::" << this << log::end;
    DELETE(mDraw);
    mDraw = new std::function<void()>{std::move(cDraw)};
  }
  
  void CGameLoop::read(TCallback&& cRead) {
    log::dbg << "uix::CGameLoop::read(void(*)())::" << this << log::end;
    DELETE(mRead);
    mRead = new std::function<void()>{std::move(cRead)};
  }
}
