#ifndef __uix_capplication_hpp__
#define __uix_capplication_hpp__

#include "sys/sys.hpp"

#include "sys/CApplication.hpp"
#include "sys/CException.hpp"
#include "sys/CLogger.hpp"
#include "uix/uix.hpp"
#include "uix/CFrame.hpp"
#include "uix/CConsole.hpp"

namespace uix {
  class CApplication : public sys::CApplication {
      using super = sys::CApplication;
  };

  template<typename T> class TApplication : public CApplication, public T {
      using super = T;
      static_assert(std::is_base_of<CWindow, T>::value, "T must be derived from CWindow");
    public:
      TApplication() : T() { }
      ~TApplication() = default;
  };
} // namespace uix

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

#endif //__uix_capplication_hpp__