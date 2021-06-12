#include "cym/CDataBuffer.hpp"
#include "cym/CGeometry.hpp"

namespace cym {
  CDataBuffer::CDataBuffer() {
    CYM_LOG_NFO("cym::CDataBuffer::CDataBuffer()::" << this);
    GLCALL(::glGenBuffers(1, &mID));
  }
  
  CDataBuffer::~CDataBuffer() {
    GLCALL(::glDeleteBuffers(1, &mID));
  }
  
  GLcount CDataBuffer::data(cym::CGeometryInput* in) {
    return data(in->data(), in->size());
  }
}
