#ifndef __cym_uix_csurface_hpp__
#define __cym_uix_csurface_hpp__

#include "uix.hpp"
#include "CWidget.hpp"
#include "CContext.hpp"

namespace cym { namespace uix {
  class CSurface : public CWidget {
    protected:
      using CWidget::CWidget;
      typedef CWidget super;
      static constexpr int STYLE  = CWidget::STYLE;
    public:
      typedef CContext::SConfig SConfig;
    protected:
      CContext* mContext = {nullptr};
    public:
      CSurface(                                       int = ZERO);
      CSurface(          const SConfig& sConfig,      int = ZERO);
      CSurface(CWindow*, const SConfig& sConfig = {}, int = ZERO);
      ~CSurface();
    protected:
      bool init(CWindow*, const CContext::SConfig&, int);
  };
}}

#endif //__cym_uix_csurface_hpp__
