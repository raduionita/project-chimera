#include "win/CConsole.hpp"

#ifdef PLATFORM_WINDOWS

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

#endif // PLATFORM_WINDOWS
