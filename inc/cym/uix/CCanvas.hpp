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
      CCanvas() = default;
      CCanvas(                                                                                             int);
      CCanvas(                                                            const SShape&,                   int = 0); 
      CCanvas(                                       const TString&,      const SShape& = SShape::DEFAULT, int = 0);
      CCanvas(          const SConfig& sConfig,      const TString& = "", const SShape& = SShape::DEFAULT, int = 0);
      CCanvas(CWindow*, const SConfig& sConfig = {}, const TString& = "", const SShape& = SShape::DEFAULT, int = 0);
      ~CCanvas();
    protected:
      bool init(CWindow*, const CContext::SConfig&, const TString&, const SShape&, int);
  };  
}}

#endif //__cym_uix_ccanvas_hpp__
