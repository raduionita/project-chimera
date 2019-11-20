#ifndef __sys_cstream_hpp__
#define __sys_cstream_hpp__

#include "sys/sys.hpp"

namespace sys {
  class CStream; typedef sys::CPointer<CStream> PStream;
  
  class CStream {
    public:
      enum EFlag : sys::bitfield {
        FREECLOSE = 0b00000001,
        READONLY  = 0b00000010,
      };
    protected:
      size_t mSize {0};
      uint   mOpts {0};
      ubyte* mData {nullptr};
      ubyte* mCurr {nullptr};
      ubyte* mEnds {nullptr};
    public:
      CStream() = default;
      virtual ~CStream() = default;
      CStream(void* ptr, size_t size, uint flags = 0);
      CStream(size_t size, uint flags = 0);
    public: // inline
      inline ubyte* ptr() const { return mCurr; }
      inline bool   empty() const { return mSize == 0; }
    public:
      ubyte* data(size_t, uint = 0);
  };
  
}

#endif //__sys_cstream_hpp__
