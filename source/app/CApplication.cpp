#include "app/CApplication.hpp"
#include "uix/CFrame.hpp"

namespace app {
  // ctor
  // CApplication::CApplication() {
  //   LOGDBG("app::CApplication::CApplication()");
  // } 
  // // dtor
  // CApplication::~CApplication() {
  //   LOGDBG("app::CApplication::~CApplication()");
  // }

  void CApplication::onInit() {
    LOGDBG("app::CApplication::onInit()");

    // play|full
      // console
        // win::CConsole* pConsole = new win::CConsole(name, size, font);
        // cym::CScreen* pScreen = new cym::CScreen{pConsole};

      // window
        // win::CWindow* pWindow = new win::CWindow;
        // cym::CScreen* pScreen = new cym::CScreen{pWindow};

      // opengl
        // win::CCanvas* pCanvas = new win::CCanvas;
        // cym::CScreen* pScreen = new cym::CScreen{pCanvas}

    // edit
      // console
        // N/A

      // CApplication : TApplication<CFrame>
        // uix::CSection
          // cym::TScreen // parent=section
            // cym::CLayer // scene
            // cym::CLayer // gui
            // 
        // uix:CPanel // buttons


  }

  void CApplication::onTick(float fElapsed) {
    LOGDBG("app::CApplication::onTick()::" << fElapsed);

    quit(0);
  }
} // namespace app
