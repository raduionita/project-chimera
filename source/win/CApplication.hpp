#ifndef __win_capplication_hpp__
#define __win_capplication_hpp__

#include "win/win.hpp"
#include "sys/CApplication.hpp"

namespace win {
  class CApplication : public sys::CApplication {
      bool mRunning {true};
    public:
      CApplication();
    public:
      int  exec();
    private:
      bool init();
      bool free();

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
  LOGNFO("   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << " INIT");                                     \
  try {                                                                                                                \
    CLS app;                                                                                                           \
    INT result = app.exec();                                                                                           \
    LOGNFO("   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << " EXIT");                                   \
    return result;                                                                                                     \
  } catch (sys::CException& ex) {                                                                                      \
    LOGERR("FATAL! " << ex);                                                                                           \
    return -1;                                                                                                         \
  }                                                                                                                    \
}

#endif //__win_capplication_hpp__