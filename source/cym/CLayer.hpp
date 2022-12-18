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
  };
} // namespace cym

#endif //__cym_clayer_hpp__

// CScreen
  // CLayer[]
    // CTarget

// CONTEXT == CONSOLE
  // CTarget = CGlyphSurface
// CONTEXT = WINDOW
  // CTarget = CPixelSurface
// CONTEXT = OPENGL || DIRECTX || VULKAN
  // CTarget = CTextureSurface