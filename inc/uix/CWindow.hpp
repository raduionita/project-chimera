#ifndef __uix_cwindow_hpp__
#define __uix_cwindow_hpp__

#include "uix/uix.hpp"
#include "uix/CObject.hpp"
#include "uix/CListener.hpp"
#include "uix/CApplication.hpp"
#include "uix/CStyle.hpp"

#ifdef UIX_PLATFORM_WINDOWS
  #include "win/CWindow.hpp"
  #define UIX_WINDOW win::CWindow
#else
  #define UIX_WINDOW
#endif

namespace uix {  // acme { gui { win, unx, osx } }
  class CWindow : public CObject, public CListener {
      friend class CLayout;
      friend class CWidget;
      friend class CPopup;
    protected:
      using CObject::CObject;
      using CObject::operator=;
      typedef CObject super;
      static constexpr int WINDOW = EWindow::AUTOXY|EWindow::AUTOWH; // @todo: rename this to HINTS or WINDOW or CONFIG
    protected:
      CApplication*         mApplication {CApplication::instance()};
      HWND                  mHandle      {NULL};
      CLayout*              mLayout      {nullptr};
      CWindow*              mParent      {nullptr};
      uint                  mState       {ZERO};
      CStyle*               mStyle       {nullptr};
      uint                  mHints       {ZERO};
      sys::CString          mTitle;
      SArea                 mArea;
      sys::vector<CWindow*> mChildren;
    private: // ctor
      CWindow() = default;
    public: // ctor
      ~CWindow() /*=default*/;
    public: // cast
      explicit operator       HWND();
      explicit operator const HWND() const;
      explicit operator       HDC();
      explicit operator const HDC() const;
    protected:
      virtual bool           init(CWindow* = nullptr, const CString& = "", const SArea& = AUTO, uint = CWindow::WINDOW);
      virtual bool           free();
      virtual inline CString name() const final { return sys::concat("uix::CWindow::", mId); };
    protected: // events
      virtual void onInit();
      virtual void onFree();
    public: // actions
      bool            move(int, int);
      bool            size(int, int);
      SSize           size() const;
      SMove           move() const;
      bool            area(const SArea&);
      SArea           area() const;
      bool            rect(const SRect&);
      SRect           rect() const;
      bool            center();
      SRect           adjust();
      virtual bool    show(uint=1);
      bool            hide(uint=1);
      bool            focus(uint=1);
      bool            pack();
      bool            minimize();
      bool            maximize();
      virtual bool    fullscreen(int=ZERO);
      bool            close();
    public: // chages
      inline bool     hint(EWindow eWindow) const { return mHints & eWindow; }
      STATE           state() const;
      auto            parent() const -> decltype(mParent);
      bool            assign(CWindow*);
      bool            remove(CWindow*);
      auto            children() const -> decltype(mChildren);
      auto            siblings() const -> decltype(mChildren);
      bool            title(const CString&);
      CString         title() const;
      virtual bool    style(CStyle*);
      virtual CStyle* style();
      CLayout*        layout() const;
      CLayout*        layout(CLayout*);
    protected:
      static CWindow*         find(const CString&);
      static CWindow*         find(HWND);
      static LRESULT CALLBACK proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  }; 
}

// @todo: this should be the base

// __MINGW32__  // mingw-32
// __MINGW64__  // mingw-64
// __GNUC__     // gcc (mingw uses gcc)

// __i386__     // cpu arch
// __x86_64__   // 64bit
// __arm__

// __WIN32__   // win32
// __WIN64__   // win64 (implies __WIN32__)
// __linux__   // linux and linux derived (like droid)
// __ANDROID__ // android (implies linux) 
// __APPLE__   // macos & ios

#if defined(__WIN32__)
// class CWindowUIX
// # include "uix/msc/CWindow.hpp"
// # define CWindow CWindowMSW
#elif defined(__APPLE__)
// mac/ios stuff
#elif defined(__linux__)
// unix/linux/android stuff
#endif

#endif //__uix_cwindow_hpp__
