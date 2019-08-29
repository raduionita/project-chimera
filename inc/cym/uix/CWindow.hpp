#ifndef __cym_uix_cwindow_hpp__
#define __cym_uix_cwindow_hpp__

#include "uix.hpp"
#include "CObject.hpp"
#include "CHandler.hpp"
#include "CApplication.hpp"

namespace cym { namespace uix { 
  class CWindow : public CObject, CHandler {
    typedef CObject super;
    // static class CRegistry {
    //   friend class CWindow;
    //   static std::map<SString, ATOM> mClasses;  
    //   CRegistry();
    //   ~CRegistry();
    //   bool insert(WNDCLASSEX*);
    // } xRegistry;
    private:
      static std::map<SString, LPTSTR> sRegistry;
    protected:
      bool          mInited = {false};
      HWND          mHandle = {NULL};
      CLayout*      mLayout = {nullptr};
      CWindow*      mParent = {nullptr};
      const SString mCname  = {concat("uix::CWindow::", mId)};
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
      virtual bool init(CWindow*, const SShape&, int);
      virtual bool free() final;
      LPTSTR       classify();
    public:
      bool move(int x, int y);
      bool show(int = 1);
      bool hide(int = 1);
    public:
      CLayout* layout() const;
      bool     layout(CLayout* pLayout);
      CWindow* parent() const;
      bool     title(const SString&);
      SString  title() const;
    protected:
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
