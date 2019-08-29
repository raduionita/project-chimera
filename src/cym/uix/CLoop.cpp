#include "cym/uix/CLoop.hpp"

namespace cym { namespace uix {
  CLoop::CLoop() {
    std::cout << "uix::CLoop::CLoop()::" << this << std::endl;
  }
  
  CLoop::~CLoop() {
    std::cout << "uix::CLoop::~CLoop()::" << this << std::endl;
  }
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  int CLoop::exec(int nMode/*=0*/) {
    std::cout << "uix::CLoop::exec(int)::" << this << std::endl;
    
    while (mRunning) {
      
    }
    
    return 0;
  }
  
  int CLoop::quit(int nCode/*=0*/) {
    std::cout << "uix::CLoop::quit(int)::" << this << std::endl;
    mRunning = false;
    return nCode;
  }
}}
