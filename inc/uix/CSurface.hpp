#ifndef __uix_csurface_hpp__
#define __uix_csurface_hpp__

#include "CPanel.hpp"
#include "CContext.hpp"
#include "CRender.hpp"

namespace uix {
  class CSurface : public CPanel, public CRender {
    protected:
      using CPanel::CPanel;
      using CPanel::operator=;
      typedef CPanel super;
      static constexpr int WINDOW = CPanel::WINDOW;
    public: // ctor
      CSurface() = default;
      CSurface(CWindow*,                                int);
      CSurface(CWindow*, const CContext::SConfig& = {}, int = ZERO);
      ~CSurface();
    public: // copy = deleted
      CSurface(const CSurface&) = delete;
      CSurface& operator =(const CSurface&) = delete;
    protected:
      bool init(CWindow*, const CContext::SConfig&, int);
    public:
      virtual CStyle* style() override { return nullptr; }
  };
}

#endif //__uix_csurface_hpp__
