#ifndef __cym_uix_ccontrol_hpp__
#define __cym_uix_ccontrol_hpp__

#include "CWidget.hpp"

namespace cym { namespace uix {
  class CControl : public CWidget {
    protected:
      using CWidget::CWidget;
      using CWidget::operator=;
    protected:
      typedef CWidget super;
      static constexpr int WINDOW = CWidget::WINDOW;
  };
}}

#endif //__cym_uix_ccontrol_hpp__
