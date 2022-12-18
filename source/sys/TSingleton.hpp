#ifndef __sys_tsingleton_hpp__
#define __sys_tsingleton_hpp__

namespace sys {
  template<typename T> class TSingleton {
    protected:
      TSingleton() { }
    public:
      inline static T& getSingleton() { static T sSingleton{}; return sSingleton; }
  };
}// namespace sys

#endif //__sys_tsingleton_hpp__