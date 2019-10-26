#ifndef __glo_cexception_hpp__
#define __glo_cexception_hpp__

#include "sys/CException.hpp" 

namespace glo {
  class CException : public sys::CException {
    public:
      using CException::CException;
  };
}

#endif //__glo_cexception_hpp__
