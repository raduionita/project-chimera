#include "uix/CContext.hpp"
#include "uix/CWindow.hpp"

#include <windows.h>
#include <GL/wglext.h>

namespace uix {
  CContext::CContext(const SConfig& sOptions) : mConfig{sOptions} {
    CYM_LOG_NFO("uix::CContext::CContext(SConfig&)::" << this);
  }
  
  CContext::CContext(CWindow* pWindow, const SConfig& sOptions) : mConfig{sOptions} {
    CYM_LOG_NFO("uix::CContext::CContext(CWindow*,SConfig&)::" << this);
    bind(pWindow);
  }
  
  CContext::~CContext() {
    CYM_LOG_NFO("uix::CContext::CContext()::" << this);
    CContext::free();
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CContext::init(CWindow* pWindow) {
    CYM_LOG_NFO("uix::CContext::init()::" << this << " CONFIG: v" << mConfig.nMajorVersion << "." << mConfig.nMinorVersion);
    
    RETURN((mState & EContext::INITED),true);
    
    mCurrent = pWindow;
    
    mHandle = (HWND)(*mCurrent);
    
    LPCSTR szClsName = "uix::CContext::DUMMY"; // need dummy window for ogl 4.x
  
    WNDCLASSEX tWndCls = {
      sizeof(WNDCLASSEX),                       // UINT      // cbSize        // struct size  
      CS_HREDRAW|CS_VREDRAW|CS_OWNDC,           // UINT      // style
      ::DefWindowProc,                          // WNDPROC   // lpfnWndProc   // uix::CWidget::proc
      0,                                        // int       // cbClsExtra    // no extra bytes after the window class
      0,                                        // int       // cbWndExtra    // extra bytes to allocate after the win getSingleton 
      (HINSTANCE)(*CApplication::instance()),// HINSTANCE // hInstance     // to identify the dll that loads this module  
      ::LoadIcon(NULL, IDI_APPLICATION),        // HICON     // hIcon
      ::LoadCursor(NULL, IDC_ARROW),            // HCURSOR   // hCursor
      (HBRUSH)(NULL_BRUSH),                     // HBRUSH    // hbrBackground
      NULL,                                     // LPCTSTR   // lpszMenuName  // no menu
      szClsName,                                // LPCTSTR   // lpszClassName
      ::LoadIcon(NULL, IDI_APPLICATION)         // HICON     // hIconSm
    };
    
    if (!::RegisterClassEx(&tWndCls)) {
      CYM_LOG_NFO("[CContext] ::RegisterClassEx() failed!");
      ::MessageBox(NULL, "[CContext] ::RegisterClassEx() failed!", "ERROR", MB_OK);
      return false;
    }
    
    HWND tWnd = ::CreateWindowEx(
      0,                     // dwExStyle
      szClsName,             // wndcls
      NULL,                  // title
      WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
      0,0,1,1,               // x,y,w,h
      NULL,                  // parent
      NULL,                  // menu
      (HINSTANCE)(*CApplication::instance()),
      NULL
    );
  
    if (!tWnd) {
      ::MessageBox(NULL, "[CContext] ::CreateWindowEx() failed!", "ERROR", MB_OK);
      CYM_LOG_NFO("[CContext] ::CreateWindowEx() failed!");
      
      ::UnregisterClass(szClsName, HINSTANCE(*CApplication::instance()));
      
      return false;
    }
    
    HDC tDC = ::GetDC(tWnd);
  
    PIXELFORMATDESCRIPTOR tPFD = {
      .nSize        = sizeof(PIXELFORMATDESCRIPTOR),                              // WORD
      .nVersion     = 1,                                                          // WORD
      .dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // DWORD
      .iPixelType   = PFD_TYPE_RGBA,
      .cColorBits   = mConfig.nColorBits,
      .cAlphaBits   = mConfig.nAlphaBits,
      .cDepthBits   = mConfig.nDepthBits,
      .cStencilBits = mConfig.nStencilBits,
    };
    
    INT tPFID = ::ChoosePixelFormat(tDC, &tPFD);
    if (!tPFID) {
      CYM_LOG_NFO("[CContext] ChoosePixelFormat failed!");
      ::MessageBox(NULL, "[CContext] ::ChoosePixelFormat() failed!", "Error", MB_OK);
      
      ::DestroyWindow(tWnd);
      ::UnregisterClass(szClsName, HINSTANCE(*CApplication::instance()));
      
      return false;
    } 
    
    if (!::SetPixelFormat(tDC, tPFID, &tPFD)) {
      CYM_LOG_NFO("[CContext] ::SetPixelFormat() failed!");
      ::MessageBox(NULL, "[CContext] ::SetPixelFormat() failed!", "Error", MB_OK);
      
      ::DestroyWindow(tWnd);
      ::UnregisterClass(szClsName, HINSTANCE(*CApplication::instance()));
      
      return false;
    } 
    
    HGLRC tRC = ::wglCreateContext(tDC);
    if (!tRC) {
      CYM_LOG_NFO("[CContext] ::wglCreateContext() failed!");
      ::MessageBox(NULL, "[CContext] ::wglCreateContext() failed!", "Error", MB_OK);
      
      ::DestroyWindow(tWnd);
      ::UnregisterClass(szClsName, HINSTANCE(*CApplication::instance()));
      
      return false;
    } 
    
    if (!::wglMakeCurrent(tDC, tRC)) {
      CYM_LOG_NFO("[CContext] ::wglMakeCurrent() failed!");
      ::MessageBox(NULL, "[CContext] ::wglMakeCurrent() failed!", "Error", MB_OK);
      
      ::ReleaseDC(tWnd, tDC);
      ::wglDeleteContext(tRC);
      ::DestroyWindow(tWnd);
      ::UnregisterClass(szClsName, HINSTANCE(*CApplication::instance()));
      
      return false;
    }
    
    typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC)    (HDC,CONST INT*,CONST FLOAT*,UINT,INT*,UINT*);
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(::wglGetProcAddress("wglChoosePixelFormatARB"));
    if (!wglChoosePixelFormatARB) {
      CYM_LOG_NFO("[CContext] ::wglChoosePixelFormatARB() failed!");
      ::MessageBox(NULL, "[CContext] ::wglChoosePixelFormatARB() failed!", "Error", MB_OK);
      
      ::ReleaseDC(tWnd, tDC);
      ::wglDeleteContext(tRC);
      ::DestroyWindow(tWnd);
      ::UnregisterClass(szClsName, HINSTANCE(*CApplication::instance()));
      
      return false;
    }
    
    typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC,HGLRC,CONST INT*);
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(::wglGetProcAddress("wglCreateContextAttribsARB"));
    if (!wglCreateContextAttribsARB) {
      CYM_LOG_NFO("[CContext] ::wglCreateContextAttribsARB() not found!");
      ::MessageBox(NULL, "[CContext] ::wglCreateContextAttribsARB() not found!", "Error", MB_OK);
      
      ::ReleaseDC(tWnd, tDC);
      ::wglDeleteContext(tRC);
      ::DestroyWindow(tWnd);
      ::UnregisterClass(szClsName, HINSTANCE(*CApplication::instance()));
      
      return false;
    }
  
