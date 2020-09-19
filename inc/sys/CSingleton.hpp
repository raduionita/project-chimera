#ifndef __sys_csingleton_hpp__
#define __sys_csingleton_hpp__

#include "sys.hpp"
#include "sys/CPointer.hpp"

#include <cassert>

// @warning
// @todo: this might NOT WORK if TPointer<T> is deleted AFTER TSingleton<T>::sInstance
// @warning

namespace sys {
  template<typename T> class TSingleton {
      template<typename D> class TDeletable {
        public:
          D* mDeletable {nullptr};
        public:
          ~TDeletable() { if (mDeletable) delete mDeletable; }
      };
    protected:
      static TDeletable<T> sInstance;
    public:
      TSingleton() { 
        assert(!sInstance.mDeletable && "TSingleton<>::sIntastace already created");
        sInstance.mDeletable = static_cast<T*>(this);
      }
      virtual ~TSingleton() {
        assert( sInstance.mDeletable && "TSingleton<>::sIntastace already deleted");
        sInstance.mDeletable = nullptr;
      }
    public:
      inline static T* instance() { if (!sInstance.mDeletable) new T; return sInstance.mDeletable; }
  };
  template<typename T> typename TSingleton<T>::template TDeletable<T> TSingleton<T>::sInstance;
}

#endif //__sys_csingleton_hpp__
