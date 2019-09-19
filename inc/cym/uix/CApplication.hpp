#ifndef __cym_uix_capplication_hpp__
#define __cym_uix_capplication_hpp__

#include "uix.hpp"
#include "CObject.hpp"
#include "CHandler.hpp"

namespace cym { namespace uix {
  class CApplication : public CObject, public CHandler {
    protected:
      using CObject::CObject;
      using CObject::operator=;
    protected:
      static CApplication* sInstance;
      HINSTANCE            mHandle   = {NULL};
      CConsole*            mConsole  = {nullptr};
      bool                 mRunning  = {false};
    public: // ctor
      CApplication(HINSTANCE = ::GetModuleHandle(NULL), int = 0);
      ~CApplication();
    public: // copy
      CApplication(const CApplication&);
    public: // assign
      CApplication& operator =(const CApplication&);
    public: // cast
      explicit operator       HINSTANCE();
      explicit operator const HINSTANCE() const;
    protected:
      bool init();
      bool tick(int=0);
      bool free();
    public:
      bool  exec(int=0);
      bool  quit(int=0);
    public:
      static CApplication* instance();
    protected:
      virtual void onInit();
      virtual void onTick(int=0);
      virtual void onFree();
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
