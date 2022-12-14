#ifndef __sys_treference_hpp__
#define __sys_treference_hpp__

#include "sys/sys.hpp"

namespace sys {
  template<typename T> class TReference {
    private:
      T& mReference;
    public:
      TReference(T& rReference) : mReference{rReference} { 
        // sdasd
      }
      ~TReference() = default;
  };
} // namespace mem

#endif //__sys_treference_hpp__