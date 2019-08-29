#include "cym/uix/CContext.hpp"
#include "cym/uix/CWindow.hpp"

namespace cym { namespace uix {
  CContext::CContext(CWindow* pParent, const SOptions& sOptions) : mParent{pParent}, mOptions{sOptions}, mHandle{(HWND)(*pParent)} {
    std::cout << "uix::CContext::CContext(CWindow*,SOptions&)::" << this << std::endl;
    init();
  }
  
  CContext::~CContext() {
    std::cout << "uix::CContext::CContext()::" << this << std::endl;
    free();
  }
  
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CContext::init() {
    std::cout << "uix::CContext::init()::" << this << std::endl;
    
    // need dummy window for ogl 4.x
    
    LPTSTR szWndcls = (LPTSTR)(*mParent);
    
    HWND tWnd = ::CreateWindowEx(
      0,                     // dwExStyle
      szWndcls,              // wndcls
      NULL,                  // title
      WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
      0,0,1,1,               // x,y,w,h
      NULL,                  // parent
      NULL,                  // menu
      (HINSTANCE)(*CApplication::getInstance()),
      NULL
    );
    
    HDC tDC = ::GetDC(tWnd);
    
    PFD tPFD;
    tPFD.nSize        = sizeof(PFD);                                                // WORD
    tPFD.nVersion     = 1;                                                          // WORD
    tPFD.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; // DWORD
    tPFD.iPixelType   = PFD_TYPE_RGBA;
    tPFD.cColorBits   = mOptions.nColorBits;
    tPFD.cDepthBits   = mOptions.nDepthBits;
    tPFD.cStencilBits = mOptions.nStencilBits;
    tPFD.cAlphaBits   = mOptions.nAlphaBits;
    
    INT tPFID = ::ChoosePixelFormat(tDC, &tPFD);
    if (tPFID == 0) {
      std::cout << "[CContext] ChoosePixelFormat failed!" << std::endl;
      ::MessageBox(NULL, "[CCanvas] ChoosePixelFormat failed!", "Error", MB_OK);
      return false;
    } else if (::SetPixelFormat(tDC, tPFID, &tPFD) == 0) {
      std::cout << "[CContext] SetPixelFormat failed!" << std::endl;
      ::MessageBox(NULL, "[CContext] SetPixelFormat failed!", "Error", MB_OK);
      return false;
    } 
    
    HGLRC tRC = ::wglCreateContext(tDC);
    if (tRC == 0) {
      std::cout << "[CContext] wglCreateContext failed!" << std::endl;
      ::MessageBox(NULL, "[CContext] wglCreateContext failed!", "Error", MB_OK);
      return false;
    } else if (::wglMakeCurrent(tDC, tRC) == 0) {
      std::cout << "[CContext] wglMakeCurrent failed!" << std::endl;
      ::MessageBox(NULL, "[CContext] wglMakeCurrent failed!", "Error", MB_OK);
      return false;
    }
  
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
    wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
    if (wglChoosePixelFormatARB == nullptr) {
      std::cout << "[CContext] wglChoosePixelFormatARB failed!" << std::endl;
      ::MessageBox(NULL, "[CContext] wglChoosePixelFormatARB failed!", "Error", MB_OK);
      return false;
    }
  
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
    wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
    if (wglCreateContextAttribsARB == nullptr) {
      std::cout << "[CContext] wglCreateContextAttribsARB failed!" << std::endl;
      ::MessageBox(NULL, "[CContext] wglCreateContextAttribsARB failed!", "Error", MB_OK);
      return false;
    }
    
    mDC = ::GetDC(mHandle);
  
    const int aPixelAttrs[] = {
      WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
      WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
      WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
      WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
      WGL_COLOR_BITS_ARB,     mOptions.nColorBits,
      WGL_ALPHA_BITS_ARB,     mOptions.nAlphaBits,
      WGL_DEPTH_BITS_ARB,     mOptions.nDepthBits,
      WGL_STENCIL_BITS_ARB,   mOptions.nStencilBits,
      WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
      WGL_SAMPLES_ARB,        mOptions.nSamples,
      0
    };
    
    int nPFID; UINT nFormats;
    bool bStatus = wglChoosePixelFormatARB(mDC, aPixelAttrs, NULL, 1, &nPFID, &nFormats);
    if (bStatus == false && nFormats == 0) {
      std::cout << "[CCanvas] wglChoosePixelFormatARB failed!" << std::endl;
      ::MessageBox(NULL, "[CCanvas] wglChoosePixelFormatARB failed!", "Error", MB_OK);
      return false;
    }
    
    PFD sPFD;
    ::DescribePixelFormat(mDC, nPFID, sizeof(sPFD), &sPFD);
    ::SetPixelFormat(mDC, nPFID, &sPFD);
    
    const int aContextAttr[] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB, mOptions.nMajorVersion,
      WGL_CONTEXT_MINOR_VERSION_ARB, mOptions.nMinorVersion,
      WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
   // WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
      0
    };
    
    mRC = wglCreateContextAttribsARB(mDC, 0, aContextAttr);
    if (mRC == NULL) {
      std::cout << "[CCanvas] wglCreateContextAttribsARB failed!" << std::endl;
      ::MessageBox(NULL, "[CCanvas] wglCreateContextAttribsARB failed!", "Error", MB_OK);
      return false;
    }
    
    // clear
    ::wglMakeCurrent(NULL,NULL);
    ::wglDeleteContext(tRC);
    ::ReleaseDC(tWnd, tDC);
    ::DestroyWindow(tWnd);
    
    // make current
    if (!::wglMakeCurrent(mDC, mRC)) {
      std::cout << "[CCanvas] wglMakeCurrent failed! " << std::endl;
      ::MessageBox(NULL, "[CCanvas] wglMakeCurrent failed!", "Error", MB_OK);
      return false;
    }
  
    ::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    ::SwapBuffers(mDC);
    
    return true;
  }
  
  bool CContext::free() {
    std::cout << "uix::CContext::free()::" << this << std::endl;
    ::wglMakeCurrent(NULL,NULL);
    mRC && ::wglDeleteContext(mRC);
    mDC && ::ReleaseDC(mHandle, mDC);
    return true;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CContext::swap() const {
    std::cout << "uix::CContext::swap()::" << this << std::endl;
    return ::SwapBuffers(mDC);
  }
  
  bool CContext::current() const {
    std::cout << "uix::CContext::current()::" << this << std::endl;
    return wglMakeCurrent(mDC,mRC);
  }
}}
