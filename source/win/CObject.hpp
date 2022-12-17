#ifndef __win_cobject_hpp__
#define __win_cobject_hpp__

#include "win/win.hpp"

namespace win {
  class CObject {
    public:
      CObject() = default;
      virtual ~CObject() = default;
  };
} // namespace win


#endif //__win_cobject_hpp__