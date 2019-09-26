#ifndef __app_capplication_hpp__
#define __app_capplication_hpp__

#define CYM_LOGGER
#define CYM_LOGGER_INFO
#define CYM_LOGGER_COUT

#define UIX_STYLE
#define UIX_STYLE_BACKGROUND_COLOR RGB(33,33,33)

#include "cym/uix/CApplication.hpp"
#include "cym/uix/CEvent.hpp"

namespace app {
  using namespace cym;
  using log = cym::log;
  
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
      void onDraw(uix::CEvent*);
  };
}

#endif //__app_capplication_hpp__
