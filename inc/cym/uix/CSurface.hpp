#ifndef __cym_uix_csurface_hpp__
#define __cym_uix_csurface_hpp__

#include "CPanel.hpp"
#include "CContext.hpp"
#include "CRender.hpp"

namespace cym { namespace uix {
  class CSurface : public CPanel, public CRender {
    protected:
      using CPanel::CPanel;
      using CPanel::operator=;
      typedef CPanel super;
      static constexpr int STYLE  = CPanel::STYLE;
    public: // ctor
      CSurface(CWindow*,                      int);
      CSurface(CWindow*, const SConfig& = {}, int = ZERO);
      ~CSurface();
    public: // copy = deleted
      CSurface(const CSurface&) = delete;
      CSurface& operator =(const CSurface&) = delete;
    protected:
      bool init(CWindow*, const CContext::SConfig&, int);

  };
}}

#endif //__cym_uix_csurface_hpp__
