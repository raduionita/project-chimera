#ifndef __uix_hpp__
#define __uix_hpp__

#include "sys/sys.hpp"
#include "sys/CLogger.hpp"
#include "sys/CException.hpp"
#include "sys/CSingleton.hpp"

// #include "./SArea.hpp"


// @todo: move this to CWindow
#define WIN32_LEAN_AND_MEAN // before <windows.h> exclude unusable stuff
#include <windows.h>
#include <windowsx.h>
#include <windef.h>
#include <wingdi.h>
#include <commctrl.h>

#include <cassert>
#include <iomanip>
#include <atomic>
#include <list>     // for (auto&& v : list)
#include <bitset>
#include <tuple>

#define RETURNCN(cond)      if(cond)return
#define RETURNCV(cond,val)  if(cond)return val
#define GET3RDARG(arg0,arg1,arg2,...) arg2
#define CHOOSERETURN(...)   GET3RDARG(__VA_ARGS__, RETURNCV, RETURNCN,)
#define RETURN(...)         CHOOSERETURN(__VA_ARGS__)(__VA_ARGS__)
#define IF(cond,action)     if(cond)action
#define WHILE(cond,action)  while(cond)action
#define BREAK(cond)         if(cond)break
#define CONTINUE(cond)      if(cond)continue
#undef  DELETE
#define DELETE(what)        delete what;what=nullptr
#define NEW(what)           new (_NORMAL_BLOCK,__FILE__,__LINE__)
#define ASSERT(cond)        assert(cond)

#define CM_INIT       (WM_USER       + 0x0001) // custom message
#define CM_FREE       (CM_INIT       + 0x0001) // custom message
#define CM_TABCHANGE  (CM_FREE       + 0x0001)
#define CM_STATE      (CM_TABCHANGE  + 0x0001)
#define CM_FULLSCREEN (CM_STATE      + 0x0001)
#define CM_WINDOWED   (CM_FULLSCREEN + 0x0001)
#define CM_REPAINT    (CM_WINDOWED   + 0x0001) // triggers invalidate rect + WM_PAINT
#define CM_CONTEXT    (CM_REPAINT    + 0x0001) 

#define CTX_NONE    0
#define CTX_OPENGL  1
#define CTX_VULKAN  2
#define CTX_DIRECTX 3

#ifndef UIX_PEN
#define UIX_PEN NULL_PEN
#endif

#ifndef UIX_STYLE
#define UIX_STYLE false
#endif//UIX_STYLE

#ifndef UIX_STYLE_BACKGROUND
#define UIX_STYLE_BACKGROUND       NULL_BRUSH
#endif//UIX_STYLE_BACKGROUND

#ifndef UIX_STYLE_BACKGROUND_COLOR
#define UIX_STYLE_BACKGROUND_COLOR RGB( 0, 0, 0)
#endif//UIX_STYLE_BACKGROUND_COLOR

#ifndef UIX_STYLE_BORDER
#define UIX_STYLE_BORDER           NULL_PEN
#endif//UIX_STYLE_BORDER

#ifndef UIX_STYLE_BORDER_COLOR
#define UIX_STYLE_BORDER_COLOR     RGB(90,90,90)
#endif//UIX_STYLE_BORDER_COLOR

#ifndef UIX_STYLE_BORDER_SIZE
#define UIX_STYLE_BORDER_SIZE      1
#endif//UIX_STYLE_BORDER_SIZE

#ifndef UIX_STYLE_BORDER_TYPE
#define UIX_STYLE_BORDER_TYPE      EStyle::SOLID
#endif//UIX_STYLE_BORDER_TYPE

#ifndef UIX_WINDOW
#define UIX_WINDOW false
#endif//UIX_WINDOW

#ifndef UIX_WINDOW_AREA_X
#define UIX_WINDOW_AREA_X CW_USEDEFAULT
#endif//UIX_WINDOW_AREA_X

#ifndef UIX_WINDOW_AREA_Y
#define UIX_WINDOW_AREA_Y CW_USEDEFAULT
#endif//UIX_WINDOW_AREA_Y

#ifndef UIX_WINDOW_AREA_W
#define UIX_WINDOW_AREA_W CW_USEDEFAULT
#endif//UIX_WINDOW_AREA_W

#ifndef UIX_WINDOW_AREA_H
#define UIX_WINDOW_AREA_H CW_USEDEFAULT
#endif//UIX_WINDOW_AREA_H

// @here: functions that should have been in win32 

struct STATE {
  DWORD dwStyle   {0};
  DWORD dwExStyle {0};
  RECT  rc        {0};
};

