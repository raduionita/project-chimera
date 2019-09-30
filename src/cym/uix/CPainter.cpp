#include "cym/uix/CPainter.hpp"

namespace cym { namespace uix {
  CPainter::CPainter(CWindow* pWindow) : mWindow{pWindow} {
    log::nfo << "uix::CPainter::CPainter(CWindow*)::" << this << " WINDOW:" << mWindow << log::end;
    
    // @todo: if window is NOT in a draw state => assert:false // only draw on WM_PAINT?!
  }
  
  CPainter::~CPainter() {
    log::nfo << "uix::CPainter::~CPainter()::" << this << " WINDOW:" << mWindow << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CPainter::rectangle(const SArea& sArea, const EPainter& ePainter) {
    log::nfo << "uix::CPainter::rectangle(SArea&,EPainter&)::" << this << " ID:" << mWindow->id() << log::end;
    
    // @todo: set brush
    // @todo: set pen
    
    return TRUE == ::Rectangle(HDC(*mWindow), sArea.x, sArea.y, sArea.x+sArea.w, sArea.y+sArea.h);
  }
}}
