#ifndef __sys_cpointer_hpp__
#define __sys_cpointer_hpp__

#include "sys/sys.hpp"

#include <type_traits>
#include <atomic>
#include <ostream>

namespace sys {
  template<typename T, EPointer E> class TPointer { };

  template<typename T> class TPointer<T, EPointer::SHARED> {
    public:
      using EType = EPointer;
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
      TPointer(T* pPointer) : mPointer{pPointer}, mCount{new uint32_t{1}} { }
      // pointer + count constructor
      TPointer(T* pPointer, uint32_t* pCount) : mPointer{pPointer}, mCount{pCount} { }
      // move object into pointer
      TPointer(T&& oObject) : mPointer{new T{std::move(oObject)}}, mCount{new uint32_t{1}} { }
      // copy
      TPointer(const T& oObject)  : mPointer{new T{oObject}}, mCount{new uint32_t{1}} { }
      // take ownership
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(Y* pPointer) : mPointer{pPointer}, mCount{new uint32_t{0}} { if (mPointer) { ++(*mCount); } }
      // copy constructor // 2 CPointers will have same mCount
      TPointer(const TPointer<T,EPointer::SHARED>& that) : mPointer{that.mPointer}, mCount{that.mCount} { if (mPointer) { ++(*mCount); } }
      // copy weak
      
// @todo: DO NOT ALLOW weak pointer (w/ no info) here
      
      TPointer(const TPointer<T,EPointer::WEAK>& that)   : mPointer{that.mPointer}, mCount{that.mCount} { if (mPointer) { ++(*mCount); } if (!mCount) { that.mCount = mCount = new uint32_t{1}; } }
      // copy foreign shared
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(const TPointer<Y,EPointer::SHARED>& that) : mPointer{that.mPointer}, mCount{that.mCount} { if (mPointer) { ++(*mCount); } }
      // copy foreign weak
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(const TPointer<Y,EPointer::WEAK>& that) : mPointer{that.mPointer}, mCount{that.mCount} { if (mPointer) { ++(*mCount); } if (!mCount) { that.mCount = mCount = new uint32_t{1}; } }
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
      TPointer<T,EPointer::SHARED>& operator =(const TPointer<T,EPointer::SHARED>& that) {
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
        // done
        return *this;
        // usage: pObject1 will try to clear then link/ref to pObject0's pointer
        // sys::CPointer<CClass> pObject0{new CClass};
        // sys::CPointer<CClass> pObject1 = {pObject0};
      }
      TPointer<T,EPointer::SHARED>& operator =(const TPointer<T,EPointer::WEAK>& that) {
        if ((*mCount) != 0) {
          --(*mCount);
        }
        if ((*mCount) == 0) {
          delete mPointer; mPointer = nullptr;
          delete mCount;   mCount   = nullptr;
        }
        // assign mPointer & mCount & ++mCount
        mPointer = that.mPointer;
        mCount   = that.mCount;
        // in case weak is the first
        if (!mCount) {
          that.mCount = mCount = new uint32_t{0};
        }
        ++(*mCount);
        // done
        return *this;
      }
      // assignment operator
      TPointer<T,EPointer::SHARED>& operator =(T* pPointer) {
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
      bool operator ==(std::nullptr_t)       { return mPointer == nullptr; }
      bool operator ==(std::nullptr_t) const { return mPointer == nullptr; }
      bool operator !=(std::nullptr_t)       { return mPointer != nullptr; }
      bool operator !=(std::nullptr_t) const { return mPointer != nullptr; }
      bool operator ==(const T* pPointer) { return mPointer == pPointer; }
      bool operator ==(const TPointer<T,EPointer::SHARED>& that) { return mPointer == that.mPointer; }
      bool operator ==(const TPointer<T,EPointer::WEAK>& that)   { return mPointer == that.mPointer; }
      bool operator ==(bool state) { return state ? mPointer != nullptr : mPointer == nullptr; }
      bool operator  !() { return mPointer == nullptr; }
      // cast operator
      operator     bool() const { return mPointer != nullptr; }
      operator       T*() const { return mPointer;  }
      operator const T*() const { return mPointer;  }
      operator        T() const { return *mPointer; }
      operator const  T() const { return *mPointer; }
    public:
      T*       ptr() const noexcept { return mPointer;  }
      T&       raw() const noexcept { return *mPointer; }
      T&       ref() const noexcept { return *mPointer; }
      uint32_t cnt() const noexcept { return *mCount;   }
      template <typename Y> TPointer<Y,EPointer::SHARED> spc() const {
        if (mPointer) {
          ++(*mCount);
          return TPointer<Y,EPointer::SHARED>(static_cast<Y*>(mPointer), mCount);
        } else {
          return TPointer<Y,EPointer::SHARED>();
        }
      }
      template <typename Y> TPointer<Y,EPointer::SHARED> dpc() const {
        Y* pPointer = dynamic_cast<Y*>(mPointer);
        if (pPointer) {
          ++(*mCount);
          return TPointer<Y,EPointer::SHARED>(pPointer, mCount);
        } else {
          return TPointer<Y,EPointer::SHARED>();
        }
      }
    public:
      template <typename Y, EPointer F> friend class TPointer;
      template <typename Y> friend TPointer<Y,EPointer::SHARED> static_pointer_cast(const TPointer<T,EPointer::SHARED>& p);
      template <typename Y> friend TPointer<Y,EPointer::SHARED> dynamic_pointer_cast(const TPointer<T,EPointer::SHARED>& p);
    public:
      template<typename P> friend std::ostream& operator <<(std::ostream& out, TPointer<P,EPointer::SHARED>& ptr);
  };
  
  template<typename T> class TPointer<T, EPointer::WEAK> {
    public:
      using EType = EPointer;
    public:
      typedef T   type;
      typedef T   template_type; // 
      typedef T*  pointer_type;
    protected:
      // the payload
      T*        mPointer {nullptr};
      uint32_t* mCount   {nullptr}; // @todo: should be atomic
    public:
      // default constructor
      TPointer() : mPointer{nullptr}, mCount{nullptr} { }
      // null constructor
      TPointer(std::nullptr_t) : mPointer{nullptr}, mCount{nullptr} { }
      // pointer constructor
      TPointer(T* pPointer) : mPointer{pPointer}, mCount{nullptr} { }
      // pointer + count constructor
      TPointer(T* pPointer, uint32_t* pCount) : mPointer{pPointer}, mCount{pCount} { }
      // move object into pointer
      TPointer(T&& oObject) : mPointer{new T{std::move(oObject)}}, mCount{nullptr} { }
      // copy
      TPointer(const T& oObject)  : mPointer{new T{oObject}}, mCount{nullptr} { }
      // take ownership
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(Y* pPointer) : mPointer{pPointer}, mCount{nullptr} { }
      // copy weak
      TPointer(const TPointer<T,EPointer::WEAK>& that) : mPointer{that.mPointer}, mCount{that.mCount} { }
      // copy shared
      TPointer(const TPointer<T,EPointer::SHARED>& that) : mPointer{that.mPointer}, mCount{that.mCount} { }
      // copy foreign weak
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(const TPointer<Y,EPointer::WEAK>& that) : mPointer{that.mPointer}, mCount{that.mCount} { }
      // copy foreign shared
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(const TPointer<Y,EPointer::SHARED>& that) : mPointer{that.mPointer}, mCount{that.mCount} { }
      // destructor
      virtual ~TPointer() { }
    public:
      // assignment operator
      TPointer<T,EPointer::WEAK>& operator =(const TPointer<T,EPointer::WEAK>& that) {
        if (this != &that) {
          mPointer = that.mPointer;
          mCount   = that.mCount;
        }
        // done
        return *this;
      }
      TPointer<T,EPointer::WEAK>& operator =(const TPointer<T,EPointer::SHARED>& that) {
        mPointer = that.mPointer;
        mCount   = that.mCount;
        // done
        return *this;
      }
      // assignment operator
      TPointer<T,EPointer::WEAK>& operator =(T* pPointer) {
        // make sure u dont reassing/delete existing pointer
        if (mPointer != pPointer) {
          mPointer = pPointer;
          mCount   = nullptr;
        }
        // done
        return *this;
        // usage: pObject will try to clear then assign/link to pointer
        // std::CPointer<CClass> pObject = new CClass;
      }
      // access operators
      T& operator  *() const noexcept { return *mPointer; }
      T* operator ->() const noexcept { return  mPointer; }
      // bool operators
      bool operator ==(std::nullptr_t)       { return mPointer == nullptr; }
      bool operator ==(std::nullptr_t) const { return mPointer == nullptr; }
      bool operator !=(std::nullptr_t)       { return mPointer != nullptr; }
      bool operator !=(std::nullptr_t) const { return mPointer != nullptr; }
      bool operator ==(const T* pPointer) { return mPointer == pPointer; }
      bool operator ==(const TPointer<T,EPointer::WEAK>& that)   { return mPointer == that.mPointer; }
      bool operator ==(const TPointer<T,EPointer::SHARED>& that) { return mPointer == that.mPointer; }
      bool operator ==(bool state) { return state ? mPointer != nullptr : mPointer == nullptr; }
      bool operator  !() { return mPointer == nullptr; }
      // cast operator
      operator     bool() const { return mPointer != nullptr; }
      operator       T*() const { return mPointer;  }
      operator const T*() const { return mPointer;  }
      operator        T() const { return *mPointer; }
      operator const  T() const { return *mPointer; }
    public:
      T*       ptr() const noexcept { return mPointer;  }
      T&       raw() const noexcept { return *mPointer; }
      T&       ref() const noexcept { return *mPointer; }
      uint32_t cnt() const noexcept { return mCount ? *mCount : 0; }
      template <typename Y> TPointer<Y,EPointer::WEAK> spc() const {
        if (mPointer) {
          return TPointer<Y,EPointer::WEAK>(static_cast<Y*>(mPointer), mCount);
        } else {
          return TPointer<Y,EPointer::WEAK>();
        }
      }
      template <typename Y> TPointer<Y,EPointer::WEAK> dpc() const {
        Y* pPointer = dynamic_cast<Y*>(mPointer);
        if (pPointer) {
          return TPointer<Y,EPointer::WEAK>(pPointer, mCount);
        } else {
          return TPointer<Y,EPointer::WEAK>();
        }
      }
    public:
      template <typename Y, EPointer F> friend class TPointer;
      template <typename Y> friend TPointer<Y,EPointer::WEAK> static_pointer_cast(const TPointer<T,EPointer::WEAK>& p);
      template <typename Y> friend TPointer<Y,EPointer::WEAK> dynamic_pointer_cast(const TPointer<T,EPointer::WEAK>& p);
    public:
      template<typename P> friend std::ostream& operator <<(std::ostream& out, TPointer<P,EPointer::WEAK>& ptr);
  };
  
  template <typename Y, typename T> inline TPointer<Y,EPointer::SHARED> static_pointer_cast(const TPointer<T,EPointer::SHARED>& p) { return p.template spc<Y>(); }
  template <typename Y, typename T> inline TPointer<Y,EPointer::WEAK>   static_pointer_cast(const TPointer<T,EPointer::WEAK>& p) { return p.template spc<Y>(); }
  
  template <typename Y, typename T> inline TPointer<Y,EPointer::SHARED> dynamic_pointer_cast(const TPointer<T,EPointer::SHARED>& p) { return p.template dpc<Y>(); }
  template <typename Y, typename T> inline TPointer<Y,EPointer::WEAK> dynamic_pointer_cast(const TPointer<T,EPointer::WEAK>& p) { return p.template dpc<Y>(); }
  
  template<typename P, EPointer E> inline std::ostream& operator <<(std::ostream& out, const sys::TPointer<P,E>& ptr) { return out << ptr.ptr(); }
}

#endif //__sys_cpointer_hpp__
