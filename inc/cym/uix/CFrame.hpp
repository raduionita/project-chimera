#ifndef __cym_uix_cframe_hpp__
#define __cym_uix_cframe_hpp__

#include "CPopup.hpp"

namespace cym { namespace uix {
  class CFrame : public CPopup {
    protected:
      using CPopup::CPopup;
      using CPopup::operator=;
    protected:
      typedef CWindow super;
      static constexpr int STYLE = CPopup::STYLE|EHint::BORDER|EHint::TITLE|EHint::FRAME|EHint::SYSBOX|EHint::MINBOX|EHint::MAXBOX|EHint::SIZER;
    public:
      CFrame(          int = ZERO);
      CFrame(CWindow*, int = ZERO);
      ~CFrame();
    protected:
      virtual bool init(CWindow*, int) override;
  };
}}

#endif //__cym_uix_cframe_hpp__
