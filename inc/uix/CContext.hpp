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
    public:
      enum EContext : sys::bitfield {
        CONTEXT = 0,
        DUMMY   = 1 << 1,
        INITED  = 1 << 2,
        COMPAT  = 1 << 3,
        CORE    = 1 << 4,
        DEBUG   = 1 << 5,
        STEREO  = 1 << 6,
      };
    protected:
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
        int  nSwapInterval = {2};
        uint nFlags        = {EContext::CONTEXT|EContext::CORE|EContext::DUMMY}; // debug | stereo
      };
    private:
      HWND  mHandle {NULL};
      HDC   mDevice {NULL}; // device context
      HGLRC mRender {NULL}; // render context
    protected:
      CWindow* mCurrent {nullptr};
      SConfig  mConfig  {};
      uint     mState   {0};
    public: 
      CContext(                  const SConfig& = {UIX_CONTEXT_MAJOR,UIX_CONTEXT_MINOR,1,32,24,8,8,1,EContext::CONTEXT|EContext::CORE});
      CContext(CWindow* pParent, const SConfig& = {UIX_CONTEXT_MAJOR,UIX_CONTEXT_MINOR,1,32,24,8,8,1,EContext::CONTEXT|EContext::CORE});
      ~CContext();
    public:
      bool init(CWindow* pWindow);
    protected:
      bool free();
      void bind(CWindow*);
    public:
      inline bool swap()    const { return ::SwapBuffers(mDevice); }
      bool        current(CWindow* = nullptr);
      bool        clear(int = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT) const;
      bool        reset();
      const char* version() const;
      bool        extension(const char*) const;
      void        interval(int) const;
      void        vsync(bool);
    protected:
      static bool error(); 
  };
}

#endif //__uix_ccontext_hpp__
