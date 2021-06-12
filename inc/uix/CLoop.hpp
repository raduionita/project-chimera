#ifndef __uix_cloop_hpp__
#define __uix_cloop_hpp__

#include "uix.hpp"

#include <functional>

namespace uix {
  class CLoop {
      friend class CApplication;  
    protected:
      CApplication* mApplication;
    public:
      CLoop();
      virtual ~CLoop();
    protected:
      virtual void init();
      virtual void done();
      virtual void loop() { };
      virtual void tick(float) { };
  };
  
  class CEventLoop : public CLoop {
      friend class CApplication;
    public:
      CEventLoop();
    protected:
      void loop() override;
      void tick(float) override;
  };
  
  class CGameLoop : public CLoop {
      friend class CApplication;
      using FRead = std::function<void()>;
      using FTick = std::function<void(float)>;
      using FDraw = std::function<void()>;
    protected:
      int mMaxLoops    {10};
      int mTicksPerSec {25};
    protected:
      FRead mRead;
      FTick mTick;
      FDraw mDraw;
    public:
      CGameLoop(int=10, int=25);
      CGameLoop(FTick&& cTick);
      CGameLoop(FTick&& cTick, FDraw&& cDraw);
      CGameLoop(FTick&& cTick, FDraw&& cDraw, FRead&& cRead);
      ~CGameLoop();
    protected: // override
      void loop()      override;
      void tick(float) override;
      void read();
      void draw();
    public:
      void tick(FTick&&);
      void draw(FDraw&&);
      void read(FRead&&);
  };
}

#endif //__uix_cloop_hpp__
