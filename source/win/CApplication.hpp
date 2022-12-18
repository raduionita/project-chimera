#ifndef __win_capplication_hpp__
#define __win_capplication_hpp__

#include "sys/CApplication.hpp"
#include "sys/CException.hpp"
#include "sys/CLogger.hpp"
#include "win/win.hpp"
#include "win/CFrame.hpp"
#include "win/CConsole.hpp"

namespace win {
  class CApplication : public sys::CApplication {
      using super = sys::CApplication;
    protected:
      static CApplication* sInstance;
      bool                 mRunning {true}; // TODO: atomic bool
    public:
      CApplication();
      ~CApplication();
    public:
      inline static CApplication* getInstance() { return sInstance; }
      inline bool isRunning() const { return mRunning; }
    public:
      // start
      virtual int  exec();
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

  template<typename T> class TApplication : public CApplication, public T {
      using super = T;
      static_assert(std::is_base_of<CWindow, T>::value, "T must be derived from CWindow");
    public:
      TApplication() : T() { }
      ~TApplication() = default;
  };
} // namespace win

#undef DECLARE_APPLICATION
#define DECLARE_APPLICATION(CLS)                                                                                       \
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {                      \
  LOGTAG("   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)");                                                               \
  LOGNFO("::" << hInstance << " INIT");                                                                                \
  try {                                                                                                                \
    CLS app;                                                                                                           \
    INT result = app.exec();                                                                                           \
    LOGNFO("::" << hInstance << " EXIT");                                                                              \
    return result;                                                                                                     \
  } catch (sys::CException& ex) {                                                                                      \
    LOGERR("::FATAL! " << ex);                                                                                         \
    return -1;                                                                                                         \
  }                                                                                                                    \
}

#endif //__win_capplication_hpp__