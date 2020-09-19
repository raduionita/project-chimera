#ifndef __cym_cexception_hpp__
#define __cym_cexception_hpp__

#include "sys/CException.hpp" 

namespace cym {
  class CException : public sys::CException {
    public:
      using sys::CException::CException;
  };
}

#endif //__cym_cexception_hpp__
