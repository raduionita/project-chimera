#include "sys/CStream.hpp"
#include "sys/CException.hpp"

namespace sys {
  CStream::CStream(size_t size, sys::uint flags) {
    data(size,flags);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  ubyte* CStream::data(size_t size, uint flags/*=0*/) {
    sys::throw_if(mData != nullptr, "Non-empty stream can't be reused!",__FILE__,__LINE__);
    mSize = size;
    mOpts = flags; 
    mData = new ubyte[size];
    mCurr = mData;
    mEnds = mData + size;
// @todo: check size > 0
// @todo: check mEnds >= mData
    return mData;
  }
}
