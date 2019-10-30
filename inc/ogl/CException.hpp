#ifndef __ogl_cexception_hpp__
#define __ogl_cexception_hpp__

#include "sys/CException.hpp" 

namespace ogl {
  class CException : public sys::CException {
    public:
      using sys::CException::CException;
  };
}

#endif //__ogl_cexception_hpp__
