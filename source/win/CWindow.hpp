#ifndef __win_cwindow_hpp__
#define __win_cwindow_hpp__

#include "win/CObject.hpp"

namespace win {
  class CWindow : public CObject {
    protected:
      virtual void init() { }
      virtual void free() { }
  };
} // namespace win


#endif //__win_cwindow_hpp__