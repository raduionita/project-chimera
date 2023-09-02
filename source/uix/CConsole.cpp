#include "uix/CConsole.hpp"

namespace uix {
  bool CConsole::sMain{true};
  // ctor
  CConsole::CConsole() {
    mMain = sMain;
    sMain = false;
  }
  // dtor
  CConsole::~CConsole() {
    sMain = mMain;
  }
} // namespace uix
