#ifndef __cym_uix_cpanel_hpp__
#define __cym_uix_cpanel_hpp__

#include "CWidget.hpp"

namespace cym { namespace uix {
  class CPanel : public CWidget {
    protected:
    using CWidget::CWidget;
    using CWidget::operator=;
      
    protected:
    typedef CWidget super;
    static constexpr int STYLE = CWidget::STYLE;
    
    public:
    CPanel(CWindow*, int = ZERO);
    ~CPanel();
    
    protected:
    virtual bool init(CWindow*, int) override;
  };
}}


#endif //__cym_uix_cpanel_hpp__
