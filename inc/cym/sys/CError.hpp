#ifndef __cym_sys_cerror_hpp__
#define __cym_sys_cerror_hpp__

namespace cym { namespace sys {
  class CError {
    protected:
      CError* mOriginal = {nullptr};
      int     mCode     = {0};
    public:
      CError();
      virtual ~CError();
  };
}}

#endif //__cym_sys_cerror_hpp__
