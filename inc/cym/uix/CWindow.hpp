#ifndef __cym_uix_cwindow_hpp__
#define __cym_uix_cwindow_hpp__

#include "uix.hpp"
#include "CObject.hpp"
#include "CHandler.hpp"
#include "CApplication.hpp"

namespace cym { namespace uix { 
  class CWindow : public CObject, CHandler {
    typedef CObject super;
    private:
      static std::map<TString, LPTSTR> sRegistry;
    protected:
      bool               mInited = {false};
      HWND               mHandle = {NULL};
      CLayout*           mLayout = {nullptr};
      CWindow*           mParent = {nullptr};
      EState             mState  = {EState::_STATE_};
      TVector<CWindow*>  mChildren;
    public:
      CWindow();
      ~CWindow();
      CWindow(const CWindow&);
      // operators
      CWindow& operator          =(const CWindow&);
      explicit operator       HWND();
      explicit operator const HWND() const;
      explicit operator       LPTSTR();
    protected:
      virtual bool    init(CWindow*, int);
      virtual bool    free() final;
      virtual LPTSTR  classify();
      virtual TString name() const final;
    public:
      bool    move(int, int);
      bool    size(int, int);
      bool    center();
      SRect   adjust();
      bool    show(int = 1);
      bool    hide(int = 1);
      bool    focus(int = 1);
      bool    pack();
      bool    style(int = 0);
      bool    minimize();
      bool    maximize();
      SArea   area() const;
      SRect   rect() const;
      auto    layout() const -> decltype(mLayout);
      bool    layout(CLayout* pLayout);
      auto    parent() const -> decltype(mParent);
      auto    children() const -> decltype(mChildren);
      auto    siblings() const -> decltype(mChildren);
      bool    title(const TString&);
      TString title() const;
    protected:
      static CWindow* find(const TString&);
      static LRESULT CALLBACK proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  }; 
}}

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
