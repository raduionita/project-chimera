#ifndef __sys_cstream_hpp__
#define __sys_cstream_hpp__

#include "sys/sys.hpp"

namespace sys {
  class CStream {
    public:
      enum EFlag : sys::bitfield { FREECLOSE = 0b00000001, READONLY  = 0b00000010, };
    protected:
      uint   mOpts {0};
      byte*  mData {nullptr};
      byte*  mCurr {nullptr};
      byte*  mEnds {nullptr};
    public:
      CStream() = default;
      virtual ~CStream();
      CStream(byte* ptr, size_t size, uint flags = 0);
      CStream(size_t size, uint flags = 0);
    public: // inline
      inline byte* ptr() const { return mCurr; }
      inline bool  empty() const { return size() == 0; }
      inline size_t size() const { return (mEnds - mData); }
    public:
      byte* data(byte*, size_t, uint = 0);
      byte* data(size_t, uint = 0);
  };
  
}

#endif //__sys_cstream_hpp__
