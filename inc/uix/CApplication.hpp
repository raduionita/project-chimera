#ifndef __uix_capplication_hpp__
#define __uix_capplication_hpp__

#include "uix.hpp"
#include "uix/CModule.hpp"
#include "uix/CListener.hpp"

namespace uix { 
  template<typename T>
  class TApplication : public T {
      
  };
  
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
      CLoop*               mLoop     {nullptr};
    public: // ctor
      CApplication(int=0);
      ~CApplication();
    public: // set/get
      CStyle* style();
      bool    style(CStyle*);
    protected: // events  
      bool           init() override;
      virtual CLoop* loop();
      bool           free() override;
      virtual bool   poll() final;
    public:
      bool         tick(int=0);
      virtual int  exec();
              bool quit(int=0);
              bool runs() const;
              void runs(bool);
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
  try {                                                                                                                \
    CLS app;                                                                                                           \
    INT result = app.exec();                                                                                           \
    sys::log::nfo << "   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << " EXIT" << sys::log::end;         \
    return result;                                                                                                     \
  } catch (sys::CException& ex) {                                                                                      \
    sys::log::err << "FATAL! " << ex << sys::log::end;                                                                 \
    return -1;                                                                                                         \
  }                                                                                                                    \
}                                                                                                                     //

#endif //__uix_capplication_hpp__
