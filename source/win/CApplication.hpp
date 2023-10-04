#ifndef __win_capplication_hpp__
#define __win_capplication_hpp__

#include "sys/sys.hpp"

#ifdef PLATFORM_WINDOWS

#include "sys/CApplication.hpp"
#include "sys/CException.hpp"
#include "sys/CLogger.hpp"
#include "win/win.hpp"
#include "win/CFrame.hpp"
#include "win/CConsole.hpp"

namespace win {
  class CApplication : public sys::CApplication {
      using super = sys::CApplication;
  };

  template<typename T> class TApplication : public CApplication, public T {
      using super = T;
      static_assert(std::is_base_of<CWindow, T>::value, "T must be derived from CWindow");
    public:
      TApplication() : T() { }
      ~TApplication() = default;
    public:
      virtual bool poll() override;
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

#endif // PLATFORM_WINDOWS

#endif //__win_capplication_hpp__