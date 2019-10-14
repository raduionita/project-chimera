#ifndef __app_ceditwindow_hpp__
#define __app_ceditwindow_hpp__

#include "app.hpp"
#include "uix/CFrame.hpp"

namespace app {
  class CEditWindow : public uix::CFrame {
    private:
      uix::CSurface*    mSurface;
    protected:
      void onInit();
      void onFree();
      void onKeydown(uix::CEvent*);
      void onClick(uix::CEvent*);
      void onCommand(uix::CEvent*);
      void onDraw(uix::CEvent*);
  };
}

#endif //__app_ceditwindow_hpp__
