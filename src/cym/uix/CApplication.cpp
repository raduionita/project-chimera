#include "cym/uix/CApplication.hpp"
#include "cym/uix/CConsole.hpp"

namespace cym { namespace uix {
  CApplication* CApplication::sInstance{nullptr};
  
  CApplication::CApplication(HINSTANCE hHandle/*=::GetModuleHandle(NULL)*/, int nCmdShow/*=0*/) : CObject(), mHandle{hHandle} {
    std::cout << "uix::CApplication::CApplication()::" << this << " INSTANCE:" << mHandle << std::endl;
    assert(!sInstance && "CApplication::sIntastace already defined. Only one CApplication instance allowed!");
    mConsole  = new CConsole(this, nCmdShow);
    sInstance = this;
  }
  
  CApplication::~CApplication() {
    std::cout << "uix::CApplication::~CApplication()::" << this << std::endl;
  }
  
  CApplication::CApplication(const CApplication&) {
    std::cout << "uix::CApplication::CApplication(CApplication&)::" << this << std::endl;
  }
  
  CApplication& CApplication::operator =(const CApplication& that) {
    if (this != &that) {
      
    }
    return *this;
  }
  
  CApplication::operator HINSTANCE() {
    return mHandle;
  }
  
  CApplication::operator const HINSTANCE() const {
    return mHandle;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CApplication::init() {
    std::cout << "uix::CApplication::init()::" << this << std::endl;
    onInit();
    return true;
  }
  
  bool CApplication::free() {
    std::cout << "uix::CApplication::free()::" << this << std::endl;
    
    return true;
  }
  
  int CApplication::exec(int nMode/*=0*/) {
    std::cout << "uix::CApplication::exec()::" << this << std::endl;
    
    // @todo: run mLoop.exec()
    // @todo: mLoop stops => CApplication stop  
    
    mRunning = init();
    
    auto start = sys::now();
    
    MSG msg;
    while (mRunning) {
      if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        mRunning = msg.message != WM_QUIT;
      } else {
        onTick(sys::now() - start);
      }
    }
    
    mRunning = !free();
  
    return (int)(msg.wParam);
  }
  
  int CApplication::quit(int nCode/*=0*/) {
    std::cout << "uix::CApplication::quit(int)::" << this << std::endl;
    mRunning = false;
    onExit();
    return nCode;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CApplication* CApplication::instance() {
    if (!sInstance) new CApplication;
    // this will be deleted by the CObject::CRegistry
    return sInstance;
  }
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CApplication::onInit()    { }
  void CApplication::onTick(int) { }
  void CApplication::onExit()    { }
}}
