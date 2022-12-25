#include "win/CWindow.hpp"
#include "sys/CLogger.hpp"

#ifdef PLATFORM_WINDOWS

namespace win {
  // dtor
  CWindow::~CWindow() {
    LOGDBG("win::CWindow::~CWindow()");
    CWindow::free();
  }

  // init
  bool CWindow::init() {
    RETURN((mState & EState::INITED),true);
    LOGDBG("win::CWindow::init()");

    mState = EState::INITED;

    return true;
  }
  // free
  bool CWindow::free() {
    RETURN((mState & EState::FREED),true);
    LOGDBG("win::CWindow::free()");


    mState = EState::FREED;

    // free only if not FREED before

    return mState & EState::FREED;
  }
} // namespace win

#endif // PLATFORM_WINDOWS