#ifndef __app_capplication_hpp__
#define __app_capplication_hpp__

#include "app/app.hpp"
#include "uix/CApplication.hpp"
#include "app/CLayer.hpp"
#include "sys/TAssociated.hpp"
#include "app/CViewport.hpp"
#include "app/CController.hpp"
#include "app/CTool.hpp"

namespace app {
  class CApplication : public uix::CApplication {
    private:
      
      // app::CMainLayer*
      // app::CGUILayer*
      // app::CMenuLayer*
      // app::CConsoleLayer*
      // app::CDebugLayer*
      
      uix::CButton* mCamS;
      int           mCamA {0};
      
      // app:CEditViewport : uix::CWindow*
      // app:CShowViewport
        // 
      // app:CTestViewport
      // app:CPlayViewport
      // app:CGameViewport
      
      
      
      sys::spo<app::NGrid> mGrid;
    protected:
      virtual void exec() override;
    protected: // app events
      // void onInit()      override;
      // void onFree()      override;
    protected: // loop events
      // void onRead(); // input init
      // void onTick(); // update 
      // void onDraw(); // render
    protected:  
      void onKeydown(uix::CEvent*);
      void onClick(uix::CEvent*);
      void onCommand(uix::CEvent*);
  };
}

#endif //__app_capplication_hpp__
