#include "cym/uix/CBrush.hpp"

namespace cym { namespace uix {
  CBrush::CBrush() {
    log::nfo << "uix::CBrush::CBrush()::" << this << log::end;
  }
    
  CBrush::~CBrush() {
    log::nfo << "uix::CBrush::~CBrush()::" << this << log::end;
  }
  
  // cast ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CBrush::operator HBRUSH()             { return mHandle; }
  CBrush::operator const HBRUSH() const { return mHandle; }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
}}
