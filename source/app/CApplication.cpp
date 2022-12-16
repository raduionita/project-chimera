#include "app/CApplication.hpp"

namespace app {
  CApplication::CApplication() { }

  int CApplication::exec(int argc, char** argv) {
    BENTAG("app::CApplication::exec()");
    LOGTAG("app::CApplication::exec()");

    int* i = new int{1};

    int*& r = i;

    LOGDBG("::" << i);
    LOGDBG("::" << r);

    delete i; i = nullptr;

    LOGDBG("::" << r);

    return 0;
  }
} // namespace app
