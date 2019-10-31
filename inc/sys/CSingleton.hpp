#ifndef __csingleton_hpp__
#define __csingleton_hpp__

#include "sys.hpp"
#include "CPointer.hpp"

#include <cassert>

namespace sys {
  template <typename T> class CSingleton {
    protected:
      static CPointer<T> sInstance;
    public:
      CSingleton() { 
        assert(!sInstance && "CSingleton<T>::sIntastace already defined");
        sInstance = static_cast<T*>(this);
      }
    protected:
      virtual ~CSingleton() { 
        // deleted
      }
    public:
      static auto instance() -> decltype(sInstance) {  if (!sInstance) new T; return sInstance; }
  };
  template<typename T> CPointer<T> CSingleton<T>::sInstance{nullptr};
}

#endif //__csingleton_hpp__
