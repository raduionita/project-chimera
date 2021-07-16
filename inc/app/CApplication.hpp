#ifndef __app_capplication_hpp__
#define __app_capplication_hpp__

#include "app/app.hpp"
#include "uix/CApplication.hpp"
#include "sys/CLayered.hpp"
#include "sys/TAssociated.hpp"
#include "app/CViewport.hpp"
#include "app/CController.hpp"

namespace app {
  class CApplication : public uix::CApplication {
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
