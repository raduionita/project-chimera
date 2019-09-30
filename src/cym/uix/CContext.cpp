#include "cym/uix/CContext.hpp"
#include "cym/uix/CWindow.hpp"

namespace cym::uix {
  CContext::CContext(CWindow* pWindow, const SConfig& sOptions) : mWindow{pWindow}, mConfig{sOptions}, mHandle{(HWND)(*pWindow)} {
    log::nfo << "uix::CContext::CContext(CWindow*,SConfig&)::" << this << log::end;
    init();
  }
  
  CContext::~CContext() {
    log::nfo << "uix::CContext::CContext()::" << this << log::end;
    free();
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CContext::init() {
    log::nfo << "uix::CContext::init()::" << this << log::end;
    
    // need dummy window for ogl 4.x
    
    LPCSTR szClsName = "uix::CContext::DUMMY";
  
    WNDCLASSEX tWndCls = {
      sizeof(WNDCLASSEX),                       // UINT      // cbSize        // struct size  
      CS_HREDRAW|CS_VREDRAW|CS_OWNDC,           // UINT      // style
      ::DefWindowProc,                          // WNDPROC   // lpfnWndProc   // uix::CWidget::proc
      0,                                        // int       // cbClsExtra    // no extra bytes after the window class
      0,                                        // int       // cbWndExtra    // extra bytes to allocate after the win instance 
      (HINSTANCE)(*CApplication::instance()),// HINSTANCE // hInstance     // to identify the dll that loads this module  
      ::LoadIcon(NULL, IDI_APPLICATION),        // HICON     // hIcon
      ::LoadCursor(NULL, IDC_ARROW),            // HCURSOR   // hCursor
      (HBRUSH)(NULL_BRUSH),                     // HBRUSH    // hbrBackground
      NULL,                                     // LPCTSTR   // lpszMenuName  // no menu
      szClsName,                                // LPCTSTR   // lpszClassName
      ::LoadIcon(NULL, IDI_APPLICATION)         // HICON     // hIconSm
    };
    
    if (!::RegisterClassEx(&tWndCls)) {
      log::nfo << "[CContext] ::RegisterClassEx() failed!" << log::end;
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
      log::nfo << "[CContext] ::CreateWindowEx() failed!" << log::end;
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
      log::nfo << "[CContext] ChoosePixelFormat failed!" << log::end;
      ::MessageBox(NULL, "[CCanvas] ::ChoosePixelFormat() failed!", "Error", MB_OK);
      return false;
    } else if (!::SetPixelFormat(tDC, tPFID, &tPFD)) {
      log::nfo << "[CContext] ::SetPixelFormat() failed!" << log::end;
      ::MessageBox(NULL, "[CContext] ::SetPixelFormat() failed!", "Error", MB_OK);
      return false;
    } 
    
    HGLRC tRC = ::wglCreateContext(tDC);
    if (!tRC) {
      log::nfo << "[CContext] ::wglCreateContext() failed!" << log::end;
      ::MessageBox(NULL, "[CContext] ::wglCreateContext() failed!", "Error", MB_OK);
      return false;
    } else if (!::wglMakeCurrent(tDC, tRC)) {
      log::nfo << "[CContext] ::wglMakeCurrent() failed!" << log::end;
      ::MessageBox(NULL, "[CContext] ::wglMakeCurrent() failed!", "Error", MB_OK);
      return false;
    }
  
    DEFINE_WGL_FUNCTION(wglChoosePixelFormatARB);
    if (!wglChoosePixelFormatARB) {
      log::nfo << "[CContext] ::wglChoosePixelFormatARB() failed!" << log::end;
      ::MessageBox(NULL, "[CContext] ::wglChoosePixelFormatARB() failed!", "Error", MB_OK);
      return false;
    }
  
    DEFINE_WGL_FUNCTION(wglCreateContextAttribsARB);
    if (!wglCreateContextAttribsARB) {
      log::nfo << "[CContext] ::wglCreateContextAttribsARB() failed!" << log::end;
      ::MessageBox(NULL, "[CContext] ::wglCreateContextAttribsARB() failed!", "Error", MB_OK);
      return false;
    }
    
    mDC = ::GetDC(mHandle);
  
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
      0
    };
    
    int nPFID; UINT nFormats;
    bool bStatus = wglChoosePixelFormatARB(mDC, aPixelAttrs, NULL, 1, &nPFID, &nFormats);
    if (bStatus == false && nFormats == 0) {
      log::nfo << "[CCanvas] ::wglChoosePixelFormatARB() failed!" << log::end;
      ::MessageBox(NULL, "[CCanvas] ::wglChoosePixelFormatARB() failed!", "Error", MB_OK);
      return false;
    }
  
    PIXELFORMATDESCRIPTOR sPFD;
    ::DescribePixelFormat(mDC, nPFID, sizeof(sPFD), &sPFD);
    ::SetPixelFormat(mDC, nPFID, &sPFD);
    
    const int aContextAttr[] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB, mConfig.nMajorVersion,
      WGL_CONTEXT_MINOR_VERSION_ARB, mConfig.nMinorVersion,
      WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
   // WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
   // WGL_STEREO_ARB, GL_TRUE,
      0
    };
    
    mRC = wglCreateContextAttribsARB(mDC, 0, aContextAttr);
    if (!mRC) {
      log::nfo << "[CCanvas] ::wglCreateContextAttribsARB() failed!" << log::end;
      ::MessageBox(NULL, "[CCanvas] ::wglCreateContextAttribsARB() failed!", "Error", MB_OK);
      return false;
    }
    
    // clear
    ::wglMakeCurrent(NULL,NULL);
    ::wglDeleteContext(tRC);
    ::ReleaseDC(tWnd, tDC);
    ::DestroyWindow(tWnd);
    ::UnregisterClass(szClsName, (HINSTANCE)(*CApplication::instance()));
    
    return current();
    
    // ::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    // swap();
  }
  
  bool CContext::free() {
    log::nfo << "uix::CContext::free()::" << this << log::end;
    ::wglMakeCurrent(NULL,NULL);
    mRC && ::wglDeleteContext(mRC);
    mDC && ::ReleaseDC(mHandle, mDC);
    return true;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CContext::swap() const {
    log::nfo << "uix::CContext::swap()::" << this << log::end;
    if (!::SwapBuffers(mDC)) {
      log::nfo << "[CContext] ::SwapBuffers() failed! " << log::end;
      ::MessageBox(NULL, "[CContext] ::SwapBuffers() failed!", "Error", MB_OK);
      return false;
    }
    return true;
  }
  
  bool CContext::current() const {
    log::nfo << "uix::CContext::current()::" << this << log::end;
    if (!::wglMakeCurrent(mDC, mRC)) {
      log::nfo << "[CContext] ::wglMakeCurrent() failed! " << log::end;
      ::MessageBox(NULL, "[CContext] ::wglMakeCurrent() failed!", "Error", MB_OK);
      return false;
    }
    return true;
  }
  
  bool CContext::clear(int nBit/*=GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT*/) const {
    ::glClearColor(0.f,0.f,0.f,0.f);
    ::glClear(nBit);
    return true;
  }
  
  bool CContext::reset() const {
    return current() && clear() && swap();
  }
}
