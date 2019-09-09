#ifndef __cym_sys_csingleton_hpp__
#define __cym_sys_csingleton_hpp__

#include "sys.hpp"
#include "CPointer.hpp"

#include <cassert>

namespace cym { namespace sys {
  template <typename T> class CSingleton {
    protected:
    static CPointer<T> sInstance;
    
    protected:
    CSingleton() { assert(!sInstance && "CSingleton<T>::sIntastace already defined"); }
    virtual ~CSingleton() { }
    
    public:
    static auto instance() -> decltype(sInstance) { return (!sInstance) ? sInstance = new T : sInstance; }
  };
  template<typename T> CPointer<T> CSingleton<T>::sInstance{nullptr};
}}

#endif //__cym_sys_csingleton_hpp__
