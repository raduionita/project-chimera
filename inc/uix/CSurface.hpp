#ifndef __uix_csurface_hpp__
#define __uix_csurface_hpp__

#include "uix/CPanel.hpp"
#include "uix/CContext.hpp"

namespace uix {
  class CSurface : public CPanel {
    protected:
      using CPanel::CPanel;
      using CPanel::operator=;
      typedef CPanel super;
      static constexpr int WINDOW = CPanel::WINDOW;
    protected:
      CContext*         mContext {nullptr};
      CContext::SConfig mConfig;
    private: // ctor
      CSurface() = default;
    public: // ctor
      CSurface(CWindow*,                                uint);
      CSurface(CWindow*,       CContext*,               uint = CSurface::WINDOW);
      CSurface(CWindow*, const CContext::SConfig& = {}, uint = CSurface::WINDOW);
      ~CSurface();
    public: // copy = deleted
      CSurface(const CSurface&) = delete;
      CSurface& operator =(const CSurface&) = delete;
    protected:
             bool init(CWindow* = nullptr, const CContext::SConfig& = {},const CString& = "", const SArea& = AUTO, uint = WINDOW);
     virtual bool init(CWindow* = nullptr, const CString& = "", const SArea& = AUTO, uint = WINDOW) override;
    public:
      virtual CStyle*   style() override { return nullptr; }
      inline  CContext* context() const { return mContext; }
      inline  bool      swap()    const { return mContext->swap(); }
      bool              current() const;
      bool              clear(int = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT) const;
      bool              reset()   const;
      const char*       version() const;
    public:
      void onResize(CEvent*);
  };
}

#endif //__uix_csurface_hpp__
