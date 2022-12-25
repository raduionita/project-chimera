#ifndef __win_cframe_hpp__
#define __win_cframe_hpp__

#ifdef PLATFORM_WINDOWS

#include "win/CWindow.hpp"

namespace win {
  class CFrame : public win::CWindow {
      friend class win::CApplication;
      friend class win::TApplication<CFrame>;
      using super = win::CWindow;
    private:
      CFrame();
    public:
      ~CFrame();
    public:
      CFrame(win::CWindow* pParent);
    protected:
      virtual bool init() override;
      virtual bool free() override;
  };
} // namespace win

#endif // PLATFORM_WINDOWS

#endif //__win_cframe_hpp__