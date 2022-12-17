#ifndef __win_capplication_hpp__
#define __win_capplication_hpp__

#include "win/win.hpp"
#include "sys/CApplication.hpp"

namespace win {
  class CApplication : public sys::CApplication {
    protected:
      static CApplication* sInstance;
      bool                 mRunning {true}; // TODO: atomic bool
    public:
      CApplication();
    public:
      static inline CApplication* getInstance() { return sInstance; }
      inline bool isRunning() const { return mRunning; }
    public:
      int  exec();
    private:
      // setup/cleanup
      bool init();
      bool free();
      // actions
      void loop();
      bool exit();
      bool tick();
      bool poll();
      // events
      void onInit();
      void onTick(int=0);
      void onFree();
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