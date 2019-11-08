#ifndef __sys_cstream_hpp__
#define __sys_cstream_hpp__

#include "sys/sys.hpp"

namespace sys {
  class CStream {
    public:
      enum EOption : sys::bitfield {
        FREECLOSE = 0b00000001,
        READONLY  = 0b00000010,
      }; 
    protected:
      ubyte* mStart;
      ubyte* mCursor;
      ubyte* mLast;
    public:
      CStream(void* mem, size_t size, uint options = 0);
      virtual ~CStream();
  };
  
  // class CDataStream;
  // class CMemoryStream : public CDataStream;
  // class CFileStream : public CDataStream;
  
  typedef sys::CPointer<CStream> PStream;
}

#endif //__sys_cstream_hpp__
