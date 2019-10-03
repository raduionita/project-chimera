#include "cym/uix/CModule.hpp"

namespace cym::uix {
  CModule::CModule(HINSTANCE hHandle/*=::GetModuleHandle(NULL)*/) : CObject(), mHandle{hHandle} {
    log::nfo << "uix::CModule::CModule()::" << this << " INSTANCE:" << mHandle << log::end;
  }
  
  CModule::CModule(const char* dll) : CObject(), mHandle{::LoadLibrary(dll)} {
    log::nfo << "uix::CModule::CModule(const char*)::" << this << " INSTANCE:" << mHandle << log::end;
  }
    
  CModule::~CModule() {
    log::nfo << "uix::CModule::~CModule()::" << this << log::end;
  }
  
  CModule::operator HINSTANCE() {
    return mHandle;
  }
  
  CModule::operator const HINSTANCE() const {
    return mHandle;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CModule::init() {
    log::nfo << "uix::CModule::init()::" << this << log::end;
    mInited = true;
    return mInited;
  }
  
  bool CModule::free() {
    log::nfo << "uix::CModule::free()::" << this << log::end;
    return true;
  }
}


// libGL = LoadLibraryW(L"opengl32.dll");
//     if(libGL != NULL) {
//         cppglGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE)GetProcAddress(
//                 libGL, "wglGetProcAddress");
//         return cppglGetProcAddressPtr != NULL;
//     }
