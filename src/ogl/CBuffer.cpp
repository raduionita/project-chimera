#include "ogl/CBuffer.hpp"

namespace ogl {
  CDataBuffer::CDataBuffer() {
    log::nfo << "ogl::CDataBuffer::CDataBuffer()::" << this << log::end;
    GLCALL(::glGenBuffers(1, &mID));
  }
  
  CDataBuffer::~CDataBuffer() {
    log::nfo << "ogl::CDataBuffer::~CDataBuffer()::" << this << log::end;
    GLCALL(::glDeleteBuffers(1, &mID));
  }
}
