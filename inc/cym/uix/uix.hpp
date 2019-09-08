#ifndef __cym_uix_hpp__
#define __cym_uix_hpp__

#include "../cym.hpp"
#include "../sys/CLogger.hpp"

#define WIN32_LEAN_AND_MEAN // before <windows.h> exclude unusable stuff
#include <windows.h>
#include <windowsx.h>
#include <windef.h>
#include <wingdi.h>
#include <commctrl.h>

#include <cassert>
#include <iomanip>
#include <atomic>
#include <map>
#include <bitset>
#include <vector>

#define RETURNN(cond)     if(cond)return
#define RETURNV(cond,out) if(cond)return out
#define GET3RDARG(arg0,arg1,arg2,...) arg2
#define CHOOSERETURN(...) GET3RDARG(__VA_ARGS__, RETURNV, RETURNN,) 
#define RETURN(...)       CHOOSERETURN(__VA_ARGS__)(__VA_ARGS__)
#define IF(cond,action)   if(cond)action
#define BREAK(cond)       if(cond)break
#define CONTINUE(cond)    if(cond)continue
#undef  DELETE
#define DELETE(what)      delete what;what = nullptr

#define CM_INIT      (WM_USER + 0x0001) // custom message
#define CM_TABCHANGE (CM_INIT + 0x0001)

namespace cym { namespace uix {
  constexpr int ZERO =  0;
  constexpr int AUTO = -1;
  constexpr int FULL = -1;
  
  class CHandler;
  class CLoop;
  class CDisplay;
  class CObject;
    class CConsole;
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
      class CPopup;         // abstract // toplevel windows
        class CFrame;       // titlebar + borders (opt: statusbar + menubar + toolbar)
          class CSplash;    // spalsh screen // no titlebar, no borders, no buttons, only an image
          class CPreview;   // prevew (like printing)
          class CCanvas;    // ogl|d3d|vlk // no border no titlebar w/ CGLContext similar to CCanvas but only 1 class
        class CDialog;      // modal
          class CMessage;
          class CWizard;
      class CWidget;        // abstract // child windows
        class CPanel;       // empty widget/window
          class CSurface;   // empty widget + context
        class CTitlebar;
        class CMenubar;     // items are CMenu(s)
        class CToolbar;     // items are CWidget(s) | default bottom | holds info
        class CStatusbar;   // items are CWidget(s) | default top | under menubar
        class CImage;
        class CVideo;
        class CLabel;
        class CSeparator;   // CDivider
        class CControl;
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
    operator       RECT()  const;
    operator const RECT()  const;
    operator       SArea() const;
    operator const SArea() const;
  };
  
  struct SArea {
    static constexpr int DEFAULT = -1;
    union {int data[4]; struct {int x, y, w, h;};};
    SArea(int v = DEFAULT) : x(v), y(v), w(v), h(v) { }
    SArea(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) { }
    operator       RECT()  const;
    operator const RECT()  const;
    operator       SRect() const; 
    operator const SRect() const; 
  };
    
  inline SRect::operator       RECT()  const { return RECT{l,t,r,b}; }
  inline SRect::operator const RECT()  const { return RECT{l,t,r,b}; }
  inline SRect::operator       SArea() const { return SArea{l,t,r-l,b-t}; }
  inline SRect::operator const SArea() const { return SArea{l,t,r-l,b-t}; }
    
  inline SArea::operator       RECT()  const { return RECT{x,y,x+w,y+h}; }
  inline SArea::operator const RECT()  const { return RECT{x,y,x+w,y+h}; }
  inline SArea::operator       SRect() const { return SRect{x,y,x+w,y+h}; }
  inline SArea::operator const SRect() const { return SRect{x,y,x+w,y+h}; }
    
  typedef SShape S;
  typedef SPoint P;
  typedef SArea  A;
  typedef SRect  R;
  
  inline std::ostream& operator <<(std::ostream&o, const RECT& r) { return o << "l:" << r.left << " t:" << r.top << " r:" << r.right << " b:" << r.bottom; }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  using TID        = int32_t;
  using TString    = std::string;
  template<typename K, typename V> 
  using TMap       = std::map<K,V>;
  template<typename T>
  using TVector    = std::vector<T>;
    
  using log        = cym::sys::CLogger;
  
  inline TString T(const char* text) { return TString(text); }
  inline TString T(int num)          { return std::to_string(num); }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  enum EState {
    _STATE_   = ZERO,
    PUSHED    = 0b00000001,
    FOCUSED   = 0b00000100,
    CHECKED   = 0b00010000,
    MINIMIZED = 0b00100000,
    MAXIMIZED = 0b01000000,
  };
  
  enum EHint {
    _HINT_     = ZERO,
    CHILD      = 0b00000000000000000000000000000001, // WS_CHILD // stays in parent area, moves w/ the parent (oposite 2 WS_POPUP)
    POPUP      = 0b00000000000000000000000000000010, // WS_POPUP
    BORDER     = 0b00000000000000000000000000000100, // WS_BORDER
    TITLE      = 0b00000000000000000000000000001000, // WS_CAPTION + WS_BORDER
    HSCROLL    = 0b00000000000000000000000000010000,
    VSCROLL    = 0b00000000000000000000000000100000,
    FRAME      = 0b00000000000000000000000001000000, // WS_THICKFRAME // thickframe normal sized frame, does not work w/ ::SetWindowLong
    GROUP      = 0b00000000000000000000000010000000,
    MINBOX     = 0b00000000000000000000000100000000,
    MAXBOX     = 0b00000000000000000000001000000000,
    SYSBOX     = 0b00000000000000000000010000000000|TITLE|MINBOX|MAXBOX, // WS_SYSMENU // icon + maxbox holder + minbox + close
    SIZER      = 0b00000000000000000000100000000000,
    VISIBLE    = 0b00000000000000000001000000000000,
    HIDDEN     = 0b00000000000000000010000000000000,
    DISABLED   = 0b00000000000000000100000000000000,
    NOCLIP     = 0b00000000000000001000000000000000,
#undef ABSOLUTE
    ABSOLUTE   = 0b00000000000000010000000000000000,
#define ABSOLUTE 1
#undef RELATIVE
    RELATIVE   = 0b00000000000000100000000000000000,
#define RELATIVE 2
    LEFT       = 0b00000000000001000000000000000000,
    RIGHT      = 0b00000000000010000000000000000000,
    TOP        = 0b00000000000100000000000000000000,
    BOTTOM     = 0b00000000001000000000000000000000,
    VERTICAL   = 0b00000000010000000000000000000000,
    HORIZONTAL = 0b00000000100000000000000000000000,
    CENTER     = 0b00000001000000000000000000000000,
    PACKED     = 0b00000010000000000000000000000000, // run CWindow::pack() 
    ADJUST     = PACKED,
      
    MINIMIZE   = 0b00000100000000000000000000000000,
    MAXIMIZE   = 0b00001000000000000000000000000000,
    
    AUTOXY     = 0b00010000000000000000000000000000,
    AUTOWH     = 0b00100000000000000000000000000000, // 32bit
  };
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}}

#endif //__cym_uix_hpp__
