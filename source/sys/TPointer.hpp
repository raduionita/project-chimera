#ifndef __sys_tpointer_hpp__
#define __sys_tpointer_hpp__

#include "sys/sys.hpp" 

#include <atomic>

namespace sys {
  template<typename T> class TPointer  {
      typedef std::atomic_uint32_t C;
      friend class TReference<T>;
    protected:
      T* mPointer {nullptr};
      C* mCounter {nullptr};
    public:
      // ctor null
      TPointer()               : mPointer{nullptr}, mCounter{nullptr} {}
      // ctor null
      TPointer(std::nullptr_t) : mPointer{nullptr}, mCounter{nullptr} {}
      // ctor pointer
      TPointer(T* pPointer) : mPointer{pPointer} { if (mPointer) { mCounter = new C{1}; } }
      // ctor copy value
      TPointer(const T& tValue)  : mPointer{new T{tValue}}, mCounter{new C{1}} {}
      // ctor move value
      TPointer(T&& tValue) : mPointer{new T{std::move(tValue)}}, mCounter{new C{1}} {}
      // ctor copy
      TPointer(const TPointer& that) : mPointer{that.mPointer}, mCounter{that.mCounter} { if (mPointer) { ++(*mCounter); } }
      // ctor move
      TPointer(TPointer&& that) : mPointer{std::move(that.mPointer)}, mCounter{std::move(that.mCounter)} { if (mPointer) { ++(*mCounter); } }
      // dtor
      ~TPointer() {
          if ((mCounter) && ((--(*mCounter)) == 0)) {
              delete mPointer; mPointer = nullptr;
              delete mCounter; mCounter = nullptr;
          }
      }
    public:
      // asgn null
      TPointer& operator =(std::nullptr_t) {
          if (mCounter) {
              if ((*mCounter) > 0 && (--(*mCounter)) == 0) {
                  delete mPointer;
                  delete mCounter;
              }
              mPointer = nullptr;
              mCounter = nullptr;
          }
          return *this;
      }
      // asgn pointer // std::CPointer<CClass> pObject = new CClass;
      TPointer& operator =(T* pPointer) {
          // make sure u dont reassing/delete existing pointer
          if (mPointer != pPointer) {
              // if this already has a ref => decrement
              if (mCounter && (*mCounter) > 0 && (--(*mCounter)) == 0) {
                  // if at zero => remove old refs
                  delete mPointer;
                  delete mCounter;
              }
              // assign...
              mPointer = pPointer;
              mCounter = nullptr;
              if (mPointer) {
                  mCounter = new C{1};
              }
          }
          return *this;
      }
      // asgn copy
      TPointer& operator =(const TPointer& that) {
          // make sure u dont reassing/delete existing pointer
          if (this != &that) {
              if (mCounter && (*mCounter) > 0 && (--(*mCounter)) == 0) {
                  // if at zero => remove old refs
                  delete mPointer; // mPointer = nullptr;
                  delete mCounter; // mCounter = nullptr;
              }
              // assign mPointer & mCount & ++mCount
              mPointer = that.mPointer;
              mCounter = that.mCounter;
              if (mCounter) {
                  ++(*mCounter);
              }
          }
          // done
          return *this;
          // usage: pObject1 will try to clear then link/ref to pObject0's pointer
          // sys::CPointer<CClass> pObject0{new CClass};
          // sys::CPointer<CClass> pObject1 = {pObject0};
      }
    public: // access operators
      inline const T& operator  *() const noexcept { return *mPointer; }
      inline       T* operator ->() const noexcept { return  mPointer; }
    public:
      template<typename ...Args> static TPointer make(Args&&...args) { return TPointer<T>{new T{std::forward<Args>(args)...}}; }
  };
} // namespace sys

#endif //__sys_tpointer_hpp__
