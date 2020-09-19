#include "cym/CBuffer.hpp"

namespace cym {
  CDataBuffer::CDataBuffer() {
    log::nfo << "cym::CDataBuffer::CDataBuffer()::" << this << log::end;
    GLCALL(::glGenBuffers(1, &mID));
  }
  
  CDataBuffer::~CDataBuffer() {
    log::nfo << "cym::CDataBuffer::~CDataBuffer()::" << this << log::end;
    GLCALL(::glDeleteBuffers(1, &mID));
  }
}
