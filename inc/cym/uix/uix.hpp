#ifndef __cym_uix_hpp__
#define __cym_uix_hpp__

#define WIN32_LEAN_AND_MEAN // before <windows.h> exclude unusable stuff
#include <windows.h>
#include <windowsx.h>
#include <windef.h>
#include <wingdi.h>
#include <commctrl.h>

#include <cassert>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <atomic>
#include <vector>
#include <map>
#include <chrono>

#define RETURNN(cond)     if(cond)return
#define RETURNV(cond,out) if(cond)return out
#define GET3RDARG(arg0,arg1,arg2,...) arg2
#define CHOOSERETURN(...) GET3RDARG(__VA_ARGS__, RETURNV, RETURNN,) 
#define RETURN(...)       CHOOSERETURN(__VA_ARGS__)(__VA_ARGS__)
#define BREAK(cond)       if(cond)break
#define CONTINUE(cond)    if(cond)continue
#undef  DELETE
#define DELETE(what)      delete what;what = nullptr

#define CM_INIT      (WM_USER + 0x0001) // custom message
#define CM_TABCHANGE (CM_INIT + 0x0001)

#define PFD PIXELFORMATDESCRIPTOR 

namespace cym { namespace uix {
  class CHandler;
  class CLoop;
  class CObject;
    class CModule;
    class CApplication;
    class CContext;         // ogl|d3d|vlk contex
    class CMenu;
    class CTooltip;
    class CStyle;
    class CPainter;
      class CPen;
      class CBrush;
    class CWindow;          // abstract
      class CToplevel;
        class CFrame;       // titlebar + borders (opt: statusbar + menubar + toolbar)
          class CSplash;    // spalsh screen // no titlebar, no borders, no buttons, only an image
          class CPreview;   // prevew (like printing)
          class CCanvas;    // ogl|d3d|vlk // no border no titlebar w/ CGLContext similar to CCanvas but only 1 class
        class CDialog;
          class CMessage;
          class CWizard;        
      class CWidget;
        class CMenubar;     // items are CMenu(s)
        class CToolbar;     // items are CWidget(s) | default bottom | holds info
        class CStatusbar;   // items are CWidget(s) | default top | under menubar
        class CSurface;
        class CImage;
        class CVideo;
        class CLabel;
        class CControl;
          class CScroller;  // scroll bar
          class CButton;
          class CSelect;
          class CInput;
          class CTextarea;
          class CSlider;    // CRange
          class CSpinner;
          class CSearch;    // input + button/icon + search event
    class CLayout;          // CLayout::CItem|SItem
      class CBoxLayout;     // vertical || horizontal
      class CGridLayout;    // how many cells
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  struct SShape { 
    static constexpr int DEFAULT = -1;
    int w, h;
    SShape()      : w(DEFAULT), h(DEFAULT) {} 
    SShape(int v) : w(v),       h(v)       {} 
  };
  
  struct SPoint { 
    static constexpr int DEFAULT = -1;
    int x, y;
    SPoint()      : x(DEFAULT), y(DEFAULT) {} 
    SPoint(int v) : x(v),       y(v)       {} 
  };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  typedef std::string SString;
  
  inline SString T(const char* text) { return SString(text); }
  inline SString T(int num)          { return std::to_string(num); }
  
  template <typename T> inline SString concat(const char* text, T frag) { std::ostringstream os; os << text << frag; return os.str(); } 

  inline int64_t now() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  typedef SShape S;
  typedef SPoint P;
}}

// @here: functions that should have been in win32 

inline int FindPixelFormat(HDC hDC, int nColorBits = 32, int nDepthBits = 24, int nStencilBits = 8) {
  // to evel what we find
  int currMode  = 0;
  int currScore = 0;
  int bestMode  = 0;
  int bestScore = 0;
  
  // temp PFD
  PFD sPFD;
  
  for (currMode = 1; ::DescribePixelFormat(hDC, currMode, sizeof(sPFD), &sPFD) > 0; ++currMode) {
    CONTINUE(!(sPFD.dwFlags & PFD_SUPPORT_OPENGL));                                    // ignore if no opengl
    CONTINUE(!(sPFD.dwFlags & PFD_DRAW_TO_WINDOW));                                    // ignore if no window dra
    CONTINUE((sPFD.iPixelType != PFD_TYPE_RGBA) || (sPFD.dwFlags & PFD_NEED_PALETTE)); // ignore if no RGBA mode
    CONTINUE(!(sPFD.dwFlags & PFD_DOUBLEBUFFER));                                      // ignore if no doublebuffer
    
    // candidate found, evaluate it...
    
    currScore = 0;
    
    if (sPFD.cColorBits >= nColorBits) ++currScore; // color 
    if (sPFD.cColorBits == nColorBits) ++currScore;
  
    if (sPFD.cDepthBits >= nDepthBits) ++currScore; // depth 
    if (sPFD.cDepthBits == nDepthBits) ++currScore; //  
    
    if (sPFD.cStencilBits >= nStencilBits) ++currScore; // stencil 
    if (sPFD.cStencilBits == nStencilBits) ++currScore; //  
    
    if (sPFD.cAlphaBits > 0) ++currScore; // alpha
    
    if (currScore > bestScore) bestScore = currScore; // best score
    if (currScore > bestScore) bestMode  = currMode;  // best mode
  }
  
  return bestScore;
}

inline std::string GetLastErrorString() {
  DWORD errid = ::GetLastError();
  if (errid == 0) return std::string();
  LPSTR buffer = nullptr;
  size_t size = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errid, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, NULL);
  std::string errmsg(buffer, size);
  ::LocalFree(buffer);
  return errmsg;
}

inline void SetDefaultFont(HWND hWnd) {
  ::SendMessage(hWnd, WM_SETFONT, (WPARAM)::GetStockObject(DEFAULT_GUI_FONT), (LPARAM)true);
}

#endif //__cym_uix_hpp__
