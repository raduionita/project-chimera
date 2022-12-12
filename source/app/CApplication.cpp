#include "app/CApplication.hpp"

#include <iostream>

namespace app {
  CApplication::CApplication() { }

  int CApplication::exec(int argc, char** argv) {

    std::cout << "app::CApplication::exec()\n";

    return 0;
  }
} // namespace app
