#include "cym/CMaterial.hpp"

namespace cym {
  CMaterial::CMaterial() {
    log::nfo << "cym::CMaterial::CMaterial()::" << this << log::end;
  }
  
  CMaterial::~CMaterial() {
    log::nfo << "cym::CMaterial::~CMaterial()::" << this << log::end;
  }
}
