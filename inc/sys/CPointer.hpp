#ifndef __sys_cpointer_hpp__
#define __sys_cpointer_hpp__

#include "sys.hpp"

#include <type_traits>
#include <atomic>

namespace sys {
  class CPointer {
    public:
      CPointer() = default;
      virtual ~CPointer() = default;
  };
  
  template<typename T> class TPointer : public CPointer {
    public:
      typedef T   type;
      typedef T   template_type; // 
      typedef T*  pointer_type;
    protected:
      // the payload
      T*        mPointer;
      // shared w/ other CPointer's // will inc/dec on all CPointer's w/ same mPointer // @see copy const.
      uint32_t* mCount; // @todo: should be atomic
    public:
      // default constructor
      TPointer() : mPointer{nullptr}, mCount{new uint32_t{0}} { }
      // null constructor
      TPointer(std::nullptr_t) : mPointer{nullptr}, mCount{new uint32_t{0}} { }
      // pointer constructor
      TPointer(T* pPointer) : mPointer{pPointer}, mCount{new uint32_t{1}} { std::cout << "TPointer<"<< typeid(T).name() <<">::TPointer(T*)" << pPointer << std::endl; }
      // pointer + count constructor
      TPointer(T* pPointer, uint32_t* pCount) : mPointer{pPointer}, mCount{pCount} { }
      // move object into pointer
      TPointer(T&& oObject) : mPointer{new T{std::move(oObject)}}, mCount{new uint32_t{1}} { }
      TPointer(const T& oObject)  : mPointer{new T{std::move(oObject)}}, mCount{new uint32_t{1}} { }
      // take ownership
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(Y* pPointer) : mPointer{pPointer}, mCount{new uint32_t{0}} { if (mPointer) { ++(*mCount); } }
      // copy constructor // 2 CPointers will have same mCount
      TPointer(const TPointer& that) : mPointer{that.mPointer}, mCount{that.mCount} { if (mPointer) { ++(*mCount); } }
      // copy foreign constructor
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(const TPointer<Y>& that) : mPointer{that.mPointer}, mCount{that.mCount} { if (mPointer) { ++(*mCount); } }
      // destructor // decrements mCount // deletes mPointer only if mCount is 0 = nobody else has a ref to it
      virtual ~TPointer() {
        // std::cout << "TPointer<"<< typeid(T).name() <<">::~TPointer()" << std::endl;
        if (--(*mCount) == 0) {
          delete mPointer; mPointer = nullptr;
          delete mCount;   mCount   = nullptr;
        }
    }
    public:
      // assignment operator
      TPointer& operator =(const TPointer& that) {
        // make sure u dont reassing/delete existing pointer
        if (this != &that) {
          // if this already has a ref => decrement
          if ((*mCount) != 0) {
            --(*mCount);
          }
          // if at zero => remove old refs
          if ((*mCount) == 0) {
            delete mPointer; mPointer = nullptr;
            delete mCount;   mCount   = nullptr;
          }
          // assign mPointer & mCount & ++mCount
          mPointer = that.mPointer;
          mCount   = that.mCount;
          ++(*mCount);
        }
        return *this;
        // usage: pObject1 will try to clear then link/ref to pObject0's pointer
        // sys::CPointer<CClass> pObject0{new CClass};
        // sys::CPointer<CClass> pObject1 = {pObject0};
      }
      // assignment operator
      TPointer& operator =(T* pPointer) {
        std::cout << "TPointer<"<< typeid(T).name() <<">::operator =(T*)" << pPointer << std::endl;
        // make sure u dont reassing/delete existing pointer
        if (mPointer != pPointer) {
          // if this already has a ref => decrement
          if ((*mCount) > 0) {
            --(*mCount);
          }
          // if at zero => remove old refs
          if ((*mCount) == 0) {
            delete mPointer; mPointer = nullptr;
            delete mCount;   mCount   = nullptr;
          }
          // assign...
          mPointer = pPointer;
          mCount   = new uint32_t{1};
        }
        return *this;
        // usage: pObject will try to clear then assign/link to pointer
        // std::CPointer<CClass> pObject = new CClass;
      }
      // access operators
      T& operator  *() const noexcept { return *mPointer; }
      T* operator ->() const noexcept { return  mPointer; }
      // bool operators
      bool operator ==(std::nullptr_t) { return mPointer == nullptr; }
      bool operator ==(const T* pPointer) { return mPointer == pPointer; }
      bool operator ==(const TPointer& that) { return mPointer == that.mPointer; }
      bool operator ==(bool state) { return state ? mPointer != nullptr : mPointer == nullptr; }
      bool operator  !() { return mPointer == nullptr; }
      // cast operator
      operator     bool() const { return mPointer != nullptr; }
      operator       T*() const { return mPointer;  }
      operator const T*() const { return mPointer;  }
      operator        T() const { return *mPointer; }
      operator const  T() const { return *mPointer; }
      // delete
      // void operator delete(void*) {}
      // pointer
      T*       ptr() const noexcept { return mPointer; }
      uint32_t cnt() const noexcept { return *mCount;   }
      template <typename Y> TPointer<Y> spc() const {
        if (mPointer) {
          ++(*mCount);
          return TPointer<Y>(static_cast<Y*>(mPointer), mCount);
        } else {
          return TPointer<Y>();
        }
      }
      template <typename Y> TPointer<Y> dpc() const {
        Y* pPointer = dynamic_cast<Y*>(mPointer);
        if (pPointer) {
          ++(*mCount);
          return TPointer<Y>(pPointer, mCount);
        } else {
          return TPointer<Y>();
        }
      }
    public:
      template <typename Y> friend class TPointer;
      template <typename Y> friend TPointer<Y> static_pointer_cast(const TPointer<T>& p);
      template <typename Y> friend TPointer<Y> dynamic_pointer_cast(const TPointer<T>& p);
  };
  
  template <typename Y, typename T> inline TPointer<Y> static_pointer_cast(const TPointer<T>& p) { return p.template spc<Y>(); }
  
  template <typename Y, typename T> inline TPointer<Y> dynamic_pointer_cast(const TPointer<T>& p) { return p.template dpc<Y>(); }
}

#endif //__sys_cpointer_hpp__
