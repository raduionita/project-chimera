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
      T*        mPointer {nullptr};
      // shared w/ other CPointer's // will inc/dec on all CPointer's w/ same mPointer // @see copy const.
      uint32_t* mCount   {nullptr}; // @todo: should be atomic
    public:
      /* default constructor */
      TPointer() : mPointer{nullptr}, mCount{nullptr} { }
      /* null constructor */
      TPointer(std::nullptr_t) : mPointer{nullptr}, mCount{nullptr} { }
      /* pointer constructor */
      TPointer(T* pPointer) : mPointer{pPointer} { if (mPointer) { mCount = new uint32_t{1}; } }
      /* pointer + count constructor */
      TPointer(T* pPointer, uint32_t* pCount) : mPointer{pPointer}, mCount{pCount} { }
      /* move object into pointer */
      TPointer(T&& tSource) : mPointer{new T{std::move(tSource)}}, mCount{new uint32_t{1}} { }
      /* copy */
      TPointer(const T& tSource)  : mPointer{new T{tSource}}, mCount{new uint32_t{1}} { }
      /* take ownership */
      template <typename Y, typename = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(Y* pPointer) : mPointer{pPointer} { if (mPointer) { mCount = new uint32_t{1}; } }
      /* copy constructor // 2 CPointers will have same mCount */
      TPointer(const TPointer<T,EPointer::SHARED>& that) : mPointer{that.mPointer}, mCount{that.mCount} { if (mPointer) { ++(*mCount); } }
      /* move constructor // 2 CPointers will have same mCount */
      TPointer(TPointer<T,EPointer::SHARED>&& that) : mPointer{std::move(that.mPointer)}, mCount{std::move(that.mCount)} { if (mPointer) { ++(*mCount); } }
      
