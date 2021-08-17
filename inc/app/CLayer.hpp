#ifndef __app_clayer_hpp__
#define __app_clayer_hpp__

#include "sys/sys.hpp"

#include <list>

namespace app {
  class CLayer {
//     - DEBUG layer (debug info, fps, cpu...)
//     - CONSOLE layer (console/command terminal)
//     - MENU/PAUSE layer  + PANIC layer (error/message boxes)
//     - GUI (/hud) layer
//     - GAME/PLAY/DRAW/MAIN layer => rendering starts w/ the deepest one   
  };
  
  
// @todo: separete what get's rendered:
  // stats (fps)
  // gui (on window menus)
  // tools (gizmo, )
  // scene
  // background (2d games)
}

#endif //__app_clayer_hpp__
