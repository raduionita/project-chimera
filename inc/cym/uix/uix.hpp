#ifndef __cym_uix_hpp__
#define __cym_uix_hpp__

#include "../cym.hpp"
#include "../CLogger.hpp"
#include "../CString.hpp"
#include "../CException.hpp"
#include "../CSingleton.hpp"

// #include "./SArea.hpp"


// @todo: move this to CWindow
#define WIN32_LEAN_AND_MEAN // before <windows.h> exclude unusable stuff
#include <windows.h>
#include <windowsx.h>
#include <windef.h>
#include <wingdi.h>
#include <commctrl.h>

#include "../fix/msw.hpp"

#include <cassert>
#include <iomanip>
#include <atomic>
#include <map>      // for (const auto& [k,v] : map)
#include <set>
#include <list>     // for (auto&& v : list)
#include <bitset>
#include <vector>
#include <array>
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

#define CM_INIT       (WM_USER       + 0x0001) // custom message
#define CM_TABCHANGE  (CM_INIT       + 0x0001)
#define CM_STATE      (CM_TABCHANGE  + 0x0001)
#define CM_FULLSCREEN (CM_STATE      + 0x0001)
#define CM_WINDOWED   (CM_FULLSCREEN + 0x0001)
#define CM_REPAINT    (CM_WINDOWED   + 0x0001) // triggers invalidate rect + WM_PAINT

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

namespace cym::uix {
  constexpr int ZERO =  0;
  constexpr int AUTO = -1;
  constexpr int FULL = -1;

  constexpr bool STYLE                  {UIX_STYLE};
  constexpr auto STYLE_BACKGROUND_COLOR {UIX_STYLE_BACKGROUND_COLOR};
  constexpr auto STYLE_BORDER_COLOR     {UIX_STYLE_BORDER_COLOR};
    
  // @todo: #ifdef set something in the app from here // like set styles

  class CListener;
  class CDisplay;
  class CEvent;
  class CRender;
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
  
  template<typename V>
  using CSet       = std::set<V>;
  template<typename K, typename V> 
  using CMap       = std::map<K,V>;
  template<typename V>
  using CVector    = std::vector<V>;
  template<typename V, std::size_t S>
  using CArray     = std::array<V,S>;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  enum class EState : int {
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
  
  enum EWindow : int {
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
    AUTOWH     = 0b00100000000000000000000000000000,
    
    FULLSCREEN = 0b01000000000000000000000000000000,
    LAYERED    = 0b1000000000000000000000000000000, // 32bit // @todo...
  };
  
  enum class EFullscreen : int {
    EMPTY        = ZERO,
    WINDOWED     = 0b000,
    FULLSCREEN   = 0b001,
    CURSOR       = 0b010,
    MONITOR      = 0b100,
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
  
  enum class ELayout : short {
    EMPTY      = ZERO,
    LEFT       = 0b0000000000000001,
    RIGHT      = 0b0000000000000010,
    TOP        = 0b0000000000000100,
    BOTTOM     = 0b0000000000001000,
    VERTICAL   = 0b0000000000010000,
    HORIZONTAL = 0b0000000000100000,
    ADJUST     = 0b0000000001000000,
    CENTER     = 0b0000000010000000,
  };
  
  inline int operator |(ELayout lhs, ELayout rhs) { return static_cast<int>(lhs) | static_cast<int>(rhs); }
  inline int operator |(int     lhs, ELayout rhs) { return lhs                   | static_cast<int>(rhs); }
  inline int operator &(ELayout lhs, ELayout rhs) { return static_cast<int>(lhs) & static_cast<int>(rhs); }
  inline int operator &(int     lhs, ELayout rhs) { return lhs                   & static_cast<int>(rhs); }
  inline int operator ~(ELayout rhs)              { return ~(static_cast<int>(rhs)); }
  
  enum class EStyle : short { // 2byte
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
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  using log = cym::log;
}

#endif //__cym_uix_hpp__
