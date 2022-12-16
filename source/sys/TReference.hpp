#ifndef __sys_treference_hpp__
#define __sys_treference_hpp__

#include "sys/sys.hpp"

namespace sys {
  template <typename T> class TReference {
      friend class TPointer<T>;
    protected:
      T*& mReference;
    public:
      TReference(TPointer<T>& pPointer) : mReference{pPointer} { };
      TReference(TReference& that) : mReference{that.mReference} { };
      TReference(const T&&) = delete;
    public:
      inline T*& operator ->() const noexcept { return mReference; }
      inline T&  operator  *() const noexcept { return *mReference; }
  };
} // namespace mem

#endif //__sys_treference_hpp__