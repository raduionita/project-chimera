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
      typedef uint size_type;
      typedef A    alloc_type;
    protected:
      static A sAlloc;            // static std::allocator<TPieceFree<T>> sAlloc;
      uint     mCount  {0};       // mLength
      uint     mNext   {0};       // mNext
      T*       mData   {nullptr}; // mData    // TBlockPiece<T>* mData;
    public:
      TBlock() = default;
      TBlock(uint c)             : mCount{c}, mNext{0}, mData{sAlloc.allocate(c)} { }
      TBlock(T* d, uint c)       : mCount{c}, mNext{0}, mData{d}                  { }
      TBlock(TBlock&& that)      : mCount{std::move(that.mCount)}, mNext{std::move(that.mNext)}, mData{sAlloc.allocate(mCount)} { 
        // log::nfo << "sys::TBlock<>::TBlock(TBlock&&)::"<< this << "::c=" << mCount << "::n=" << mNext << log::end;
        for (uint i = 0; i < mNext; i++) 
          sAlloc.construct(mData+mNext,std::forward<T>(std::move(that.mData[i])));
      }
      TBlock(const TBlock& that) : mCount{that.mCount}, mNext{that.mNext}, mData{sAlloc.allocate(mCount)} { 
        // log::nfo << "sys::TBlock<>::~TBlock(TBlock&)::"<< this << "::c=" << mCount << "::n=" << mNext << log::end;
        for (uint i = 0; i < mNext; i++) 
          sAlloc.construct(mData+i,that.mData[i]);
      }
      virtual ~TBlock() { 
        // log::nfo << "sys::TBlock<>::~TBlock()::" << this << "::c=" << mCount << "::n=" << mNext << log::end;
        free(); 
      }
    public:
      // assign operator
      TBlock& operator =(const TBlock& that) {
        // log::nfo << "sys::TBlock<>::operator=(TBlock&)::"<< this << "::c=" << mCount << "::n=" << mNext << log::end;
        if (&that == this)
          return *this;
        // @todo: for (uint i = 0; i < mNext; i++)
        // @todo:   mData[i] = that.mData[i]
        alloc(that.mCount);
        mNext  = that.mNext;
        mCount = that.mCount;
        for (uint i = 0; i < mNext; i++) 
          sAlloc.construct(mData+i,that.mData[i]);
        return *this;
      };
      TBlock& operator =(TBlock&& that) {
        // log::nfo << "sys::TBlock<>::operator=(TBlock&&)::"<< this << "::c=" << mCount << "::n=" << mNext << log::end;
        if (&that == this)
          return *this;
        alloc(that.mCount);
        mCount = std::move(that.mCount);
        mNext  = std::move(that.mNext);
        for (uint i = 0; i < mNext; i++)
          sAlloc.construct(mData+i,std::forward<T>(that.mData[i]));
        return *this;
      };
      // add operator
      TBlock& operator +(T&& e)      { return push(std::move(e)); *this; }
      TBlock& operator +(const T& e) { return push(e);            *this; }
      // index operator
            T& operator [](uint i)       { assert(i<mCount); return mData[i]; }
      const T& operator [](uint i) const { assert(i<mCount); return mData[i]; }
      // cast operator 
      explicit operator       T*()       { if (!fit()) shrink(); return (      T*)mData; }
      explicit operator const T*() const { if (!fit()) shrink(); return (const T*)mData; }
    public:
      inline bool fit()      const { return mNext == mCount; }
      inline uint size()     const { return mNext; }
      inline bool empty()    const { return mNext == 0; }
      inline uint usage()    const { return (mNext-1) * sizeof(T); }
      inline uint capacity() const { return mCount; }
      inline T*   data()     const { return mData; }
      
      void push(T&& e) { 
        // log::nfo << "sys::TBlock<>::push(T&&)::c=" << mCount << "::n=" << mNext << log::end;
        if (mNext == mCount)
          extend(2 + (mCount / 2) + (mCount / 2) % 2);
        sAlloc.construct(mData+mNext,std::forward<T>(e));
        ++mNext;
      }
      
      void push(const T& e) { 
        // log::nfo << "sys::TBlock<>::push(T&)::c=" << mCount << "::n=" << mNext << log::end;
        if (mNext == mCount)
          extend(2 + (mCount / 2) + (mCount / 2) % 2);
        sAlloc.construct(mData+mNext,e);
        ++mNext;
      }
        
      void extend(int c = 2) {
        // log::nfo << "sys::TBlock<>::extend("<< c <<")::c=" << mCount << "::n=" << mNext << log::end;
        if (c < 1)
          return; 
        c += mCount; 
        T* pTemp = sAlloc.allocate(c);
        for (uint i = 0; i < mNext; i++) 
          std::memcpy(pTemp+i, mData+i, sizeof(T)); // sAlloc.construct(pTemp+i,mData[i]);
        sAlloc.deallocate(mData,mCount); 
        mCount = c; 
        mData = pTemp; 
      }
      
      void shrink() {
        // log::nfo << "sys::TBlock<>::shrink()::c=" << mCount << "::n=" << mNext << log::end;
        mCount = mNext;
        T* pTemp = nullptr;
        if (mCount > 0)
          pTemp = sAlloc.allocate(mCount);
        for (uint i = 0; i < mNext; i++) 
          std::memcpy(pTemp+i, mData+i, sizeof(T)); // sAlloc.construct(pTemp+i,mData[i]);
        sAlloc.deallocate(mData,mCount); 
        mData = pTemp; 
      }
      
      void clear() { 
        // log::nfo << "sys::TBlock<>::clear()::c=" << mCount << "::n=" << mNext << log::end;
        if (mCount == 0) 
          return;
        for (uint i = 0; i < mNext; i++)
          sAlloc.destroy(mData+i);
        mNext = 0;
      }
      
      void free() {
        // log::nfo << "sys::TBlock<>::free()::"<< this << "::c=" << mCount << "::n=" << mNext << log::end;
        if (mCount == 0) 
          return;
        for (uint i = 0; i < mNext; i++)
          sAlloc.destroy(mData+i);
        sAlloc.deallocate(mData,mCount);
        mData  = nullptr; 
        mCount = 0; 
        mNext  = 0; 
      }
      
      void begin();
      void cbegin();
      void rbegin();
      void end();
      void cend();
      void rend();
    protected:
      void alloc(uint c = 2) {
        // log::nfo << "sys::TBlock<>::alloc(" << c << ")::c=" << mCount << "::n=" << mNext << log::end;
        if (c < 1)
          return;
        for (uint i = 0; i < mNext; i++)
          sAlloc.destroy(mData+i);
        if (mCount > 0)
          sAlloc.deallocate(mData,mCount);
        mCount = c;
        mData = sAlloc.allocate(mCount);
        mNext = 0;
      }
  };
  
  template<typename T, typename A> A TBlock<T,A>::sAlloc;
}

#endif //__sys_cblock_hpp__