    mDevice      = ::GetDC(mHandle);
    
    const int aPixelAttrs[] = {
      WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
      WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
      WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
      WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
      WGL_COLOR_BITS_ARB,     mConfig.nColorBits,
      WGL_ALPHA_BITS_ARB,     mConfig.nAlphaBits,
      WGL_DEPTH_BITS_ARB,     mConfig.nDepthBits,
      WGL_STENCIL_BITS_ARB,   mConfig.nStencilBits,
      WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
      WGL_SAMPLES_ARB,        mConfig.nSamples,
      // WGL_STEREO_ARB,         mConfig.nFlags & EContext::STEREO ? GL_TRUE : GL_FALSE, 
      GL_NONE,
    };
    
    int nPFID; UINT nFormats;
    bool bStatus = wglChoosePixelFormatARB(mDevice, aPixelAttrs, NULL, 1, &nPFID, &nFormats);
    if (bStatus == false && nFormats == 0) {
      CYM_LOG_NFO("[CContext] ::wglChoosePixelFormatARB() failed!");
      ::MessageBox(NULL, "[CContext] ::wglChoosePixelFormatARB() failed!", "Error", MB_OK);
      
      ::ReleaseDC(tWnd, tDC);
      ::wglDeleteContext(tRC);
      ::DestroyWindow(tWnd);
      ::UnregisterClass(szClsName, HINSTANCE(*CApplication::instance()));
      
      return false;
    }
  
