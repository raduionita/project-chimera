#ifndef __cym_uix_cwindow_hpp__
#define __cym_uix_cwindow_hpp__

#include "uix.hpp"
#include "CObject.hpp"
#include "CHandler.hpp"
#include "CApplication.hpp"

namespace cym { namespace uix { 
  class CWindow : public CObject, CHandler {
    protected:
    struct SState {
      static constexpr int PREV = -1;
      static constexpr int CURR =  0;
      static constexpr int FUTR =  1;
      EState eState{EState::_STATE_};
      
    };
    
    protected:
    using CObject::CObject;
    using CObject::operator=;
    
    protected:
    typedef CObject super;
    static constexpr int STYLE = EHint::AUTOXY|EHint::AUTOWH;
    
    protected:
    bool              mInited = {false};
    HWND              mHandle = {NULL};
    CLayout*          mLayout = {nullptr};
    CWindow*          mParent = {nullptr};
    TArray<SState, 3> mStates;
    EState            mState  = {EState::_STATE_};
    TVector<CWindow*> mChildren;
    
    public:
    // ctor
    CWindow();
    ~CWindow();
    // cast
    explicit operator       HWND();
    explicit operator const HWND() const;
    
    protected:
    virtual bool    init(CWindow*, int);
    virtual bool    free() final;
    virtual CString name() const final;
    
    public:
    bool    move(int, int);
    bool    size(int, int);
    bool    center();
    SRect   adjust();
    bool    show(int = 1);
    bool    hide(int = 1);
    bool    focus(int = 1);
    bool    pack();
    bool    minimize();
    bool    maximize();
    bool    area(const SArea&);
    SArea   area() const;
    bool    rect(const SRect&);
    SRect   rect() const;
    auto    layout() const -> decltype(mLayout);
    auto    layout(CLayout* pLayout) -> decltype(mLayout);
    auto    parent() const -> decltype(mParent);
    bool    child(CWindow*);
    auto    children() const -> decltype(mChildren);
    auto    siblings() const -> decltype(mChildren);
    bool    title(const CString&);
    CString title() const;
    
    protected:
    static CWindow* find(const CString&);
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
