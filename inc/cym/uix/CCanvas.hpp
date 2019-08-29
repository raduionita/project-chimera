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
      typedef CContext::SOptions SOptions; 
    protected:
      CContext* mContext = {nullptr};
    public:
      CCanvas() = default;
      CCanvas(                                                                                               int);
      CCanvas(                                                              const SShape&,                   int = 0); 
      CCanvas(                                         const SString&,      const SShape& = SShape::DEFAULT, int = 0);
      CCanvas(          const SOptions& sOptions,      const SString& = "", const SShape& = SShape::DEFAULT, int = 0);
      CCanvas(CWindow*, const SOptions& sOptions = {}, const SString& = "", const SShape& = SShape::DEFAULT, int = 0);
      ~CCanvas();
    protected:
      bool init(CWindow*, const CContext::SOptions& sOptions, const SString&, const SShape&, int);
  };  
}}

#endif //__cym_uix_ccanvas_hpp__