    PIXELFORMATDESCRIPTOR sPFD;
    ::DescribePixelFormat(mDevice, nPFID, sizeof(sPFD), &sPFD);
    ::SetPixelFormat(mDevice, nPFID, &sPFD);
    
    int nMajor, nMinor;
    if (!::glVersion(nMajor,nMinor)) {
      CYM_LOG_NFO("[CContext] ::glVersion() failed!");
      ::MessageBox(NULL, "[CContext] ::glVersion() failed!", "Error", MB_OK);
      
      ::ReleaseDC(tWnd, tDC);
      ::wglDeleteContext(tRC);
      ::DestroyWindow(tWnd);
      ::UnregisterClass(szClsName, HINSTANCE(*CApplication::instance()));
      
      ::ReleaseDC(mHandle, mDevice);
    }
    
    if (mConfig.nMajorVersion == AUTO || mConfig.nMinorVersion == AUTO) {
      mConfig.nMajorVersion = nMajor;
      mConfig.nMinorVersion = nMinor;
    }
    
    const int aContextAttr[] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB, mConfig.nMajorVersion,
      WGL_CONTEXT_MINOR_VERSION_ARB, mConfig.nMinorVersion,
      WGL_CONTEXT_PROFILE_MASK_ARB,  mConfig.nFlags & EContext::CORE ? WGL_CONTEXT_CORE_PROFILE_BIT_ARB : WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, 
      WGL_CONTEXT_FLAGS_ARB, mConfig.nFlags & EContext::DEBUG ? WGL_CONTEXT_DEBUG_BIT_ARB : GL_FALSE,
   // WGL_STEREO_ARB, mConfig.nFlags & EContext::STEREO ? GL_TRUE : GL_FALSE,
      GL_NONE,
    };
  
    mRender = wglCreateContextAttribsARB(mDevice, 0, aContextAttr);
    if (!mRender) {
      CYM_LOG_NFO("[CContext] ::wglCreateContextAttribsARB() failed!");
      ::MessageBox(NULL, "[CContext] ::wglCreateContextAttribsARB() failed!", "Error", MB_OK);
      
      ::ReleaseDC(tWnd, tDC);
      ::wglDeleteContext(tRC);
      ::DestroyWindow(tWnd);
      ::UnregisterClass(szClsName, HINSTANCE(*CApplication::instance()));
      
      ::ReleaseDC(mHandle, mDevice);
  
      return false;
    }
    
    // cleanup
    ::wglMakeCurrent(NULL,NULL);
    ::wglDeleteContext(tRC);
    ::ReleaseDC(tWnd, tDC);
    ::DestroyWindow(tWnd);
    ::UnregisterClass(szClsName, HINSTANCE(*CApplication::instance()));
  
    current();
        
    if (!::glLoad(mConfig.nMajorVersion, mConfig.nMinorVersion)) {
      CYM_LOG_NFO("[CContext] cym::init() failed!");
      ::MessageBox(NULL, "[CContext] cym::init() failed!", "Error", MB_OK);
      
      ::wglMakeCurrent(NULL,NULL);
      ::wglDeleteContext(mRender);
      ::ReleaseDC(mHandle, mDevice);
      
      return false;
    }
  
    ::SendMessage(mHandle, CM_CONTEXT, WPARAM(CTX_OPENGL), MAKELPARAM(mConfig.nMajorVersion,mConfig.nMinorVersion));
    
    interval(mConfig.nSwapInterval);
    
    return (mState |= EContext::INITED);
  }
  
  bool CContext::free() {
    CYM_LOG_NFO("uix::CContext::free()::" << this);
    ::wglMakeCurrent(NULL,NULL);
    ::wglDeleteContext(mRender);
    ::ReleaseDC(mHandle, mDevice);
    return true;
  }
  
  void CContext::bind(CWindow* pCurrent) {
    if (pCurrent != nullptr && pCurrent != mCurrent) {
      log::dbg << "uix::CContext::bind(CWindow*)::" << this << log::end;
      mCurrent = pCurrent;
      mHandle  = (HWND)(*mCurrent);
      mDevice  = ::GetDC(mHandle);
      // ::SetFocus(mHandle);
      // SetForegroundWindow(mHandle); 
      // SetActiveWindow(mHandle); 
      // SetWindowPos(mHandle, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE  | SWP_NOSIZE);
    }
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CContext::current(CWindow* pCurrent/*=nullptr*/) {
    log::dbg << "uix::CContext::current(CWindow*)::" << this << log::end;
    CContext::bind(pCurrent);
    if (!::wglMakeCurrent(mDevice, mRender)) {
      CYM_LOG_NFO("[CContext] ::wglMakeCurrent() failed! ");
      ::MessageBox(NULL, "[CContext] ::wglMakeCurrent() failed!", "Error", MB_OK);
      return false;
    }
    return true;
  }
  
  bool CContext::clear(int nBit/*=GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT*/) const {
    GLCALL(::glClearColor(0.f,0.f,0.f,0.f));
    GLCALL(::glClear(nBit));
    ::glClearError();
    return true;
  }
  
  bool CContext::reset() {
    return current() && clear() && swap();
  }
  
  bool CContext::extension(const char* ext) const {
    static PFNWGLGETEXTENSIONSSTRINGEXTPROC wglGetExtensionsStringEXT = reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGEXTPROC>(::wglGetProcAddress("wglGetExtensionsStringEXT"));
    return ::strstr(wglGetExtensionsStringEXT(), ext) == NULL;
  }
  
  void CContext::interval(int intv) const {
    if (extension("WGL_EXT_swap_control_tear")) {
      static PFNWGLSWAPINTERVALEXTPROC    wglSwapIntervalEXT    = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(::wglGetProcAddress("wglSwapIntervalEXT"));
      static PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT = reinterpret_cast<PFNWGLGETSWAPINTERVALEXTPROC>(::wglGetProcAddress("wglGetSwapIntervalEXT"));
      if (!wglGetSwapIntervalEXT) {
        CYM_LOG_NFO("[CContext] ::wglGetSwapIntervalEXT() failed!");
        ::MessageBox(NULL, "[CContext] ::wglGetSwapIntervalEXT() failed!", "Error", MB_OK);
      }
      if (!wglSwapIntervalEXT) {
        CYM_LOG_NFO("[CContext] ::wglSwapIntervalEXT() failed!");
        ::MessageBox(NULL, "[CContext] ::wglSwapIntervalEXT() failed!", "Error", MB_OK);
      } else {
        wglSwapIntervalEXT(intv);
      }
    } else {
      log::wrn << "[CContext] WGL_EXT_swap_control_tear not supported!" << log::end;
    }
  }
  
  void CContext::vsync(bool state) {
    interval(state?1:0);
  } 
  
  const char* CContext::version() const { return reinterpret_cast<const char*>(::glGetString(GL_VERSION)); }
}
