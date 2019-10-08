#ifndef __uix_capplication_hpp__
#define __uix_capplication_hpp__

#include "CModule.hpp"
#include "CListener.hpp"

namespace uix {
  class CApplication : public CModule, public CListener {
      class SState {
          // @todo: application state
      };
    protected:
      using CModule::CModule;
      using CModule::operator=;
    protected:
      static CApplication* sInstance;
      CConsole*            mConsole  {nullptr};
      bool                 mRunning  {false};
      CStyle*              mStyle    {nullptr};
    public: // ctor
      CApplication(int=0);
      ~CApplication();
    public: // set/get
      CStyle* style();
      bool    style(CStyle*);
    protected: // events  
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
}

#define DECLARE_APPLICATION(CLS)                                                                                       \
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {                      \
  sys::log::nfo << "   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << " INIT" << sys::log::end;           \
  auto app = new CLS;                                                                                                  \
  INT result = app->exec();                                                                                            \
  delete app;                                                                                                          \
  sys::log::nfo << "   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << " EXIT" << sys::log::end;           \
  return result;                                                                                                       \
}                                                                                                                     //

#endif //__uix_capplication_hpp__
