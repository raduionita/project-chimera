#include "uix/CPen.hpp"

namespace uix {
  CPen::CPen() {
    SYS_LOG_NFO("uix::CPen::CPen()::" << this);
    mHandle = HPEN(NULL_PEN);
  }
  
  CPen::~CPen() {
    SYS_LOG_NFO("uix::CPen::~CPen()::" << this);
  }
}
