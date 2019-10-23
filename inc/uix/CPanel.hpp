#ifndef __uix_cpanel_hpp__
#define __uix_cpanel_hpp__

#include "CWidget.hpp"

namespace uix {
  class CPanel : public CWidget {
    protected:
      using CWidget::CWidget;
      using CWidget::operator=;
      typedef CWidget super;
      static constexpr int WINDOW = CWidget::WINDOW;
    public:
      CPanel() = default;
      CPanel(CWindow*, int = ZERO);
      ~CPanel();
    protected:
      virtual bool init(CWindow*, int) override;
  };
}


#endif //__uix_cpanel_hpp__
