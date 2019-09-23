#include "cym/uix/CPainter.hpp"

namespace cym { namespace uix {
  CPainter::CPainter(CWindow* pWindow) {
    
    // @todo: if window is NOT in a draw state => assert:false // only draw on WM_PAINT?!
    
    
    // mWindow = pWindow;
  }
  
  CPainter::~CPainter() {
    
  }
}}
