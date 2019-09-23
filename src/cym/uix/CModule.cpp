#include "cym/uix/CModule.hpp"

namespace cym { namespace uix {
  CModule::CModule(HINSTANCE hHandle/*=::GetModuleHandle(NULL)*/) : CObject(), mHandle{hHandle} {
    log::nfo << "uix::CModule::CModule()::" << this << " INSTANCE:" << mHandle << log::end;
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
    return true;
  }
  
  bool CModule::free() {
    log::nfo << "uix::CModule::init()::" << this << log::end;
    return true;
  }
}}