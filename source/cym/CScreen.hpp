#ifndef __cym_cscreen_hpp__
#define __cym_cscreen_hpp__

#include "cym/cym.hpp"

#include <list>

namespace cym {
  class CScreen {
    protected:
      std::list<cym::CLayer*> mLayers;
    public:
      CScreen();
      ~CScreen();
  };
} // namespace cym


#endif //__cym_cscreen_hpp__