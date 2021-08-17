#ifndef __uix_capplication_hpp__
#define __uix_capplication_hpp__

#include "uix/uix.hpp"
#include "uix/CModule.hpp"
#include "uix/CListener.hpp"
#include "uix/CConsole.hpp"
#include "uix/CLoop.hpp"

namespace uix { 
  template<typename T> class TApplication : public T { };
  
  class CApplication : public CModule, public CListener {
      class SState {
          // @todo: application state
      };
    protected:
      using CModule::CModule;
      using CModule::operator=;
    protected:
      static CApplication* sInstance;
      sys::spo<CConsole>   mConsole  {nullptr};
      bool                 mRunning  {false};
      CStyle*              mStyle    {nullptr};
      sys::spo<CLoop>      mLoop     {nullptr};
    public: // ctor
      CApplication(int=0);
      ~CApplication();
    public: // set/get
      CStyle* style();
      bool    style(CStyle*);
    protected: // events  
      bool         init() override;
      virtual void exec();
      virtual void loop();
      bool         free() override;
      virtual bool poll() final;
    public:
      virtual int  load() final;
              bool tick(float=0.f);
              bool quit(int=0);
              bool exit(int=0);
              bool runs() const;
              void runs(bool);
              bool isRunning() const;
              void isRunning(bool);
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
  SYS_LOG_NFO("   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << " INIT");                                \
  try {                                                                                                                \
    CLS app;                                                                                                           \
    INT result = app.load();                                                                                           \
    SYS_LOG_NFO("   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << " EXIT");                              \
    return result;                                                                                                     \
  } catch (sys::CException& ex) {                                                                                      \
    SYS_LOG_ERR("FATAL! " << ex);                                                                                      \
    return -1;                                                                                                         \
  }                                                                                                                    \
}                                                                                                                     //

#endif //__uix_capplication_hpp__
