#ifndef __cym_uix_cwidget_hpp__
#define __cym_uix_cwidget_hpp__

#include "uix.hpp"
#include "CWindow.hpp"

namespace cym { namespace uix { 
  class CWidget : public CWindow {
    using CWindow::CWindow;
    typedef CWindow super;
    public:
      CWidget() = default;
      ~CWidget();
  };
}}

#endif //__cym_uix_cwidget_hpp__
