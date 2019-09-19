#ifndef __cym_uix_ccontext_hpp__
#define __cym_uix_ccontext_hpp__

#include "CObject.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>

typedef HGLRC(WINAPI * wglCreateContextAttribsARB_t) (HDC,HGLRC,CONST INT*);
typedef BOOL (WINAPI * wglChoosePixelFormatARB_t)    (HDC,CONST INT*,CONST FLOAT*,UINT,INT*,UINT*);

#define DEFINE_WGL_FUNCTION(name) name##_t name = reinterpret_cast<name##_t>(::wglGetProcAddress(#name))

#define PFD 

namespace cym { namespace uix {
  class CContext : public CObject {
    protected:
    using CObject::CObject;
    using CObject::operator=;
    
    protected:
    friend class CSurface;
    friend class CCanvas;
    
    public:
    struct SConfig {
      static constexpr int DEFAULT = -1; 
      int  nMajorVersion = {3};
      int  nMinorVersion = {2};
      int  nSamples      = {1};
      BYTE nColorBits    = {32};
      BYTE nDepthBits    = {24};
      BYTE nStencilBits  = {8};
      BYTE nAlphaBits    = {8};
      int  nFlags        = {0}; // debug | stereo
    };
    
    protected:
    CWindow* mWindow  = {nullptr};
    SConfig  mConfig = {};
    HWND     mHandle  = {NULL};
    HDC      mDC      = {NULL}; // device context
    HGLRC    mRC      = {NULL}; // render context
    
    public: 
    CContext(CWindow* pParent, const SConfig& = {3, 2, 1, 32, 24, 8, 8, 0});
    ~CContext();
    
    protected:
    virtual bool init();
    virtual bool free();
    
    public:
    bool swap()    const;
    bool current() const;
    bool clear(int = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT) const;
    bool reset() const;
  };  
}}



#endif //__cym_uix_ccontext_hpp__
