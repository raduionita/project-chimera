#include "uix/CWindow.hpp"
#include "sys/CLogger.hpp"

namespace uix {
  // dtor
  CWindow::~CWindow() {
    LOGDBG("uix::CWindow::~CWindow()");
    CWindow::free();
  }

  // init
  bool CWindow::init() {
    RETURN((mState & EState::INITED),true);
    LOGDBG("uix::CWindow::init()");

    mState = EState::INITED;

    return true;
  }
  // free
  bool CWindow::free() {
    RETURN((mState & EState::FREED),true);
    LOGDBG("uix::CWindow::free()");


    mState = EState::FREED;

    // free only if not FREED before

    return mState & EState::FREED;
  }
} // namespace uix
