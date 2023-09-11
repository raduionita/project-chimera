#ifndef __sys_capplication_hpp__
#define __sys_capplication_hpp__

#include "sys/sys.hpp"
#include "sys/CExecutable.hpp"

namespace sys {
  class CApplication : public CExecutable {
      using super = sys::CExecutable;
    protected:
      static const CApplication* sInstance;
      bool                       mRunning {true}; // TODO: atomic bool
    public:
      CApplication();
      ~CApplication();
    public:
      inline static const CApplication* getInstance() { return sInstance; }
      inline bool isRunning() const { return mRunning; }
    public:
      virtual int  exec() override;
      // init/clean
      virtual bool init();
              bool free();
      // actions
              void loop();
      virtual bool tick(float fElapsed=0.f);
              void quit(int nCode=0);
              bool poll();
      // events
      virtual void onInit();
      virtual void onTick(float=0.f);
      virtual void onFree();
  };
} // namespace sys

#endif //__sys_capplication_hpp__