#ifndef __app_hpp__
#define __app_hpp__

#define CYM_LOGGER 1
#define CYM_LOGGER_INFO
#define CYM_LOGGER_COUT

#define UIX_STYLE 1
#define UIX_STYLE_BACKGROUND_COLOR RGB(33,33,33)

#define UIX_CONTEXT_MAJOR 3
#define UIX_CONTEXT_MINOR 2

#include "uix/uix.hpp"

namespace app {
  using log = sys::log;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CApplication;
  class CEditWindow;
  class CGameWindow;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif //__app_hpp__
