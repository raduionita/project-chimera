#ifndef __app_ceditwindow_hpp__
#define __app_ceditwindow_hpp__

#include "app/app.hpp"
#include "uix/CFrame.hpp"
#include "uix/CDialog.hpp"

namespace app {
  class CEditWindow : public uix::CFrame {
      friend class CApplication;
      using uix::CFrame::CFrame;
    private:
      uix::CSurface*    mSurface {nullptr};
    public:
      CEditWindow() /*=default*/;
      ~CEditWindow() /*=default*/;
    protected:
      void onInit() override;
      void onFree() override;
  };
}

#endif //__app_ceditwindow_hpp__
