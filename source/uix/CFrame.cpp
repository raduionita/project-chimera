#include "uix/CFrame.hpp"
#include "sys/CLogger.hpp"

namespace uix {
  // ctor
  CFrame::CFrame() {
    LOGDBG("uix::CFrame::CFrame()");
    init();
  }  
  // dtor
  CFrame::~CFrame() {
    LOGDBG("uix::CFrame::~CFrame()");
    free();
  }

  // init
  bool CFrame::init() {
    LOGDBG("uix::CFrame::init()");
    super::init();

    return true;
  }  
  // free
  bool CFrame::free() {
    LOGDBG("uix::CFrame::free()");
    super::free();

    return true;
  }
} // namespace uix
