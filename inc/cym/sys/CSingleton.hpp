#ifndef __cym_sys_csingleton_hpp__
#define __cym_sys_csingleton_hpp__

#include "sys.hpp"
#include "CPointer.hpp"

namespace cym { namespace sys {
  template <typename T> class CSingleton {
    protected:
      static CPointer<T> sInstance;
    protected:
      CSingleton() { }
      virtual ~CSingleton() { }
    public:
      static auto instance() -> decltype(sInstance) {
        if (!sInstance) sInstance = new T;
        return sInstance;
      }
  };
  template<typename T> CPointer<T> CSingleton<T>::sInstance{nullptr};
}}

#endif //__cym_sys_csingleton_hpp__
