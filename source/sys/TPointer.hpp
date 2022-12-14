#ifndef __sys_tpointer_hpp__
#define __sys_tpointer_hpp__

#include "sys/sys.hpp" 

#include <atomic>

namespace sys {
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
} // namespace sys

#endif //__sys_tpointer_hpp__
