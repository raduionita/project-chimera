#ifndef __cym_uix_capplication_hpp__
#define __cym_uix_capplication_hpp__

#include "uix.hpp"
#include "CObject.hpp"
#include "CLoop.hpp"

namespace cym { namespace uix {
  class CApplication : public CObject {
    protected:
      static CApplication* sInstance;
      HINSTANCE            mHandle   = {NULL};
      bool                 mRunning  = {false};
      CLoop*               mLoop     = {nullptr};
    public:
      CApplication(HINSTANCE = ::GetModuleHandle(NULL));
      ~CApplication();
      CApplication(const CApplication&);
      CApplication& operator =(const CApplication&);
      explicit operator       HINSTANCE();
      explicit operator const HINSTANCE() const;
    protected:
      bool init();
      bool free();
    public:
      int  exec(int = 0);
      int  quit(int = 0);
    public:
      static CApplication* getInstance();
    protected:
      virtual void onInit();
      virtual void onTick(int = 0);
      virtual void onExit();
  };  
}}

#define DECLARE_APPLICATION(cls)                                                                                       \
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {                      \
  std::cout << "   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << std::endl;                              \
  auto app   = new cls;                                                                                                \
  INT result = app->exec();                                                                                            \
  delete app;                                                                                                          \
  return result;                                                                                                       \
}                                                                                                                     //

#endif //__cym_uix_capplication_hpp__
