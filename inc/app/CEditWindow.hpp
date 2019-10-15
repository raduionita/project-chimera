#ifndef __app_ceditwindow_hpp__
#define __app_ceditwindow_hpp__

#include "app.hpp"
#include "uix/CFrame.hpp"

namespace app {
  class CEditWindow : public uix::CFrame {
      using uix::CFrame::CFrame;
    private:
      uix::CSurface*    mSurface;
    public:
      CEditWindow();
      ~CEditWindow();
    protected:
      void onInit() override;
      void onFree() override;
      void onKeydown(uix::CEvent*);
      void onClick(uix::CEvent*);
      void onCommand(uix::CEvent*);
      void onDraw(uix::CEvent*);
  };
}

#endif //__app_ceditwindow_hpp__
