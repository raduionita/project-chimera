#ifndef __cerror_hpp__
#define __cerror_hpp__

#include "sys.hpp"

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

#endif //__cerror_hpp__
