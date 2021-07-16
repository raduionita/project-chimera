#include "uix/CLoop.hpp"
#include "uix/CApplication.hpp"

namespace uix {
  CLoop::CLoop() : mApplication{CApplication::instance()} {
    CYM_LOG_NFO("uix::CLoop::CLoop()::" << this);
  }
  
  CLoop::~CLoop() {
    CYM_LOG_NFO("uix::CLoop::~CLoop()::" << this);
  }
  
  void CLoop::init() {
    CYM_LOG_NFO("uix::CLoop::init()::" << this);
  }
  
  void CLoop::done() {
    CYM_LOG_NFO("uix::CLoop::done()::" << this);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CEventLoop::CEventLoop() : CLoop() {
    CYM_LOG_NFO("uix::CEventLoop::CEventLoop()::" << this);
  }
  
  void CEventLoop::loop() {
    CYM_LOG_NFO("uix::CEventLoop::loop()::" << this);
    init();
    DWORD     nCurTicks{::GetTickCount()};
    MSG       sMSG;
    // the run loop
    while (mApplication->runs()) {
      if (!::HandleMessage(&sMSG) || !mApplication->runs()) {
        break;
      }
      tick(::GetTickElapsed()/1000.f);
    }
    done();
  }
  
  void CEventLoop::tick(float fElapsed) {
    mApplication->runs() && mApplication->tick(fElapsed);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CGameLoop::CGameLoop(int nMaxLoops/*=10*/, int nTicksPerSec/*=25*/) : CLoop(), mMaxLoops{nMaxLoops}, mTicksPerSec{nTicksPerSec} {
    CYM_LOG_NFO("uix::CGameLoop::CGameLoop(CApplication*)::" << this);
  }
  
  CGameLoop::CGameLoop(FTick&& cTick) : CLoop(), mTick{std::move(cTick)} {
    CYM_LOG_NFO("uix::CGameLoop::CGameLoop(TCallback)::" << this);
  }
  
  CGameLoop::CGameLoop(FTick&& cTick, FDraw&& cDraw) : CLoop() {
    CYM_LOG_NFO("uix::CGameLoop::CGameLoop(TCallback&&, TCallback&&)::" << this);
    tick(std::move(cTick));
    draw(std::move(cDraw));
  }
  
  CGameLoop::CGameLoop(FTick&& cTick, FDraw&& cDraw, FRead&& cRead) : CLoop() {
    CYM_LOG_NFO("uix::CGameLoop::CGameLoop(TCallback&&, TCallback&&, TCallback&&)::" << this);
    tick(std::move(cTick));
    draw(std::move(cDraw));
    read(std::move(cRead));
  }
  
  CGameLoop::~CGameLoop() {
    CYM_LOG_NFO("uix::CGameLoop::~CGameLoop()::" << this);
  }
  
  void CGameLoop::loop() {
    CYM_LOG_NFO("uix::CGameLoop::loop()::" << this);
    
    init();
    
    DWORD     nCurrTicks;
    DWORD     nNxtTicks = nCurrTicks = ::GetTickCount();
    float     fInterp;
    int       iLoop     {0};
    const int kJumpTime {1000 / mTicksPerSec};
    MSG       sMSG;
    
    // the run loop
    while (mApplication->runs()) {
      if (!::HandleMessage(&sMSG) || !mApplication->runs()) {
        break;
      }
  
      // read inputs
      read();
  
      // update loop (game state)
      iLoop = 0;
      // if tick logic is very fast => do it again
      while ((nNxtTicks < ::GetTickCount()) && (iLoop++ < mMaxLoops)) {
        
        tick(::GetTickElapsed()/1000.f);
        
        nNxtTicks += kJumpTime;
      }
      
      // fInterp = float(::GetTickCount() + kJumpTime - nNxtTicks) / float(kJumpTime);
      
      // draw scene
      draw();
    }
    
    done();
  }
  
  void CGameLoop::read() {
    log::dbg << "uix::CGameLoop::init()::" << this << log::end;
    if (mRead) mRead();
  }
  
  void CGameLoop::tick(float fElapsed) {
    log::dbg << "uix::CGameLoop::tick(float)::" << this << log::end;
    if (mTick) mTick(fElapsed);
  }
  
  void CGameLoop::draw() {
    log::dbg << "uix::CGameLoop::draw(float)::" << this << log::end;
    if (mDraw) mDraw();
  }
  
  void CGameLoop::tick(FTick&& cTick) {
    log::dbg << "uix::CGameLoop::tick(FTick&&)::" << this << log::end;
    mTick = std::move(cTick);
  }
  
  void CGameLoop::draw(FDraw&& cDraw) {
    log::dbg << "uix::CGameLoop::tick(FDraw&&)::" << this << log::end;
    mDraw = std::move(cDraw);
  }
  
  void CGameLoop::read(FRead&& cRead) {
    log::dbg << "uix::CGameLoop::init(FRead&&)::" << this << log::end;
    mRead = std::move(cRead);
  }
}
