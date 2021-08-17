#ifndef __sys_csingleton_hpp__
#define __sys_csingleton_hpp__

#include "sys.hpp"
#include "sys/TPointer.hpp"

#include <cassert>

// @warning
// @todo: this might NOT WORK if TPointer<T> is deleted AFTER TSingleton<T>::sSingleton
// @warning

namespace sys {
  template<typename T> class TSingleton {
      template<typename D> class TDeletable {
        public:
          D* mDeletable {nullptr};
        public:
          inline TDeletable() = default;
          inline ~TDeletable() { if (mDeletable) delete mDeletable; }
      };
    private:
      static TDeletable<T> sSingleton;
    public:
      TSingleton() {
        // std::cout << "TSingleton<" << typeid(T).name() << ">::TSingleton()" << std::endl;
        assert(!sSingleton.mDeletable && "TSingleton<>::sIntastace already created");
        sSingleton.mDeletable = static_cast<T*>(this);
      }
      virtual ~TSingleton() {
        // std::cout << "TSingleton<" << typeid(T).name() << ">::~TSingleton()" << std::endl;
        assert(sSingleton.mDeletable && "TSingleton<>::sIntastace already deleted");
        sSingleton.mDeletable = nullptr;
      }
    public:
      inline static sys::wpo<T> getSingleton() { if (!sSingleton.mDeletable) new T; return sSingleton.mDeletable; }
  };
  template<typename T> typename TSingleton<T>::template TDeletable<T> TSingleton<T>::sSingleton;
}

#endif //__sys_csingleton_hpp__
