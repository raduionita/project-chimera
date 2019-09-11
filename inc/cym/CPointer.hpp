#ifndef __cym_cpointer_hpp__
#define __cym_cpointer_hpp__

#include "cym.hpp"

namespace cym {
  template <typename T> class CPointer {
    protected:
    // the payload
    T*        mPointer;
    // shared w/ other CPointer's // will inc/dec on all CPointer's w/ same mPointer // @see copy const.
    uint32_t* mCount;  
    
    public:
    // default constructor
    CPointer() : mPointer{nullptr}, mCount{new uint32_t{0}} { }
    // null constructor
    CPointer(std::nullptr_t) : mPointer{nullptr}, mCount{new uint32_t{0}} { }
    // pointer constructor
    CPointer(T* pPointer) : mPointer{pPointer}, mCount{new uint32_t{1}} { }
    // copy constructor // 2 CPointers will have same mCount
    CPointer(const CPointer& that) : mPointer{that.mPointer}, mCount{that.mCount} { ++(*mCount); }
    // destructor // decrements mCount // deletes mPointer only if mCount is 0 = nobody else has a ref to it
    virtual ~CPointer() {
      if (--(*mCount) == 0) {
        delete mPointer; mPointer = nullptr;
        delete mCount;   mCount   = nullptr;
      }
    }
  
    public:
    // assignment operator
    CPointer& operator =(const CPointer& that) {
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
    CPointer& operator =(T* pPointer) {
      // make sure u dont reassing/delete existing pointer
      if (mPointer != pPointer) {
        // if this already has a ref => decrement
        if ((*mCount) != 0) {
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
    T& operator  *() { return *mPointer; }
    T* operator ->() { return  mPointer; }
    // bool operators
    bool operator ==(std::nullptr_t) { return mPointer == nullptr; }
    bool operator ==(const T* pPointer) { return mPointer == pPointer; }
    bool operator ==(const CPointer& that) { return mPointer == that.mPointer; }
    bool operator ==(bool state) { return state ? mPointer != nullptr : mPointer == nullptr; }
    bool operator  !() { return mPointer == nullptr; }
    // cast operator
    operator bool() const { return mPointer != nullptr; }
    operator   T*() const { return mPointer; }
    operator    T() const { return *mPointer; }
    // pointer
    T* ptr() const noexcept { return mPointer; }
  };
  
  template<typename T> using ptr = cym::CPointer<T>;
}

#endif //__cym_cpointer_hpp__
