#ifndef __cym_uix_ccontext_hpp__
#define __cym_uix_ccontext_hpp__

#include "CObject.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>

namespace cym { namespace uix {
  class CContext : public CObject {
    protected:
      friend class CSurface;
      friend class CCanvas;
    public:
      struct SOptions {
        static constexpr int DEFAULT = -1; 
        int  nMajorVersion   = {3};
        int  nMinorVersion   = {2};
        int  nSamples        = {1};
        int  nColorBits      = {32};
        int  nDepthBits      = {24};
        int  nStencilBits    = {8};
        int  nAlphaBits      = {8};
        bool nFlags          = {0};
      };
    protected:
      CWindow* mParent = {nullptr};
      SOptions mOptions = {};
      HWND     mHandle = {NULL};
      HDC      mDC     = {NULL}; // device context
      HGLRC    mRC     = {NULL}; // render context
    public:
      CContext(CWindow* pParent, const SOptions& = {3,2,1,32,24,8,8,0});
      ~CContext();
    protected:
      virtual bool init();
      virtual bool free();
    public:
      bool swap()    const;
      bool current() const;
  };  
}}



#endif //__cym_uix_ccontext_hpp__
