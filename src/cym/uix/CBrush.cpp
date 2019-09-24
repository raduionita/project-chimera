#include "cym/uix/CBrush.hpp"
#include "cym/uix/CBitmap.hpp"
#include "cym/uix/CColor.hpp"

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
