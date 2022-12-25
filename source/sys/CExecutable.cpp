#include "sys/CExecutable.hpp"

#include <vector>
#include <string>

namespace sys {
  int CExecutable::exec() {
    return 0;
  }

  void CExecutable::setArguments(int argc, char* argv[]) {
    // TODO
    // std::vector<std::string>{argv+1, argv + argc};
    // LOGDBG("sys::CExecutable::setArguments()::" << argc);
    // for (int i = 0; i < argc; i++) {
      // LOGDBG(argv[i]);
    // }
  }
} // namespace sys
