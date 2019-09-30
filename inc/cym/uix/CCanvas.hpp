#ifndef __cym_uix_ccanvas_hpp__
#define __cym_uix_ccanvas_hpp__

#include "CFrame.hpp"
#include "CContext.hpp"
#include "CRender.hpp"

namespace cym::uix {
  class CCanvas : public CFrame, public CRender {
    protected:
      using CFrame::CFrame;
      using CFrame::operator=;
      friend class CContext;
      typedef CFrame super;
      static constexpr int WINDOW = super::WINDOW;
    public:
      CCanvas(                                                 int = ZERO);
      CCanvas(          const CContext::SConfig& sConfig,      int = ZERO);
      CCanvas(CWindow*, const CContext::SConfig& sConfig = {}, int = ZERO);
      ~CCanvas();
    protected:
      bool init(CWindow*, const CContext::SConfig&, int);
    public:
      virtual CStyle* style() override { return nullptr; }
      virtual bool    fullscreen(uint = EFullscreen::EMPTY | EFullscreen::FULLSCREEN) override;
  };  
}

#endif //__cym_uix_ccanvas_hpp__
