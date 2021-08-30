#ifndef __sys_cpointer_hpp__
#define __sys_cpointer_hpp__

#include "sys/sys.hpp"

#include <type_traits>
#include <atomic>
#include <ostream>

namespace sys {
  
// @TODO research if extending CPointerManager is possible
//       CGeometryManager extends CPointerManager
//       typedef sys::ptr<CGeometry,CGeometryManager> PGeometry; // attach pointer manager class
//       when CGeometryManager gets deleted it also deletes all the pointers
//       the remaining "dangling" wrapped pointers will already be nullptr
// @TODO this may require *pointers and *counters to be stored only in the manager NOT inside TPointer
  
  // class CPointerManager; 
  // class CDefaultPointerManager : public CPointerManager; 
  
  // pointer /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// @TODO replace CPointer w/ a signleton CPointerManager, and put everything in the header and inline
  
  class CPointer {
    private:
      static sys::table<intptr_t,uint32_t*> sPointers;
    protected:
      /* register pointer & counter // store pointer & new counter */
      static void reg(void* p, uint32_t*& c);
      /* unregister pointer // return true if realy was deleted */
      static bool unr(void* p);
  };
  
  template<typename T> class TPointer : public CPointer {
    public:
      typedef T         type;
      typedef T         template_t; 
      typedef T*        pointer_t;
      typedef uint32_t* counter_t;
    protected:
      // the payload
      T*        mPointer {nullptr};
      // shared w/ other CPointer's // will inc/dec on all CPointer's w/ same mPointer // @see copy const.
      uint32_t* mCounter {nullptr}; // @todo: should be atomic
    public:
      /* default constructor */
      TPointer() : mPointer{nullptr}, mCounter{nullptr} { /* DON'T MANAGE */ }
      /* null constructor */
      TPointer(std::nullptr_t) : mPointer{nullptr}, mCounter{nullptr} { /* DON'T MANAGE */ }
      /* pointer constructor */
      TPointer(T* pPointer) : mPointer{pPointer} { if (mPointer) { reg(mPointer,mCounter); /*mCount = new uint32_t{1};*/ } }
      /* pointer + count constructor */
      TPointer(T* pPointer, uint32_t* pCount) : mPointer{pPointer}, mCounter{pCount} { /* DON'T MANAGE */ }
      /* copy */
      TPointer(const T& tSource)  : mPointer{new T{tSource}}/*, mCounter{new uint32_t{1}}*/ { reg(mPointer,mCounter); }
      /* move object into pointer */
      TPointer(T&& tSource) : mPointer{new T{std::move(tSource)}}/*, mCount{new uint32_t{1}}*/ { reg(mPointer,mCounter); }
      /* take ownership */
      template <typename Y, typename = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(Y* pPointer) : mPointer{pPointer} { if (mPointer) { reg(mPointer,mCounter); /*mCounter = new uint32_t{1};*/ } }
      /* copy constructor // 2 CPointers will have same mCount */
      TPointer(const TPointer<T>& that) : mPointer{that.mPointer}, mCounter{that.mCounter} { if (mPointer) { ++(*mCounter); } }
      /* move constructor // 2 CPointers will have same mCount */
      TPointer(TPointer<T>&& that) : mPointer{std::move(that.mPointer)}, mCounter{std::move(that.mCounter)} { if (mPointer) { ++(*mCounter); } }
      
      /* copy foreign TPoiner */
      template <typename Y, class = typename std::enable_if<std::is_convertible<Y*,T*>::value>::type> TPointer(const TPointer<Y>& that) : mPointer{that.mPointer}, mCounter{that.mCounter} { if (mPointer) { ++(*mCounter); } }
      
      /* forward to source constructor */
      // template<typename... Args, typename = typename std::enable_if<!std::is_same<Args...,TPointer<T>>::value>::type> TPointer(Args&&... args) : mPointer{new T{std::forward<Args>(args)...}}, mCount{new uint32_t{1}} { }
      
      /* destructor // decrements mCount // deletes mPointer only if mCount is 0 = nobody else has a ref to it */
      virtual ~TPointer() {
        // std::cout << "TPointer<"<< typeid(T).name() <<">::~TPointer()" << std::endl;
        if ((mCounter) && ((--(*mCounter)) == 0)) {
          unr(mPointer);
          delete mPointer; mPointer = nullptr;
          delete mCounter; mCounter = nullptr;
        }
      }
    public:
      /* null assignment operator */ 
      TPointer<T>& operator =(std::nullptr_t) {
        if (mCounter) {
          if ((*mCounter) > 0 && (--(*mCounter)) == 0) {
            // if at zero => remove old refs
            unr(mPointer);
            delete mPointer;
            delete mCounter;
          }
          // nullify
          mPointer = nullptr;
          mCounter = nullptr;
        } 
        // else keep as is & done
        return *this;
      }
      /* pointer assignment operator */
      TPointer<T>& operator =(T* pPointer) {
        // make sure u dont reassing/delete existing pointer
        if (mPointer != pPointer) {
          // if this already has a ref => decrement
          if (mCounter) {
            if ((*mCounter) > 0 && (--(*mCounter)) == 0) {
              // if at zero => remove old refs
              unr(mPointer);
              delete mPointer;
              delete mCounter;
            }
          }
          // assign...
          mPointer = pPointer;
          if (mPointer) {
            reg(mPointer,mCounter);
            /*mCounter = new uint32_t{1};*/
          }
        }
        return *this;
        // usage: pObject will try to clear then assign/link to pointer
        // std::CPointer<CClass> pObject = new CClass;
      }
      /* */
      // TPointer<T>& operator =(T*&& pPpointer)
      /* shared assignment operator */
      TPointer<T>& operator =(const TPointer<T>& that) {
        // make sure u dont reassing/delete existing pointer
        if (this != &that) {
          if (mCounter) {
            // if this already has a ref => decrement
            if ((*mCounter) > 0 && (--(*mCounter)) == 0) {
              // if at zero => remove old refs
              unr(mPointer);
              delete mPointer; // mPointer = nullptr;
              delete mCounter; // mCounter = nullptr;
            }
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
      inline T& operator  *() const noexcept { return *mPointer; }
      inline T* operator ->() const noexcept { return  mPointer; }
    public: // bool operators
      inline bool operator ==(std::nullptr_t)       { return mPointer == nullptr; }
      inline bool operator ==(std::nullptr_t) const { return mPointer == nullptr; }
      inline bool operator !=(std::nullptr_t)       { return mPointer != nullptr; }
      inline bool operator !=(std::nullptr_t) const { return mPointer != nullptr; }
      inline bool operator ==(const T* pPointer) { return mPointer == pPointer; }
      inline bool operator ==(const TPointer<T>& that) { return mPointer == that.mPointer; }
      inline bool operator ==(bool state)              { return state ? mPointer != nullptr : mPointer == nullptr; }
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
      inline uint32_t cnt() const noexcept { return *mCounter; }
      template <typename Y> TPointer<Y> spc() const {
        if (mPointer) {
          ++(*mCounter);
          return TPointer<Y>(static_cast<Y*>(mPointer), mCounter);
        } else {
          return TPointer<Y>();
        }
      }
      template <typename Y> TPointer<Y> dpc() const {
        Y* pPointer {dynamic_cast<Y*>(mPointer)};
        if (pPointer) {
          ++(*mCounter);
          return TPointer<Y>(pPointer, mCounter);
        } else {
          return TPointer<Y>();
        }
      }
    public:
      /* forward args to T(...) // -> TPointer(T*) */
      template<typename... Args> inline static TPointer fwd(Args&&... args) { return {/*mPointer*/new T{std::forward<Args>(args)...}}; }
    public:
      template <typename Y> friend class TPointer;
      template <typename Y> friend TPointer<Y> static_pointer_cast(const TPointer<T>& p);
      template <typename Y> friend TPointer<Y> dynamic_pointer_cast(const TPointer<T>& p);
    public:
      template<typename P> friend std::ostream& operator <<(std::ostream& out, const TPointer<P>& ptr);
  };
  
  // casts ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template <typename Y, typename T> inline TPointer<Y> static_pointer_cast(const TPointer<T>& p) { return p.template spc<Y>(); }
  
  template <typename Y, typename T> inline TPointer<Y> dynamic_pointer_cast(const TPointer<T>& p) { return p.template dpc<Y>(); }
  
  // debug ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename P> std::ostream& operator <<(std::ostream& out, const sys::TPointer<P>& ptr) { return out << ptr.ptr(); }
}

#endif //__sys_cpointer_hpp__
