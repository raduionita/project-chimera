#ifndef __cym_uix_capplication_hpp__
#define __cym_uix_capplication_hpp__

#include "CModule.hpp"
#include "CListener.hpp"

namespace cym { namespace uix {
  class CApplication : public CModule, public CListener {
    protected:
      using CModule::CModule;
      using CModule::operator=;
    protected:
      static CApplication* sInstance;
      CConsole*            mConsole  = {nullptr};
      bool                 mRunning  = {false};
    public: // ctor
      CApplication(int = 0);
      ~CApplication();
    protected:
      bool init() override;
      bool tick(int=0);
      bool free() override;
    public:
      bool exec(int=0);
      bool quit(int=0);
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
  log::nfo << "   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << " INIT" << log::end;                     \
  auto app   = new cls();                                                                                              \
  INT result = app->exec();                                                                                            \
  delete app;                                                                                                          \
  log::nfo << "   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << " EXIT" << log::end;                     \
  return result;                                                                                                       \
}                                                                                                                     //

#endif //__cym_uix_capplication_hpp__
