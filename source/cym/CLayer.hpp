#ifndef __cym_clayer_hpp__
#define __cym_clayer_hpp__

#include "cym/cym.hpp"

namespace cym {
  class CLayer {
    private:
      cym::CSurface*& mSurface;
      float           mOpacity{1.f};
    public:
      CLayer(cym::CSurface*& pSurface) : mSurface{pSurface} { };
      ~CLayer() = default;
    public:
      bool update(float fElapsed = 0.f) { 

        // todo: render scene

        return true;
      }
  };
} // namespace cym

#endif //__cym_clayer_hpp__

// CLayer
// CRaycastLayer
// CPixelLayer
// CGraphicLayer


// CONTEXT == CONSOLE
  // CTarget = CGlyphSurface
// CONTEXT == WINDOW
  // CTarget = CPixelSurface
// CONTEXT == OPENGL || DIRECTX || VULKAN
  // CTarget = CTextureSurface