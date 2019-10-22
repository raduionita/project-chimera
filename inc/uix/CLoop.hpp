#ifndef __uix_cloop_hpp__
#define __uix_cloop_hpp__

#include "uix.hpp"

#include <functional>

namespace uix {
  class CLoop {
      friend class CApplication;  
    protected:
      int           mCurrTicks  {0};
      CApplication* mApplication;
    public:
      CLoop();
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
      CEventLoop();
    protected:
      void exec() override;
      void tick() override;
  };
  
  class CGameLoop : public CLoop {
      friend class CApplication;
      using TCallback = std::function<void()>;
    protected:
      int mMaxLoops    {10};
      int mTicksPerSec {25};
    protected:
      TCallback* mRead {nullptr};
      TCallback* mTick {nullptr};
      TCallback* mDraw {nullptr};
    public:
      CGameLoop(int=10, int=25);
      CGameLoop(TCallback&& cTick);
      CGameLoop(TCallback&& cTick, TCallback&& cDraw);
      CGameLoop(TCallback&& cTick, TCallback&& cDraw, TCallback&& cRead);
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
