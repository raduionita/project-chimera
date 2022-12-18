#include "win/CConsole.hpp"

namespace win {
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
} // namespace win
