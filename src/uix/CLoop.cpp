#include "uix/CLoop.hpp"
#include "uix/CApplication.hpp"

namespace uix {
  CLoop::CLoop() : mApplication{CApplication::instance()} {
    log::nfo << "uix::CLoop::CLoop()::" << this << log::end;
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
  
  CEventLoop::CEventLoop() : CLoop() {
    log::nfo << "uix::CEventLoop::CEventLoop()::" << this << log::end;
  }
  
  void CEventLoop::exec() {
    log::nfo << "uix::CEventLoop::exec()::" << this << log::end;
    init();
    DWORD     nCurTicks{::GetTickCount()};
    MSG       sMSG;
    // the run loop
    while (mApplication->runs()) {
      if (!::HandleMessage(&sMSG) || !mApplication->runs()) {
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
  
  CGameLoop::CGameLoop(int nMaxLoops/*=10*/, int nTicksPerSec/*=25*/) : CLoop(), mMaxLoops{nMaxLoops}, mTicksPerSec{nTicksPerSec} {
    log::nfo << "uix::CGameLoop::CGameLoop(CApplication*)::" << this << log::end;
  }
  
  CGameLoop::CGameLoop(TCallback&& cTick) : CLoop() {
    log::nfo << "uix::CGameLoop::CGameLoop(TCallback)::" << this << log::end;
    tick(std::move(cTick));
  }
  
  CGameLoop::CGameLoop(TCallback&& cTick, TCallback&& cDraw) : CLoop() {
    log::nfo << "uix::CGameLoop::CGameLoop(TCallback&&, TCallback&&)::" << this << log::end;
    tick(std::move(cTick));
    draw(std::move(cDraw));
  }
  
  CGameLoop::CGameLoop(TCallback&& cTick, TCallback&& cDraw, TCallback&& cRead) : CLoop() {
    log::nfo << "uix::CGameLoop::CGameLoop(TCallback&&, TCallback&&, TCallback&&)::" << this << log::end;
    tick(std::move(cTick));
    draw(std::move(cDraw));
    read(std::move(cRead));
  }
  
  CGameLoop::~CGameLoop() {
    log::nfo << "uix::CGameLoop::~CGameLoop()::" << this << log::end;
    DELETE(mTick);
    DELETE(mDraw);
    DELETE(mRead);
  }
  
  void CGameLoop::exec() {
    log::nfo << "uix::CGameLoop::exec()::" << this << log::end;
    
    init();
    
    DWORD     nNxtTicks = mCurrTicks = ::GetTickCount();
    float     fInterp;
    int       iLoop     {0};
    const int kJumpTime {1000 / mTicksPerSec};
    MSG       sMSG;
    
    // the run loop
    while (mApplication->runs()) {
      if (!::HandleMessage(&sMSG) || !mApplication->runs()) {
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
    log::dbg << "uix::CGameLoop::load()::" << this << log::end;
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
    log::dbg << "uix::CGameLoop::tick(TCallback&&)::" << this << log::end;
    DELETE(mTick);
    mTick = new TCallback{std::move(cTick)};
  }
  
  void CGameLoop::draw(TCallback&& cDraw) {
    log::dbg << "uix::CGameLoop::tick(TCallback&&)::" << this << log::end;
    DELETE(mDraw);
    mDraw = new TCallback{std::move(cDraw)};
  }
  
  void CGameLoop::read(TCallback&& cRead) {
    log::dbg << "uix::CGameLoop::load(TCallback&&)::" << this << log::end;
    DELETE(mRead);
    mRead = new TCallback{std::move(cRead)};
  }
}
