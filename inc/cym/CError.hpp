#ifndef __cym_cerror_hpp__
#define __cym_cerror_hpp__

#include "cym.hpp"

namespace cym {
  class CError {
    protected:
      CError* mOriginal = {nullptr};
      int     mCode     = {0};
    public:
      CError();
      virtual ~CError();
  };
}

#endif //__cym_cerror_hpp__
