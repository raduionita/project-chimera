#ifndef __cym_uix_cframe_hpp__
#define __cym_uix_cframe_hpp__

#include "CWindow.hpp"

namespace cym { namespace uix {
  class CFrame : public CWindow {
    protected:
      using CWindow::CWindow;
      typedef CWindow super;
      static constexpr int STYLE = EHint::POPUP|EHint::BORDER|EHint::TITLE|EHint::FRAME|EHint::SYSBOX|EHint::MINBOX|EHint::MAXBOX|EHint::SIZER;
    public:
      CFrame(          int = ZERO);
      CFrame(CWindow*, int = ZERO);
      ~CFrame();
    protected:
      virtual bool init(CWindow*, int) override;
  };
}}

#endif //__cym_uix_cframe_hpp__
