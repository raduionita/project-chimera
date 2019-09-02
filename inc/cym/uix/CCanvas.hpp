#ifndef __cym_uix_ccanvas_hpp__
#define __cym_uix_ccanvas_hpp__

#include "uix.hpp"
#include "CFrame.hpp"
#include "CContext.hpp"

namespace cym { namespace uix {
  class CCanvas : public CFrame {
    protected:
      friend class CContext;
      using CFrame::CFrame;
      typedef CFrame super;
    public:
      typedef CContext::SConfig SConfig; 
    protected:
      CContext* mContext = {nullptr};
    public:
      CCanvas(                                       int = EHint::FRAME);
      CCanvas(          const SConfig& sConfig,      int = EHint::FRAME);
      CCanvas(CWindow*, const SConfig& sConfig = {}, int = EHint::FRAME);
      ~CCanvas();
    protected:
      bool init(CWindow*, const CContext::SConfig&, int);
    public:
      bool swap() const;
      bool current() const;
  };  
}}

#endif //__cym_uix_ccanvas_hpp__
