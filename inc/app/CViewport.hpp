#ifndef __app_cviewport_hpp__
#define __app_cviewport_hpp__

#include "app/app.hpp"
#include "uix/CFrame.hpp"
#include "uix/CSurface.hpp"
#include "uix/CContext.hpp"

namespace app {
  class CViewport {
    public:
    // sys::ptr<cym::CCamera> mCamera
    public:
      CViewport(/*uix::CWindow* pParent, uix::CContext* pContext*/);
      virtual ~CViewport() = default;
    public:
      void setCamera(/*CCamera*/);
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
    
// Edit app
  // CShowViewport // preview selected node/entity
    // debug layer
    // main/draw layer
  // CPlayViewport // new window uses app scene + context + fullscreen & un-paused, doesn't render on the other viewports
    // debug layer
    // info/error layer
    // console layer
    // play/main layer
  // CEditViewport // editor
    // debug layer
    // gui layer (only if active) (on top gizmo & other menu (like camera type)
    // edit/main layer

// Play/Game app
  // CPlayViewport or CGameViewport
    // console layer
    // menu/pause layer
    // gui layer
    // game/main layer
}

#endif //__app_cviewport_hpp__