inline INT FindPixelFormat(HDC hDC, int nColorBits = 32, int nDepthBits = 24, int nStencilBits = 8) {
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

inline const char* GetLastErrorString() {
  DWORD errid = ::GetLastError();
  if (errid == 0) return "";
  LPSTR buffer = nullptr;
  const DWORD size = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errid, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, NULL);
  std::string errmsg(buffer, size);
  ::LocalFree(buffer);
  return errmsg.c_str();
}

inline STATE SwapWindowState(HWND hWnd) {
  assert(hWnd != NULL && "HWND is NULL");
  assert(::IsWindow(hWnd) != FALSE && "HWND is not a WINDOW");
  
  static std::map<HWND, STATE> states;
  
  STATE curr;
  curr.dwStyle   = static_cast<DWORD>(::GetWindowLong(hWnd, GWL_STYLE));
  curr.dwExStyle = static_cast<DWORD>(::GetWindowLong(hWnd, GWL_EXSTYLE));
  ::GetClientRect(hWnd, &curr.rc);
  
  auto it = states.find(hWnd);
  if (states.size() == 0 || it == states.end()) {    // not found // insert
    states.insert(std::pair<HWND,STATE>(hWnd, curr));
  } else {                                           // found // swap
    // read prev
    STATE  temp{it->second};
    STATE& prev{it->second};
    // store
    prev.dwStyle   = curr.dwStyle;
    prev.dwExStyle = curr.dwExStyle;
    prev.rc        = curr.rc;
    // return
    curr.dwStyle   = temp.dwStyle;
    curr.dwExStyle = temp.dwExStyle;
    curr.rc        = temp.rc;
  }
  
  return curr;
}

inline STATE GetWindowState(HWND hWnd) {
  STATE curr;
  curr.dwStyle   = static_cast<DWORD>(::GetWindowLong(hWnd, GWL_STYLE));
  curr.dwExStyle = static_cast<DWORD>(::GetWindowLong(hWnd, GWL_EXSTYLE));
  ::GetClientRect(hWnd, &curr.rc);
  return curr;
}

inline VOID SetDefaultFont(HWND hWnd) {
  ::SendMessage(hWnd, WM_SETFONT, (WPARAM)::GetStockObject(DEFAULT_GUI_FONT), (LPARAM)true);
}

inline WINBOOL HandleMessage(MSG* pMSG, const unsigned int kMax = 5, const unsigned int kTPS = 25) {
  static DWORD              nCurTicks;
  static DWORD              nNxtTicks;
  static const unsigned int kJumpTime{1000 / kTPS};
  static unsigned int       iLoop;
  
  nCurTicks = ::GetTickCount();
  nNxtTicks = nCurTicks + kJumpTime;
  iLoop     = 0;
  
  while (nCurTicks < nNxtTicks && iLoop < kMax) {
    if (::PeekMessage(pMSG, NULL, 0, 0, PM_REMOVE)) {
      if (WM_QUIT == pMSG->message) {
        return FALSE;
        break;
      } else {
        ::TranslateMessage(pMSG);
        ::DispatchMessage(pMSG);
      }
      nCurTicks = ::GetTickCount();
    }
    iLoop++;
  }
  
  return TRUE;
}

namespace uix {
  constexpr int ZERO =  0;
  constexpr int AUTO = -1;
  constexpr int FULL = -1;

  constexpr bool STYLE                  {UIX_STYLE};
  constexpr auto STYLE_BACKGROUND_COLOR {UIX_STYLE_BACKGROUND_COLOR};
  constexpr auto STYLE_BORDER_COLOR     {UIX_STYLE_BORDER_COLOR};
    
  // @todo: #ifdef set something in the app from here // like set styles
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  using log    = sys::log;
  
  using byte   = sys::byte;
  using ubyte  = sys::ubyte;
  using tiny   = sys::tiny;
  using utiny  = sys::utiny;
  using ushort = sys::ushort;
  using uint   = sys::uint;
  
