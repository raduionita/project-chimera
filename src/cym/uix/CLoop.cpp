#include "cym/uix/CLoop.hpp"

namespace cym { namespace uix {
  CLoop::CLoop() {
    log::nfo << "uix::CLoop::CLoop()::" << this << log::end;
  }
  
  CLoop::~CLoop() {
    log::nfo << "uix::CLoop::~CLoop()::" << this << log::end;
  }
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  int CLoop::exec(int nMode/*=0*/) {
    log::nfo << "uix::CLoop::exec(int)::" << this << log::end;
    
    while (mRunning) {
      
    }
    
    return 0;
  }
  
  int CLoop::quit(int nCode/*=0*/) {
    log::nfo << "uix::CLoop::quit(int)::" << this << log::end;
    mRunning = false;
    return nCode;
  }
}}
