#ifndef __app_capplication_hpp__
#define __app_capplication_hpp__

#include "app.hpp"
#include "uix/CApplication.hpp"

namespace app {
  class CApplication : public uix::CApplication {
    public:
      int exec() override;
    protected:
      // void onInit()      override;
      // void onFree()      override;
    protected: // loop events
      // void onRead(); // input read
      // void onTick(); // update 
      // void onDraw(); // render
    protected:  
      void onKeydown(uix::CEvent*);
      void onClick(uix::CEvent*);
      void onCommand(uix::CEvent*);
  };
}

#endif //__app_capplication_hpp__
