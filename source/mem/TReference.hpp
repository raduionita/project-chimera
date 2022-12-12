#ifndef __mem_TReference_hpp__
#define __mem_TReference_hpp__

#include "mem/mem.hpp"

namespace mem {
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

#endif //__mem_TReference_hpp__