  using CString                  = sys::CString;
  template<typename V> using CSet                 = sys::CSet<V>;
  template<typename K, typename V> using CMap               = sys::CMap<K,V>;
  template<typename V> using CVector              = sys::CVector<V>;
  template<typename V, std::size_t S> using CArray = sys::CArray<V,S>;
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  class CListener;
  class CDisplay;
  class CEvent;
  class CRender;
  class CLoop;
  class CObject;
    class CConsole;
    class CModule;
    class CApplication;
    class CContext;         // ogl|d3d|vlk contex
    class CMenu;
    class CTooltip;
    class CStyle;
    class CPainter;
    template <typename T> class CGdio;         // graphics device interface object
      class CBitmap;
      class CBrush;
      class CPen;
      class CPalette;
      class CFont;
      class CCursor;
      class CIcon;
    class CWindow;          // abstract
      class CPopup;         // abstract // toplevel windows
        class CFrame;       // titlebar + borders (opt: statusbar + menubar + toolbar)
          class CToplevel;  // main app that will kill the app when closed
          class CSplash;    // spalsh screen // no titlebar, no borders, no buttons, only an image
          class CPreview;   // prevew (like printing)
          class CCanvas;    // ogl|d3d|vlk // no border no titlebar w/ CGLContext similar to CCanvas but only 1 class
        class CDialog;      // modal
          class CMessage;
          class CWizard;
      class CWidget;        // abstract // child windows
        // class CSection;
        class CPanel;     // empty widget/window
          class CSurface;   // empty widget + context
        class CTitlebar;
        class CMenubar;     // items are CMenu(s)
        class CToolbar;     // items are CWidget(s) | default bottom | holds info
        class CStatusbar;   // items are CWidget(s) | default top | under menubar
        class CImage;
        class CVideo;
        class CLabel;
        class CSeparator;   // CDivider
        class CControl;     // abstract
          class CScroller;  // scroll bar
          class CButton;
          class CSwitch;
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
  
  struct SRect;
  struct SArea;
  
  struct SShape { 
    static constexpr int DEFAULT = -1;
    int w, h;
    SShape(int v = DEFAULT) : w(v), h(v) {} 
  };
  
  struct SPoint { 
    static constexpr int DEFAULT = -1;
    int x, y;
    SPoint(int v = DEFAULT) : x(v), y(v) {} 
  };
    
  struct SRect {
    static constexpr int DEFAULT = -1;
    union {int data[4]; struct {int l, t, r, b;}; struct {int left, top, right, bottom;};};
    SRect(int v = DEFAULT) : l(v), t(v), r(v), b(v) { }
    SRect(int l, int t, int r, int b) : l(l), t(t), r(r), b(b) { }
    operator       RECT();
    operator const RECT()  const;
    operator       SArea();
    operator const SArea() const;
  };
  
  struct SArea {
    static constexpr int DEFAULT = -1;
    union {int data[4]; struct {int x, y, w, h;};};
    SArea(int v = DEFAULT) : x(v), y(v), w(v), h(v) { }
    SArea(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) { }
    operator       RECT();
    operator const RECT()  const;
    operator       SRect(); 
    operator const SRect() const; 
  };
  
  struct SColor {
    static constexpr int DEFAULT = 0;
    union { COLORREF rgb; struct { BYTE r; BYTE g; BYTE b; BYTE a; };};
    SColor(COLORREF rgb = DEFAULT) : rgb(rgb) { }
    SColor(BYTE r, BYTE g, BYTE b, BYTE a = DEFAULT) : rgb(RGB(r, g, b)) { }
    operator       COLORREF();
    operator const COLORREF() const;
  };
    
  inline SRect::operator       RECT()        { return RECT{l,t,r,b}; }
  inline SRect::operator const RECT()  const { return RECT{l,t,r,b}; }
  inline SRect::operator       SArea()       { return SArea{l,t,r-l,b-t}; }
  inline SRect::operator const SArea() const { return SArea{l,t,r-l,b-t}; }
    
  inline SArea::operator       RECT()        { return RECT{x,y,x+w,y+h}; }
  inline SArea::operator const RECT()  const { return RECT{x,y,x+w,y+h}; }
  inline SArea::operator       SRect()       { return SRect{x,y,x+w,y+h}; }
  inline SArea::operator const SRect() const { return SRect{x,y,x+w,y+h}; }
  
  inline SColor::operator       COLORREF()       { return rgb; }
  inline SColor::operator const COLORREF() const { return rgb; }
    
  typedef SShape S;
  typedef SPoint P;
  typedef SArea  A;
  typedef SRect  R;
  typedef SColor C;
  
