#ifndef __app_capplication_hpp__
#define __app_capplication_hpp__

#define CYM_LOGGER 1
#define CYM_LOGGER_INFO
#define CYM_LOGGER_COUT

#define UIX_STYLE 1
#define UIX_STYLE_BACKGROUND_COLOR RGB(33,33,33)

#define UIX_CONTEXT_MAJOR 3
#define UIX_CONTEXT_MINOR 2

#include "uix/CApplication.hpp"

namespace app {
  using log = sys::log;
  
  class CApplication : public uix::CApplication {
    protected:
      uix::CFrame*   mFrame;
      uix::CSurface* mSurface;
    protected:
      void onInit()      override;
      void onTick(int=0) override;
      void onFree()      override;
    protected:
      void onKeydown(uix::CEvent*);
      void onClick(uix::CEvent*);
      void onCommand(uix::CEvent*);
      void onDraw(uix::CEvent*);
  };
}

#endif //__app_capplication_hpp__
