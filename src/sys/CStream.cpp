#include "sys/CStream.hpp"
#include "sys/CException.hpp"

namespace sys {
  CStream::CStream(size_t size, sys::uint flags) {
    data(size,flags);
  }
  
  CStream::~CStream() {
    delete [] mData;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  byte* CStream::data(byte* data, size_t size, uint flags/*=0*/) {
    sys::throw_if(data == nullptr, "Cannot use null data pointer!",__FILE__,__LINE__);
    sys::throw_if(mData != nullptr, "Non-empty stream can't be reused!",__FILE__,__LINE__);
    sys::throw_if(size == 0, "Cannot allocate 0 bytes!",__FILE__,__LINE__);
    mSize = size;
    mOpts = flags; 
    mData = data;
    mCurr = mData;
    mEnds = mData + size;
// @todo: check size > 0
// @todo: check mEnds >= mData
    return mData;
  }
  
  byte* CStream::data(size_t size, uint flags/*=0*/) {
    sys::throw_if(mData != nullptr, "Non-empty stream can't be reused!",__FILE__,__LINE__);
    sys::throw_if(size == 0, "Cannot allocate 0 bytes!",__FILE__,__LINE__);
    mSize = size;
    mOpts = flags; 
    mData = new byte[size];
    mCurr = mData;
    mEnds = mData + size;
// @todo: check size > 0
// @todo: check mEnds >= mData
    return mData;
  }
}
