#ifndef __uix_ctoplevel_hpp__
#define __uix_ctoplevel_hpp__

#include "uix.hpp"
#include "CFrame.hpp"

namespace uix {
  class CToplevel : public CFrame {
    protected:
      using CFrame::CFrame;
      using CFrame::operator=;
    protected:
      typedef CFrame super;
      static constexpr int WINDOW = super::WINDOW;
    public:
      CToplevel() = default;
      CToplevel(int = ZERO);
      ~CToplevel();
    protected:
      virtual bool init(CWindow*, int) override;
  };
}

#endif //__uix_ctoplevel_hpp__