  inline std::ostream& operator <<(std::ostream& o, const RECT& r) { return o << "l:" << r.left << " t:" << r.top << " r:" << r.right << " b:" << r.bottom; }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  inline sys::CString T(int num)          { return std::to_string(num); }
  inline sys::CString T(const char* text) { return sys::CString(text); }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  enum class EState : sys::bitfield {
    EMPTY      = ZERO,
    PUSHED     = 0b00000000'00000001,
    RELEASED   = 0b00000000'00000010,
    FOCUSED    = 0b00000000'00000100,
    BLURRED    = 0b00000000'00001000,
    CHECKED    = 0b00000000'00010000,
    MINIMIZED  = 0b00000000'00100000,
    MAXIMIZED  = 0b00000000'01000000,
    FULLSCREEN = 0b00000000'10000000,
    PAINTING   = 0b00000001'00000000, 
    CLICKED    = 0b00000010'00000000, 
    DBLCLICKED = 0b00000100'00000000, 
    DISABLE    = 0b00001000'00000000, 
  };
  
  inline int operator |(EState lhs, EState rhs) { return static_cast<int>(lhs) | static_cast<int>(rhs); }
  inline int operator |(uint   lhs, EState rhs) { return lhs                   | static_cast<int>(rhs); }
  inline int operator &(EState lhs, EState rhs) { return static_cast<int>(lhs) & static_cast<int>(rhs); }
  inline int operator &(uint   lhs, EState rhs) { return lhs                   & static_cast<int>(rhs); }
  inline int operator ~(EState rhs)             { return ~(static_cast<int>(rhs)); }
  
  enum EWindow : sys::bitfield {
    _HINT_     = ZERO,
    CHILD      = 0b00000000'00000000'00000000'00000001, // WS_CHILD // stays in parent area, moves w/ the parent (oposite 2 WS_POPUP)
    POPUP      = 0b00000000'00000000'00000000'00000010, // WS_POPUP
    BORDER     = 0b00000000'00000000'00000000'00000100, // WS_BORDER
    TITLE      = 0b00000000'00000000'00000000'00001000, // WS_CAPTION + WS_BORDER
    HSCROLL    = 0b00000000'00000000'00000000'00010000,
    VSCROLL    = 0b00000000'00000000'00000000'00100000,
    FRAME      = 0b00000000'00000000'00000000'01000000, // WS_THICKFRAME // thickframe normal sized frame, does not work w/ ::SetWindowLong
    GROUP      = 0b00000000'00000000'00000000'10000000,
    MINBOX     = 0b00000000'00000000'00000001'00000000,
    MAXBOX     = 0b00000000'00000000'00000010'00000000,
    SYSBOX     = 0b00000000'00000000'00000100'00000000|TITLE|MINBOX|MAXBOX, // WS_SYSMENU // icon + maxbox holder + minbox + close
    SIZER      = 0b00000000'00000000'00001000'00000000,
    VISIBLE    = 0b00000000'00000000'00010000'00000000,
    HIDDEN     = 0b00000000'00000000'00100000'00000000,
    DISABLED   = 0b00000000'00000000'01000000'00000000,
    NOCLIP     = 0b00000000'00000000'10000000'00000000,
#undef ABSOLUTE
    ABSOLUTE   = 0b00000000'00000001'00000000'00000000,
#define ABSOLUTE 1
#undef RELATIVE
    RELATIVE   = 0b00000000'00000010'00000000'00000000,
#define RELATIVE 2
    LEFT       = 0b00000000'00000100'00000000'00000000,
    RIGHT      = 0b00000000'00001000'00000000'00000000,
    TOP        = 0b00000000'00010000'00000000'00000000,
    BOTTOM     = 0b00000000'00100000'00000000'00000000,
    VERTICAL   = 0b00000000'01000000'00000000'00000000,
    HORIZONTAL = 0b00000000'10000000'00000000'00000000,
    CENTER     = 0b00000001'00000000'00000000'00000000,
    PACKED     = 0b00000010'00000000'00000000'00000000, // run CWindow::pack() 
    ADJUST     = PACKED,
    
    MINIMIZE   = 0b00000100'00000000'00000000'00000000,
    MAXIMIZE   = 0b00001000'00000000'00000000'00000000,
    
    AUTOXY     = 0b00010000'00000000'00000000'00000000,
    AUTOWH     = 0b00100000'00000000'00000000'00000000,
    
    FULLSCREEN = 0b01000000'00000000'00000000'00000000,
    LAYERED    = 0b10000000'00000000'00000000'00000000,
  };
  
  enum class EFullscreen : sys::bitfield {
    EMPTY        = ZERO,
    WINDOWED     = 0b00000000,
    FULLSCREEN   = 0b00000001,
    CURSOR       = 0b00000010,
    MONITOR      = 0b00000100,
    GAMING       = FULLSCREEN|CURSOR,
  };
  
