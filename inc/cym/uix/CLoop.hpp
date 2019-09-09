#ifndef __cym_uix_cloop_hpp__
#define __cym_uix_cloop_hpp__

#include "uix.hpp"

namespace cym { namespace uix {
  class CLoop {
    protected:
    DWORD mStart   = {::GetTickCount()};
    bool  mRunning = {false};
    
    public:
    CLoop();
    virtual ~CLoop();
    
    public:
    virtual bool init(int = 0); // event
    virtual bool exec(int = 0); // action
    virtual bool tick(int = 0); // event
    virtual bool quit(int = 0); // action
    virtual bool exit(int = 0); // event
    
    public:
    virtual void onInit();
    virtual void onTick();
    virtual void onExit();
  };
  
  class CEventLoop : public CLoop {
    public:
    virtual bool exec(int = 0);
  };
  
  class CGameLoop : public CLoop {
    protected:
    int mFPS = {30};
    public:
    virtual bool exec(int = 0);
  };
}}

#endif //__cym_uix_cloop_hpp__

// @todo: CEventLoop
// @todo: CGameLoop
