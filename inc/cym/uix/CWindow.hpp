#ifndef __cym_uix_cwindow_hpp__
#define __cym_uix_cwindow_hpp__

#include "CObject.hpp"
#include "CListener.hpp"
#include "CApplication.hpp"
#include "CStyle.hpp"
#include "CLayout.hpp"

namespace cym::uix {  // acme { gui { win, unx, osx } }
  class CWindow : public CObject, public CListener {
    protected:
      using CObject::CObject;
      using CObject::operator=;
      typedef CObject super;
      static constexpr int WINDOW = EWindow::AUTOXY|EWindow::AUTOWH; // @todo: rename this to HINTS or WINDOW or CONFIG
    public:
      struct SState {
        // @todo: window state
      };
      struct SConfig {
        int     nHints {ZERO};
        SArea   sArea  {CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT};
        CString oTitle {"CWindow"};
        CStyle  oStyle; // use std::move
        SConfig(                                                                                          int = ZERO);
        SConfig(                const SArea&,                                                             int = ZERO);
        SConfig(const CString&, const SArea& = {CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT}, int = ZERO);
        SConfig(const CString&,                                                                           int);
      };
    protected:
      bool              mInited      {false};
      CApplication*     mApplication {CApplication::instance()};
      HWND              mHandle      {NULL};
      CLayout*          mLayout      {nullptr};
      CWindow*          mParent      {nullptr};
      uint              mState       {ZERO};
      CStyle*           mStyle       {nullptr};
      CVector<CWindow*> mChildren;
    public: // ctor
      CWindow();
      ~CWindow();
    public: // cast
      explicit operator       HWND();
      explicit operator const HWND() const;
      explicit operator       HDC();
      explicit operator const HDC() const;
    protected:
      virtual bool    init(CWindow*, int);
      virtual bool    free();
      virtual CString name() const final;
    public: // actions
      bool            move(int, int);
      bool            size(int, int);
      bool            center();
      SRect           adjust();
      bool            show(int=1);
      bool            hide(int=1);
      bool            focus(int=1);
      bool            pack();
      bool            minimize();
      bool            maximize();
      virtual bool    fullscreen(int=ZERO);
    public: // chages
      STATE           state() const;
      bool            area(const SArea&);
      SArea           area() const;
      bool            rect(const SRect&);
      SRect           rect() const;
      auto            parent() const -> decltype(mParent);
      bool            child(CWindow*);
      auto            children() const -> decltype(mChildren);
      auto            siblings() const -> decltype(mChildren);
      bool            title(const CString&);
      CString         title() const;
      virtual bool    style(CStyle*);
      virtual CStyle* style();
      auto            layout() const -> decltype(mLayout);
      template <typename T>
      T*              layout(T* pLayout) { mLayout = pLayout; mLayout->layout(this); return pLayout; };
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

#endif //__cym_uix_cwindow_hpp__
