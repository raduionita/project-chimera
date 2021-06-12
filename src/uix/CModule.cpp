#include "uix/CModule.hpp"

namespace uix {
  CModule::CModule(HINSTANCE hHandle/*=::GetModuleHandle(NULL)*/) : CObject(), mHandle{hHandle} {
    CYM_LOG_NFO("uix::CModule::CModule()::" << this << " INSTANCE:" << mHandle);
  }
  
  CModule::CModule(const char* dll) : CObject(), mHandle{::LoadLibrary(dll)} {
    CYM_LOG_NFO("uix::CModule::CModule(const char*)::" << this << " INSTANCE:" << mHandle);
  }
    
  CModule::~CModule() {
    CYM_LOG_NFO("uix::CModule::~CModule()::" << this);
  }
  
  CModule::operator HINSTANCE() {
    return mHandle;
  }
  
  CModule::operator const HINSTANCE() const {
    return mHandle;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CModule::init() {
    CYM_LOG_NFO("uix::CModule::init()::" << this);
    mInited = true;
    return mInited;
  }
  
  bool CModule::free() {
    CYM_LOG_NFO("uix::CModule::free()::" << this);
    return true;
  }
}


// libGL = LoadLibraryW(L"opengl32.dll");
//     if(libGL != NULL) {
//         cppglGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE)GetProcAddress(
//                 libGL, "wglGetProcAddress");
//         return cppglGetProcAddressPtr != NULL;
//     }
