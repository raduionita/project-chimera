#ifndef __win_cframe_hpp__
#define __win_cframe_hpp__

#include "win/CWindow.hpp"

namespace win {
  class CFrame : public CWindow {
      friend class TApplication<CFrame>;
    protected:
      virtual void init() override { }
  };
} // namespace win


#endif //__win_cframe_hpp__