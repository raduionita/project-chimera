#ifndef __sys_tsingleton_hpp__
#define __sys_tsingleton_hpp__

#include "sys.hpp"

// @warning
// @todo: this might NOT WORK if TPointer<T> is deleted AFTER TSingleton<T>::sSingleton
// @warning

namespace sys {
  template<typename T> class TSingleton {
    protected:
      TSingleton() { }
    public:
      inline static T& getSingleton() { static T sSingleton{}; return sSingleton; }
  };
}

#endif //__sys_tsingleton_hpp__
