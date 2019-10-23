#ifndef __app_ceditwindow_hpp__
#define __app_ceditwindow_hpp__

#include "app.hpp"
#include "uix/CToplevel.hpp"

namespace app {
  class CEditWindow : public uix::CToplevel {
      friend class CApplication;
      using uix::CToplevel::CToplevel;
    private:
      uix::CSurface*    mSurface;
    public:
      CEditWindow() /*=default*/;
      ~CEditWindow() /*=default*/;
    protected:
      void onInit() override;
      void onFree() override;
  };
}

#endif //__app_ceditwindow_hpp__
