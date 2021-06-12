#ifndef __uix_cpanel_hpp__
#define __uix_cpanel_hpp__

#include "CWidget.hpp"

namespace uix {
  class CPanel : public CWidget {
      friend class CSurface;
    protected:
      using CWidget::CWidget;
      using CWidget::operator=;
      typedef CWidget super;
      static constexpr int WINDOW = CWidget::WINDOW;
    private:
      CPanel() = default;
    public:
      CPanel(CWindow*, uint = WINDOW);
      ~CPanel();
    protected:
      virtual bool init(CWindow* = nullptr, const CString& = "", const SArea& = AUTO, uint = WINDOW) override;
  };
}


#endif //__uix_cpanel_hpp__
