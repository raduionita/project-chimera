#include "cym/uix/CPen.hpp"

namespace cym { namespace uix {
  CPen::CPen() {
    log::nfo << "uix::CPen::CPen()::" << this << log::end;
    mHandle = HPEN(NULL_PEN);
  }
  
  CPen::~CPen() {
    log::nfo << "uix::CPen::~CPen()::" << this << log::end;
  }
}}
