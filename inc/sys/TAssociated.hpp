#ifndef __sys_creference_hpp__
#define __sys_creference_hpp__

#include "sys/sys.hpp"

namespace sys {
  template<typename T> class TAssociated {
    protected:
      bool mInited    {false};
      T*   mReference {nullptr};
    public:
      TAssociated() { }
      TAssociated(T& tReference) : mInited{true}, mReference{&tReference} { }
      virtual ~TAssociated() { if (!mInited && mReference != nullptr) { delete mReference; } };
    public:
      TAssociated& operator =(T& tReference) { mReference = &tReference; mInited = true; return *this; }
    public:
      T&    operator  *() const noexcept { if (!mInited && mReference == nullptr) { mReference = new T; } return *mReference; }
    public:
      operator        T() const { if (!mInited && mReference == nullptr) { mReference = new T; } return *mReference; }
      operator const  T() const { if (!mInited && mReference == nullptr) { mReference = new T; } return *mReference; }
  };
  
  template<typename T> using asc = TAssociated<T>;
}

#endif //__sys_creference_hpp__
