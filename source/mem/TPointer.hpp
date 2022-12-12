#ifndef __mem_TPointer_hpp__
#define __mem_TPointer_hpp__

#include "mem/mem.hpp" 
#include <atomic>

namespace mem {
  template<typename T> class TPointer {
      typedef std::atomic_uint32_t C;
    private:
      T* mPointer;
      C* mCounter;
    public:
      // ctor null
      TPointer() : mPointer{nullptr}, mCounter{nullptr} { }
      // ctor null
      TPointer(std::nullptr_t) : mPointer{nullptr}, mCounter{nullptr} { }
      // ctor

      // dtor
      ~TPointer() { }
    public:
      // asgn null
      TPointer& operator =(std::nullptr_t) {
        // TODO: ..
        return *this;
      } 
    private:
      void reg() {  
        //
      }

      void unr() {

      }
  };
} // namespace mem

#endif //__mem_TPointer_hpp__
