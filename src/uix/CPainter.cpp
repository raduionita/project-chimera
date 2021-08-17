#include "uix/CPainter.hpp"

namespace uix {
  CPainter::CPainter(CWindow* pWindow) : mWindow{pWindow} {
    SYS_LOG_NFO("uix::CPainter::CPainter(CWindow*)::" << this << " WINDOW:" << mWindow);
    
    // @todo: if window is NOT in a draw state => assert:false // only draw on WM_PAINT?!
  }
  
  CPainter::~CPainter() {
    SYS_LOG_NFO("uix::CPainter::~CPainter()::" << this << " WINDOW:" << mWindow);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CPainter::rectangle(const SArea& sArea, const EPainter& ePainter) {
    SYS_LOG_NFO("uix::CPainter::rectangle(SArea&,EPainter&)::" << this << " ID:" << mWindow->id());
    
    // @todo: set brush
    // @todo: set pen
    
    return TRUE == ::Rectangle(HDC(*mWindow), sArea.x, sArea.y, sArea.x+sArea.w, sArea.y+sArea.h);
  }
}
