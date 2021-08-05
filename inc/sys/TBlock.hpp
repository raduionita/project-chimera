#ifndef __sys_cblock_hpp__
#define __sys_cblock_hpp__

#include "sys/sys.hpp"
#include "sys/CLogger.hpp"
#include "sys/CException.hpp"

#include <utility>
#include <cassert>
#include <cstring>

namespace sys {
  template<typename T, typename A = std::allocator<T>> class TBlock {
    public:
      typedef uint                     size_type;
      typedef A                        alloc_type;
      typedef T                        data_type;
      typedef std::allocator_traits<A> traits_type;
    protected:
      static A sAlloc;            // static std::allocator<TPieceFree<T>> sAlloc;
      uint     mCount  {0};       // mLength
      uint     mLast   {0};       // mNext
      T*       mData   {nullptr}; // mData    // TBlockPiece<T>* mData;
    public:
      TBlock() = default;
      TBlock(uint c)             : mCount{c}, mLast{0}, mData{traits_type::allocate(sAlloc,c)} { }
      TBlock(T* d, uint c)       : mCount{c}, mLast{0}, mData{d}                  { }
      TBlock(TBlock&& that)      : mCount{std::move(that.mCount)}, mLast{std::move(that.mLast)}, mData{traits_type::allocate(sAlloc,mCount)} { 
        // CYM_LOG_NFO("sys::TBlock<>::TBlock(TBlock&&)::"<< this << "::c=" << mCount << "::n=" << mNext);
        for (uint i = 0; i < mLast; i++) 
          sAlloc.construct(mData + mLast, std::forward<T>(std::move(that.mData[i])));
      }
      TBlock(const TBlock& that) : mCount{that.mCount}, mLast{that.mLast}, mData{traits_type::allocate(sAlloc,mCount)} { 
        // CYM_LOG_NFO("sys::TBlock<>::~TBlock(TBlock&)::"<< this << "::c=" << mCount << "::n=" << mNext);
        for (uint i = 0; i < mLast; i++) 
          traits_type::construct(sAlloc, mData+i,that.mData[i]);
          // sAlloc.construct(mData+i,that.mData[i]);
      }
      virtual ~TBlock() { 
        // CYM_LOG_NFO("sys::TBlock<>::~TBlock()::" << this << "::c=" << mCount << "::n=" << mNext);
        free(); 
      }
    public:
      // assign operator
      TBlock& operator =(const TBlock& that) {
        // CYM_LOG_NFO("sys::TBlock<>::operator=(TBlock&)::"<< this << "::c=" << mCount << "::n=" << mNext);
        if (&that == this)
          return *this;
        // @todo: for (uint i = 0; i < mNext; i++)
        // @todo:   mData[i] = that.mData[i]
        alloc(that.mCount);
        mLast  = that.mLast;
        mCount = that.mCount;
        for (uint i = 0; i < mLast; i++) 
          sAlloc.construct(mData+i,that.mData[i]);
        return *this;
      };
      TBlock& operator =(TBlock&& that) {
        // CYM_LOG_NFO("sys::TBlock<>::operator=(TBlock&&)::"<< this << "::c=" << mCount << "::n=" << mNext);
        if (&that == this)
          return *this;
        alloc(that.mCount);
        mCount = std::move(that.mCount);
        mLast  = std::move(that.mLast);
        for (uint i = 0; i < mLast; i++)
          sAlloc.construct(mData+i,std::forward<T>(that.mData[i]));
        return *this;
      };
      // add operator
      TBlock& operator +(T&& e)      { return push(std::move(e)); *this; }
      TBlock& operator +(const T& e) { return push(e);            *this; }
      // index operator
            T& operator [](uint i)       { assert(i < mLast); return mData[i]; }
      const T& operator [](uint i) const { assert(i < mLast); return mData[i]; }
      // cast operator 
      explicit operator       T*()       { if (!fit()) shrink(); return (      T*)mData; }
      explicit operator const T*() const { if (!fit()) shrink(); return (const T*)mData; }
      // dereference operator
      T& operator  *() const noexcept { return *mData; }
      T* operator ->() const noexcept { return  mData; }
    public:
      inline bool fit()      const { return mLast == mCount; }
      inline uint size()     const { return mLast; }
      inline bool empty()    const { return mLast == 0; }
      inline uint usage()    const { return (mLast - 1) * sizeof(T); }
      inline uint capacity() const { return mCount; }
      inline uint vacant()   const { return mCount - mLast; } 
      inline T*   data()     const { return mData; }
      
      void push(T&& e) { 
        // CYM_LOG_NFO("sys::TBlock<>::push(T&&)::c=" << mCount << "::n=" << mNext);
        if (mLast == mCount)
          extend(2 + (mCount / 2) + (mCount / 2) % 2);
        // sAlloc.construct(mData + mLast, std::forward<T>(e));
        traits_type::construct(sAlloc, mData+mLast, std::forward<T>(e));
        ++mLast;
      }
      
      void push(const T& e) { 
        // CYM_LOG_NFO("sys::TBlock<>::push(T&)::c=" << mCount << "::n=" << mNext);
        if (mLast == mCount)
          extend(2 + (mCount / 2) + (mCount / 2) % 2);
        // sAlloc.construct(mData + mLast, e);
        traits_type::construct(sAlloc, mData+mLast, e);
        ++mLast;
      }
      
      void push(const T a[], uint n) {
        if (mCount - mLast < n)
          extend(n + (n / 2) % 2);
        for (uint i = 0; i < n; i++, mLast++)
          // sAlloc.construct(mData + mLast, a[i]);
          traits_type::construct(sAlloc, mData+mLast, a[i]);
      }
      
      template<typename... Args> T& next(Args&&... args) {
        if (mLast == mCount)
          extend(2 + (mCount / 2) + (mCount / 2) % 2);
        // sAlloc.construct(mData+mLast, std::forward<Args>(args)...);
        traits_type::construct(sAlloc, mData+mLast, std::forward<Args>(args)...);
        ++mLast;
        return mData[mLast - 1];
      }
      
      void pull(uint e) {
        assert(e < mLast);
        sAlloc.destroy(mData+e);
        mLast--;
        if (e < mLast - 1)
          for (uint i = e; i < mLast; i++)
            // std::memmove(mData+i, mData+i+1, sizeof(T));
            std::uninitialized_move_n(mData+i, 1, mData+i+1);
      }
      
      void reserve(int c = 2) {
        if (mCount - mLast < c)
          extend(c - mCount - mLast);
      }
      
      void extend(int c = 2) {
        // CYM_LOG_NFO("sys::TBlock<>::extend("<< c <<")::c=" << mCount << "::l=" << mLast);
        if (c < 1)
          return;
        c += mCount;
        // new block
        T* pTemp = std::allocator_traits<A>::allocate(sAlloc,c);
        // copy
        std::uninitialized_move(mData, mData+mLast, pTemp);
        // delete old one
        std::allocator_traits<A>::deallocate(sAlloc,mData,mCount);
        mCount = c; 
        mData = pTemp;
      }
      
      void shrink() {
        // CYM_LOG_NFO("sys::TBlock<>::shrink()::c=" << mCount << "::n=" << mNext);
        mCount = mLast;
        T* pTemp = nullptr;
        // new block
        if (mCount > 0)
          pTemp = std::allocator_traits<A>::allocate(sAlloc,mCount);
        // copy
        std::uninitialized_move(mData, mData+mLast, pTemp);
        // remove old
        std::allocator_traits<A>::deallocate(sAlloc,mData,mCount);
        mData = pTemp; 
      }
      
      void clear() { 
        // CYM_LOG_NFO("sys::TBlock<>::clear()::c=" << mCount << "::n=" << mNext);
        if (mCount == 0) 
          return;
        for (uint i = 0; i < mLast; i++)
          // sAlloc.destroy(mData+i);
          traits_type::destroy(sAlloc, mData+i);
        mLast = 0;
      }
      
      void free() {
        // CYM_LOG_NFO("sys::TBlock<>::free()::"<< this << "::c=" << mCount << "::n=" << mNext);
        if (mCount == 0) 
          return;
        for (uint i = 0; i < mLast; i++)
          // sAlloc.destroy(mData+i);
          traits_type::destroy(sAlloc, mData+i);
        std::allocator_traits<A>::deallocate(sAlloc,mData,mCount);
        mData  = nullptr; 
        mCount = 0;
        mLast  = 0; 
      }
      
      // void begin();
      // void cbegin();
      // void rbegin();
      // void end();
      // void cend();
      // void rend();
    protected:
      void alloc(uint c = 2) {
        // CYM_LOG_NFO("sys::TBlock<>::alloc(" << c << ")::c=" << mCount << "::n=" << mNext);
        if (c < 1)
          return;
        for (uint i = 0; i < mLast; i++)
          // sAlloc.destroy(mData+i);
          traits_type::destroy(sAlloc, mData+i);
        if (mCount > 0)
          std::allocator_traits<A>::deallocate(sAlloc,mData,mCount);
        mCount = c;
        mData = std::allocator_traits<A>::allocate(sAlloc,mCount);
        mLast = 0;
      }
  };
  
  template<typename T, typename A> A TBlock<T,A>::sAlloc;
}

#endif //__sys_cblock_hpp__
