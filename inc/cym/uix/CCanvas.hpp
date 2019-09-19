#ifndef __cym_uix_ccanvas_hpp__
#define __cym_uix_ccanvas_hpp__

#include "CFrame.hpp"
#include "CContext.hpp"

namespace cym { namespace uix {
  class CCanvas : public CFrame {
    protected:
      using CFrame::CFrame;
      using CFrame::operator=;
      friend class CContext;
      typedef CFrame super;
      static constexpr int STYLE = super::STYLE;
      typedef CContext::SConfig SConfig;
    protected:
      CContext* mContext = {nullptr};
    public:
      CCanvas(                                       int = ZERO);
      CCanvas(          const SConfig& sConfig,      int = ZERO);
      CCanvas(CWindow*, const SConfig& sConfig = {}, int = ZERO);
      ~CCanvas();
    protected:
      bool init(CWindow*, const CContext::SConfig&, int);
    public:
      virtual bool fullscreen(uint = EFullscreen::EMPTY | EFullscreen::FULLSCREEN) override;
    public:
      bool swap() const;
      bool current() const;
      bool clear(int = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT) const;
      bool reset() const;
  };  
}}

#endif //__cym_uix_ccanvas_hpp__
