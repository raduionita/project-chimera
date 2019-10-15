#ifndef __uix_ccontext_hpp__
#define __uix_ccontext_hpp__

#include "uix.hpp"
#include "CObject.hpp"

#include "glc/glc.hpp"

#ifndef UIX_CONTEXT_MAJOR 
#define UIX_CONTEXT_MAJOR -1
#endif//UIX_CONTEXT_MAJOR

#ifndef UIX_CONTEXT_MINOR 
#define UIX_CONTEXT_MINOR -1
#endif//UIX_CONTEXT_MINOR

namespace uix {
  class CContext : public CObject {
    protected:
      using CObject::CObject;
      using CObject::operator=;
    protected:
      friend class CSurface;
      friend class CCanvas;
      friend class CRender;
    public:
      struct SConfig {
        static constexpr int DEFAULT = -1; 
        int  nMajorVersion = {UIX_CONTEXT_MAJOR}; // AUTO
        int  nMinorVersion = {UIX_CONTEXT_MINOR}; // AUTO
        int  nSamples      = {1};
        BYTE nColorBits    = {32};
        BYTE nDepthBits    = {24};
        BYTE nStencilBits  = {8};
        BYTE nAlphaBits    = {8};
        int  nFlags        = {0}; // debug | stereo
      };
    protected:
      CWindow* mWindow {nullptr};
      SConfig  mConfig {};
      HWND     mHandle {NULL};
      HDC      mDC     {NULL}; // device context
      HGLRC    mRC     {NULL}; // render context
    public: 
      CContext(CWindow* pParent, const SConfig& = {UIX_CONTEXT_MAJOR,UIX_CONTEXT_MINOR,1,32,24,8,8,0});
      ~CContext();
    private:
      bool init();
      bool free();
    public:
      bool        swap()    const;
      bool        current() const;
      bool        clear(int = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT) const;
      bool        reset() const;
      const char* version() const;
    protected:
      static bool error(); 
  };
}

#endif //__uix_ccontext_hpp__
