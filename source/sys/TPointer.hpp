#ifndef __sys_tpointer_hpp__
#define __sys_tpointer_hpp__

#include "sys/sys.hpp"

#include <memory>

namespace sys {
  template <typename T> class TReference;
//template <typename T> class TPointer;
  template <typename T> using TPointer = std::shared_ptr<T>;

  template <typename T> using ptr = TPointer<T>;
  template <typename T> using ref = TReference<T>;

  // class TPointer { };

  template <typename T> class TReference {
    public:
      typedef T  type;
      typedef T  template_t;
      typedef T* pointer_t;
    protected:
      T* mPointer {nullptr};
    public:
      TReference(TPointer<T> pPointer) : mPointer{pPointer.get()} {

      }
  };

} // namespace sys

#endif //__sys_tpointer_hpp__