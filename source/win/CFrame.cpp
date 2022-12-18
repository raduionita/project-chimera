#include "win/CFrame.hpp"
#include "sys/CLogger.hpp"

namespace win {
  // ctor
  CFrame::CFrame() {
    LOGDBG("win::CFrame::CFrame()");
    init();
  }  
  // dtor
  CFrame::~CFrame() {
    LOGDBG("win::CFrame::~CFrame()");
    free();
  }

  // init
  bool CFrame::init() {
    LOGDBG("win::CFrame::init()");
    super::init();

    return true;
  }  
  // free
  bool CFrame::free() {
    LOGDBG("win::CFrame::free()");
    super::free();

    return true;
  }
} // namespace win
