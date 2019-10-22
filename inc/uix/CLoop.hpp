#ifndef __uix_cloop_hpp__
#define __uix_cloop_hpp__

#include "uix.hpp"

#include <functional>

namespace uix {
  class CLoop {
      friend class CApplication;  
    protected:
      int           mCurrTicks   {0};
      CApplication* mApplication {nullptr};
    public:
      CLoop(CApplication*);
      virtual ~CLoop();
    protected:
      virtual void init();
      virtual void done();
      virtual void exec() = 0;
      virtual void tick() = 0;
    public:
      long elapsed() const;
  };
  
  class CEventLoop : public CLoop {
      friend class CApplication;
    public:
      CEventLoop(CApplication*);
    protected:
      void exec() override;
      void tick() override;
  };
  
  class CGameLoop : public CLoop {
      friend class CApplication;
      typedef void(*TCallback)();
    protected:
      int mMaxLoops    {10};
      int mTicksPerSec {25};
    protected:
      std::function<void()>* mRead {nullptr};
      std::function<void()>* mTick {nullptr};
      std::function<void()>* mDraw {nullptr};
    public:
      CGameLoop(CApplication*, int=10, int=25);
      CGameLoop(CApplication*, TCallback&& cTick);
      CGameLoop(CApplication*, TCallback&& cTick, TCallback&& cDraw);
      CGameLoop(CApplication*, TCallback&& cTick, TCallback&& cDraw, TCallback&& cRead);
      ~CGameLoop();
    protected: // override
      void exec() override;
      void tick() override;
      void read();
      void draw();
    public:
      void tick(TCallback&&);
      void draw(TCallback&&);
      void read(TCallback&&);
  };
}

#endif //__uix_cloop_hpp__