  inline int operator |(EFullscreen lhs, EFullscreen rhs) { return static_cast<int>(lhs) | static_cast<int>(rhs); }
  inline int operator |(int         lhs, EFullscreen rhs) { return lhs                   | static_cast<int>(rhs); }
  inline int operator &(EFullscreen lhs, EFullscreen rhs) { return static_cast<int>(lhs) & static_cast<int>(rhs); }
  inline int operator &(int         lhs, EFullscreen rhs) { return lhs                   & static_cast<int>(rhs); }
  inline int operator ~(EFullscreen rhs)                  { return ~(static_cast<int>(rhs)); }
  
  enum class EMouse : int {
    EMPTY      = ZERO,
    LBUTTON    = MK_LBUTTON,  //  2
    RBUTTON    = MK_RBUTTON,  //  2
    SHIFT      = MK_SHIFT,    //  4
    CONTROL    = MK_CONTROL,  //  8
    MBUTTON    = MK_MBUTTON,  // 10
    X1BUTTON   = MK_XBUTTON1, // 20
    X2BUTTON   = MK_XBUTTON2  // 40
  };
  
  inline int operator |(EMouse lhs, EMouse rhs)      { return static_cast<int>(lhs) | static_cast<int>(rhs); }
  inline int operator |(int         lhs, EMouse rhs) { return lhs                   | static_cast<int>(rhs); }
  inline int operator &(EMouse lhs, EMouse rhs)      { return static_cast<int>(lhs) & static_cast<int>(rhs); }
  inline int operator &(int         lhs, EMouse rhs) { return lhs                   & static_cast<int>(rhs); }
  inline int operator ~(EMouse rhs)                  { return ~(static_cast<int>(rhs)); }
  
  enum class EEvent : int {
    EMPTY = ZERO,
    CLOSE = 1,
    QUIT  = 2,
    KEYDOWN = 3,
    KEYUP = 4,
    KEYPRESS = 5, // keyup + keydown
    MOVE = 6,
    MOVING = 7,
    RESIZE = 8, SIZE = RESIZE,
    SIZING = 9,
    FOCUS = 10,
    UNFOCUS = 11, BLUR = UNFOCUS,
    LBDOWN = 12, LBUTTONDOWN = LBDOWN, CLICK = LBDOWN, LCLICK = LBDOWN,
    LBUP = 13, LBUTTONUP = LBUP,
    RBDOWN = 14, RBUTTONDOWN = RBDOWN, RCLICK = RBDOWN,
    RBUP = 15, RBUTTONUP = RBUP,
    DBLCLICK,
    PAINT, DRAW = PAINT,
    SHOW,
    HIDE,
    COMMAND,
  };
  
  enum class ELayout : sys::bitfield {
    EMPTY      = ZERO,
    LEFT       = 0b00000000'00000001,
    RIGHT      = 0b00000000'00000010,
    TOP        = 0b00000000'00000100,
    BOTTOM     = 0b00000000'00001000,
    VERTICAL   = 0b00000000'00010000,
    HORIZONTAL = 0b00000000'00100000,
    ADJUST     = 0b00000000'01000000,
    CENTER     = 0b00000000'10000000,
  };
  
  inline int operator |(ELayout lhs, ELayout rhs) { return static_cast<int>(lhs) | static_cast<int>(rhs); }
  inline int operator |(int     lhs, ELayout rhs) { return lhs                   | static_cast<int>(rhs); }
  inline int operator &(ELayout lhs, ELayout rhs) { return static_cast<int>(lhs) & static_cast<int>(rhs); }
  inline int operator &(int     lhs, ELayout rhs) { return lhs                   & static_cast<int>(rhs); }
  inline int operator ~(ELayout rhs)              { return ~(static_cast<int>(rhs)); }
  
  enum class EStyle : sys::bitfield { // 2byte
    NONE        = ZERO,
    SOLID       = 0b00000000'00000001,
    DASH        = 0b00000000'00000010,
    WINDOW      = 0b00100000'00000000,
    APPLICATION = 0b01100000'00000000,
  };
  
  inline int operator |(EStyle lhs, EStyle rhs) { return static_cast<int>(lhs) | static_cast<int>(rhs); }
  inline int operator |(int    lhs, EStyle rhs) { return lhs                   | static_cast<int>(rhs); }
  inline int operator &(EStyle lhs, EStyle rhs) { return static_cast<int>(lhs) & static_cast<int>(rhs); }
  inline int operator &(int    lhs, EStyle rhs) { return lhs                   & static_cast<int>(rhs); }
  inline int operator ~(EStyle rhs)             { return ~(static_cast<int>(rhs)); }
}

#endif //__uix_hpp__
