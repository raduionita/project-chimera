#ifndef __cym_uix_csurface_hpp__
#define __cym_uix_csurface_hpp__

#include "CPanel.hpp"
#include "CContext.hpp"

namespace cym { namespace uix {
  class CSurface : public CPanel {
    protected:
      using CPanel::CPanel;
      typedef CPanel super;
      static constexpr int STYLE  = CPanel::STYLE;
    public:
      typedef CContext::SConfig SConfig;
    protected:
      CContext* mContext = {nullptr};
    public:
      CSurface(CWindow*, const SConfig& = {}, int = ZERO);
      ~CSurface();
    protected:
      bool init(CWindow*, const CContext::SConfig&, int);
    public:
      bool swap()    const;
      bool current() const;
  };
}}

#endif //__cym_uix_csurface_hpp__
