#ifndef __cym_msw_hpp__
#define __cym_msw_hpp__

#include "../../cym.hpp"

#define WIN32_LEAN_AND_MEAN // before <windows.h> exclude unusable stuff
#include <windows.h>
#include <windowsx.h>
#include <windef.h>
#include <wingdi.h>
#include <commctrl.h>

#include <string>

namespace cym::uix { namespace msw {
 
  
  
}}


// @here: functions that should have been in win32 

inline int FindPixelFormat(HDC hDC, int nColorBits = 32, int nDepthBits = 24, int nStencilBits = 8) {
  // to evel what we find
  int currMode  = 0;
  int currScore = 0;
  int bestMode  = 0;
  int bestScore = 0;
  
  // temp PFD
  PIXELFORMATDESCRIPTOR sPFD;
  
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
  const DWORD size = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errid, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, NULL);
  std::string errmsg(buffer, size);
  ::LocalFree(buffer);
  return errmsg;
}

inline void SetDefaultFont(HWND hWnd) {
  ::SendMessage(hWnd, WM_SETFONT, (WPARAM)::GetStockObject(DEFAULT_GUI_FONT), (LPARAM)true);
}

#endif //__cym_msw_hpp__
