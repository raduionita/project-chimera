#include "uix/CPen.hpp"

namespace uix {
  CPen::CPen() {
    CYM_LOG_NFO("uix::CPen::CPen()::" << this);
    mHandle = HPEN(NULL_PEN);
  }
  
  CPen::~CPen() {
    CYM_LOG_NFO("uix::CPen::~CPen()::" << this);
  }
}
