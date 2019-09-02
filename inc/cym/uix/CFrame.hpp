#ifndef __cym_uix_cframe_hpp__
#define __cym_uix_cframe_hpp__

#include "uix.hpp"
#include "CWindow.hpp"

namespace cym { namespace uix {
  class CFrame : public CWindow {
    protected:
      using CWindow::CWindow;
      typedef CWindow super;
    public:
      CFrame(          int = EHint::FRAME);
      CFrame(CWindow*, int = EHint::FRAME);
      ~CFrame();
    protected:
      virtual bool init(CWindow*, int) override;
  };
}}

#endif //__cym_uix_cframe_hpp__
