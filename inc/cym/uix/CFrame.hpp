#ifndef __cym_uix_cframe_hpp__
#define __cym_uix_cframe_hpp__

#include "uix.hpp"
#include "CWindow.hpp"

namespace cym { namespace uix {
  class CFrame : public CWindow {
    using CWindow::CWindow;
    typedef CWindow super;
    public:
      CFrame() = default;
      CFrame(                                                                int);
      CFrame(CWindow*, const TString& = "", const SShape& = SShape::DEFAULT, int = 0);
      ~CFrame();
    protected:
      virtual bool init(CWindow*, const SShape&, int) override;
              bool init(CWindow*, const TString&, const SShape&, int);
  };
}}

#endif //__cym_uix_cframe_hpp__