// @todo: DO NOT ALLOW weak pointer (w/ no info) here

      /* copy weak */
      TPointer(const TPointer<T,EPointer::WEAK>& that) : mPointer{that.mPointer}, mCount{that.mCount} { if (mPointer) { if (!mCount) { that.mCount = mCount = new uint32_t{0}; } ++(*mCount); } }
      /* copy foreign shared */
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(const TPointer<Y,EPointer::SHARED>& that) : mPointer{that.mPointer}, mCount{that.mCount} { if (mPointer) { ++(*mCount); } }
      /* copy foreign weak */
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(const TPointer<Y,EPointer::WEAK>& that) : mPointer{that.mPointer}, mCount{that.mCount} { if (mPointer) { if (!mCount) { that.mCount = mCount = new uint32_t{0}; } ++(*mCount); } }
      
      /* forward to source constructor */
      // template<typename... Args, typename = typename std::enable_if<!std::is_same<Args...,TPointer<T,EPointer::SHARED>>::value>::type> TPointer(Args&&... args) : mPointer{new T{std::forward<Args>(args)...}}, mCount{new uint32_t{1}} { }
      
      /* destructor // decrements mCount // deletes mPointer only if mCount is 0 = nobody else has a ref to it */
      virtual ~TPointer() {
        // std::cout << "TPointer<"<< typeid(T).name() <<">::~TPointer()" << std::endl;
        if ((mCount) && ((--(*mCount)) == 0)) {
          delete mPointer; mPointer = nullptr;
          delete mCount;   mCount   = nullptr;
        }
      }
    public:
      /* null assignment operator */ 
      TPointer<T,EPointer::SHARED>& operator =(std::nullptr_t) {
        if (mCount) {
          if ((*mCount) > 0) {
            // if at zero => remove old refs
            if ((--(*mCount)) == 0) {
              delete mPointer;
              delete mCount;
            }
          }
          // nullify
          mPointer = nullptr;
          mCount   = nullptr;
        } 
        // else keep as is & done
        return *this;
      }
      /* pointer assignment operator */
      TPointer<T,EPointer::SHARED>& operator =(T* pPointer) {
        // make sure u dont reassing/delete existing pointer
        if (mPointer != pPointer) {
          // if this already has a ref => decrement
          if (mCount) {
            if ((*mCount) > 0) {
              // if at zero => remove old refs
              if ((--(*mCount)) == 0) {
                delete mPointer;
                delete mCount;
              }
            }
          }
          // assign...
          mPointer = pPointer;
          if (mPointer) {
            mCount = new uint32_t{1};
          }
        }
        return *this;
        // usage: pObject will try to clear then assign/link to pointer
        // std::CPointer<CClass> pObject = new CClass;
      }
      /* shared assignment operator */
      TPointer<T,EPointer::SHARED>& operator =(const TPointer<T,EPointer::SHARED>& that) {
        // make sure u dont reassing/delete existing pointer
        if (this != &that) {
          if (mCount) {
            // if this already has a ref => decrement
            if ((*mCount) > 0) {
              // if at zero => remove old refs
              if ((--(*mCount)) == 0) {
                delete mPointer;// mPointer = nullptr;
                delete mCount;  // mCount   = nullptr;
              }
            }
          }
          // assign mPointer & mCount & ++mCount
          mPointer = that.mPointer;
          mCount   = that.mCount;
          if (mCount) {
            ++(*mCount);
          }
        }
        // done
        return *this;
        // usage: pObject1 will try to clear then link/ref to pObject0's pointer
        // sys::CPointer<CClass> pObject0{new CClass};
        // sys::CPointer<CClass> pObject1 = {pObject0};
      }
      /* weak assignment operator */
      TPointer<T,EPointer::SHARED>& operator =(const TPointer<T,EPointer::WEAK>& that) {
        if (mCount) {
          if ((*mCount) > 0) {
            // if at zero => remove old refs
            if ((--(*mCount)) == 0) {
              delete mPointer;
              delete mCount;
            }
          }
        }
        // assign mPointer & mCount & ++mCount
        mPointer = that.mPointer;
        mCount   = that.mCount;
        // in case weak is the first
        if (mPointer) {
          if (!mCount) {
            that.mCount = mCount = new uint32_t{0}; 
          }
          ++(*mCount);
        }
        // done
        return *this;
      }
    public: // access operators
      inline T& operator  *() const noexcept { return *mPointer; }
      inline T* operator ->() const noexcept { return  mPointer; }
    public: // bool operators
      inline bool operator ==(std::nullptr_t)       { return mPointer == nullptr; }
      inline bool operator ==(std::nullptr_t) const { return mPointer == nullptr; }
      inline bool operator !=(std::nullptr_t)       { return mPointer != nullptr; }
      inline bool operator !=(std::nullptr_t) const { return mPointer != nullptr; }
      inline bool operator ==(const T* pPointer) { return mPointer == pPointer; }
      inline bool operator ==(const TPointer<T,EPointer::SHARED>& that) { return mPointer == that.mPointer; }
      inline bool operator ==(const TPointer<T,EPointer::WEAK>& that)   { return mPointer == that.mPointer; }
      inline bool operator ==(bool state) { return state ? mPointer != nullptr : mPointer == nullptr; }
      inline bool operator  !() { return mPointer == nullptr; }
    public: // cast operator
      inline          operator     bool() const { return mPointer != nullptr; }
      inline          operator       T*() const { return mPointer;  }
      inline          operator const T*() const { return mPointer;  }
      inline explicit operator        T() const { return *mPointer; }
      inline explicit operator const  T() const { return *mPointer; }
    public:
      inline T*       ptr() const noexcept { return mPointer;  }
      inline T&       raw() const noexcept { return *mPointer; }
      inline T&       ref() const noexcept { return *mPointer; }
      inline uint32_t cnt() const noexcept { return *mCount;   }
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
      template<typename... Args> inline static TPointer fwd(Args&&... args) { return {/*mPointer*/new T{std::forward<Args>(args)...},/*mCount*/new uint32_t{1}}; }
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
      /* default constructor */
      TPointer() : mPointer{nullptr}, mCount{nullptr} { }
      /* null constructor */
      TPointer(std::nullptr_t) : mPointer{nullptr}, mCount{nullptr} { }
      /* pointer constructor */
      TPointer(T* pPointer) : mPointer{pPointer}, mCount{nullptr} { }
      /* pointer + count constructor */
      TPointer(T* pPointer, uint32_t* pCount) : mPointer{pPointer}, mCount{pCount} { }
      /* take ownership*/
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(Y* pPointer) : mPointer{pPointer}, mCount{nullptr} { }
      /* copy weak */
      TPointer(const TPointer<T,EPointer::WEAK>& that) : mPointer{that.mPointer}, mCount{that.mCount} { }
      /* move weak */
      TPointer(TPointer<T,EPointer::WEAK>&& that) : mPointer{std::move(that.mPointer)}, mCount{std::move(that.mCount)} { }
      /* copy shared */
      TPointer(const TPointer<T,EPointer::SHARED>& that) : mPointer{that.mPointer}, mCount{that.mCount} { }
      /* copy foreign weak */
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(const TPointer<Y,EPointer::WEAK>& that) : mPointer{that.mPointer}, mCount{that.mCount} { }
      /* copy foreign shared */
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(const TPointer<Y,EPointer::SHARED>& that) : mPointer{that.mPointer}, mCount{that.mCount} { }
            
      /* forward to source constructor */
      //template<typename... Args> TPointer(Args&&... args) : mPointer{new T{std::forward<Args>(args)...}}, mCount{nullptr} { }
      
      /* destructor */
      virtual ~TPointer() { }
    public: 
      /* pointer assignment operator */
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
      /* weak assignment operator */
      TPointer<T,EPointer::WEAK>& operator =(const TPointer<T,EPointer::WEAK>& that) {
        if (this != &that) {
          mPointer = that.mPointer;
          mCount   = that.mCount;
        }
        // done
        return *this;
      }
      /* shared assignment operator */
      TPointer<T,EPointer::WEAK>& operator =(const TPointer<T,EPointer::SHARED>& that) {
        mPointer = that.mPointer;
        mCount   = that.mCount;
        // done
        return *this;
      }
    public: // access operators
      T& operator  *() const noexcept { return *mPointer; }
      T* operator ->() const noexcept { return  mPointer; }
    public: // bool operators
      bool operator ==(std::nullptr_t)       { return mPointer == nullptr; }
      bool operator ==(std::nullptr_t) const { return mPointer == nullptr; }
      bool operator !=(std::nullptr_t)       { return mPointer != nullptr; }
      bool operator !=(std::nullptr_t) const { return mPointer != nullptr; }
      bool operator ==(const T* pPointer) { return mPointer == pPointer; }
      bool operator ==(const TPointer<T,EPointer::WEAK>& that)   { return mPointer == that.mPointer; }
      bool operator ==(const TPointer<T,EPointer::SHARED>& that) { return mPointer == that.mPointer; }
      bool operator ==(bool state) { return state ? mPointer != nullptr : mPointer == nullptr; }
      bool operator  !() { return mPointer == nullptr; }
    public: // cast operator
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
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CPointerManager {
    protected:
      sys::table<void*, uint32_t*> mPointers;
  };
  
  // sys::spo<CClass> p = this;
    // TPointer::TPointer(CClass*)
      // CPointerManager::register(TPointer& t)
        // void* p = std::reinterpret_cast<TPointer::pointer_type>(t.mPointer);
        // it = find(p)
        // if (it)
          // (*it->second)++;
          // t.mCount = it->second;
        // else
          // t.mCount = ne uint32_t{1};
          // mPointers.insert(p,t.mCount);
  
  // casts ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template <typename Y, typename T> inline TPointer<Y,EPointer::SHARED> static_pointer_cast(const TPointer<T,EPointer::SHARED>& p) { return p.template spc<Y>(); }
  template <typename Y, typename T> inline TPointer<Y,EPointer::WEAK>   static_pointer_cast(const TPointer<T,EPointer::WEAK>& p) { return p.template spc<Y>(); }
  
  template <typename Y, typename T> inline TPointer<Y,EPointer::SHARED> dynamic_pointer_cast(const TPointer<T,EPointer::SHARED>& p) { return p.template dpc<Y>(); }
  template <typename Y, typename T> inline TPointer<Y,EPointer::WEAK> dynamic_pointer_cast(const TPointer<T,EPointer::WEAK>& p) { return p.template dpc<Y>(); }
  
  // debug ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename P, EPointer E> inline std::ostream& operator <<(std::ostream& out, const sys::TPointer<P,E>& ptr) { return out << ptr.ptr(); }
}

#endif //__sys_cpointer_hpp__
