#ifndef __app_capplication_hpp__
#define __app_capplication_hpp__

#include "app.hpp"
#include "uix/CApplication.hpp"
#include "app/CEditWindow.hpp"

namespace app {
  class CApplication : public uix::CApplication {
    protected:
      app::CEditWindow* mMain;
    protected:
      void onInit()      override;
      void onTick(int=0) override;
      void onFree()      override;
  };
}

#endif //__app_capplication_hpp__
