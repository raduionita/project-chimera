#ifndef __cym_uix_capplication_hpp__
#define __cym_uix_capplication_hpp__

#include "CObject.hpp"
#include "CLoop.hpp"

namespace cym { namespace uix {
  class CApplication : public CObject {
    protected:
      using CObject::CObject;
      using CObject::operator=;
    protected:
      static CApplication* sInstance;
      HINSTANCE            mHandle   = {NULL};
      CConsole*            mConsole  = {nullptr};
      bool                 mRunning  = {false};
      CLoop*               mLoop     = {nullptr};
    public:
      CApplication(HINSTANCE = ::GetModuleHandle(NULL), int = 0);
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
      static CApplication* instance();
    protected:
      virtual void onInit();
      virtual void onTick(long = 0);
      virtual void onExit();
  };  
}}

#define DECLARE_APPLICATION(cls)                                                                                       \
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {                      \
  log::nfo << "   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << log::end;                                \
  auto app   = new cls();                                                                                              \
  INT result = app->exec();                                                                                            \
  delete app;                                                                                                          \
  return result;                                                                                                       \
}                                                                                                                     //

#endif //__cym_uix_capplication_hpp__
