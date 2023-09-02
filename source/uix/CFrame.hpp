#ifndef __uix_cframe_hpp__
#define __uix_cframe_hpp__

#include "uix/CWindow.hpp"

namespace uix {
  class CFrame : public uix::CWindow {
      friend class uix::CApplication;
      friend class uix::TApplication<CFrame>;
      using super = uix::CWindow;
    private:
      CFrame();
    public:
      ~CFrame();
    public:
      CFrame(uix::CWindow* pParent);
    protected:
      virtual bool init() override;
      virtual bool free() override;
  };
} // namespace uix

#endif //__uix_cframe_hpp__