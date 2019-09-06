#ifndef __cym_uix_csurface_hpp__
#define __cym_uix_csurface_hpp__

#include "CPanel.hpp"
#include "CContext.hpp"

namespace cym { namespace uix {
  class CSurface : public CPanel {
    protected:
      using CPanel::CPanel;
      using CPanel::operator=;
    protected:
      typedef CPanel super;
      static constexpr int STYLE  = CPanel::STYLE;
    public:
      typedef CContext::SConfig SConfig;
    protected:
      CContext* mContext = {nullptr};
    public:
      CSurface(CWindow*,                      int);
      CSurface(CWindow*, const SConfig& = {}, int = ZERO);
      ~CSurface();
      // move
      CSurface(CSurface&&) noexcept;
      CSurface& operator =(CSurface&&) noexcept;
      // copy = deleted
      CSurface(const CSurface&) = delete;
      CSurface& operator =(const CSurface&) = delete;
    protected:
      bool init(CWindow*, const CContext::SConfig&, int);
    public:
      bool swap()    const;
      bool current() const;
      bool clear(int = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT) const;
  };
}}

#endif //__cym_uix_csurface_hpp__
