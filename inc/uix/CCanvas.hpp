#ifndef __uix_ccanvas_hpp__
#define __uix_ccanvas_hpp__

#include "CFrame.hpp"
#include "CContext.hpp"
#include "CRender.hpp"

namespace uix {
  class CCanvas : public CFrame {
    protected:
      using CFrame::CFrame;
      using CFrame::operator=;
      friend class CContext;
      typedef CFrame super;
      static constexpr int WINDOW = super::WINDOW;
    protected:
      CContext*         mContext {nullptr};
      CContext::SConfig mConfig;
    private:
      CCanvas() = default;
    public:
      CCanvas(                                                                                                                                   uint);
      CCanvas(          const CContext::SConfig& sConfig,                                                                                        uint = WINDOW);
      CCanvas(CWindow*, const CContext::SConfig& sConfig = {UIX_CONTEXT_MAJOR,UIX_CONTEXT_MINOR,1,32,24,8,8,1,CContext::CONTEXT|CContext::CORE}, uint = WINDOW);
      ~CCanvas();
    protected:
      virtual bool init(CWindow* = nullptr, const CString& = "", const SArea& = AUTO, uint = WINDOW) override;
    public:
      virtual CStyle* style() override { return nullptr; }
      virtual bool    fullscreen(uint = EFullscreen::EMPTY | EFullscreen::FULLSCREEN) override;
      inline bool     swap()    const { return mContext->swap(); };
      bool            current() const;
      bool            clear(int = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT) const;
      bool            reset()   const;
      const char*     version() const;
    public:
      void onResize(CEvent*);
  };  
}

#endif //__uix_ccanvas_hpp__
