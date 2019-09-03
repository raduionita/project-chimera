#ifndef __cym_uix_cwidget_hpp__
#define __cym_uix_cwidget_hpp__

#include "CWindow.hpp"

namespace cym { namespace uix { 
  class CWidget : public CWindow {
    protected:
      using CWindow::CWindow;
      typedef CWindow super;
      static constexpr int STYLE  = EHint::CHILD;
    public:
      ~CWidget();
  };
}}

#endif //__cym_uix_cwidget_hpp__
