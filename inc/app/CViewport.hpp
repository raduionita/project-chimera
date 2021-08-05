#ifndef __app_cviewport_hpp__
#define __app_cviewport_hpp__

#include "app/app.hpp"

namespace app {
  class CViewport {
    public:
      // mScene
      // mWindow
      // mCamera
  };
  
// @todo: CApplication can have multiple viewports
  // left (ortho), right (ortho), top (ortho), main (perspective), custom (perspective|ortho)
// @todo: viewport has custom rendering options
// @todo: viewport has it's own scene that renders
// @todo: viewport has multiple app::CLayer(s)

// @todo: in CApplication
  // for each viewport
    // use camera
    // use window
    // draw scene
    
// CSelectViewport // preview selected node/entity
// CPlayViewport   // test app
}

#endif //__app_cviewport_hpp__
