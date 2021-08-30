#ifndef __sys_tclonable_hpp__
#define __sys_tclonable_hpp__

namespace sys {
  template<typename T> class TClonable {
    private:
      T mOriginal;
    public:
      virtual T clone(T&) = 0;
  };
}

#endif //__sys_tclonable_hpp__
