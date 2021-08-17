#include "cym/CDataBuffer.hpp"
#include "cym/CGeometry.hpp"

namespace cym {
  CDeviceBuffer::~CDeviceBuffer() {
    // SYS_LOG_NFO("cym::CDeviceBuffer::~CDeviceBuffer()::" << this);
    GLCALL(::glDeleteBuffers(1, &mID));
  }
  
  CDataBuffer::CDataBuffer() {
    // SYS_LOG_NFO("cym::CDataBuffer::CDataBuffer()::" << this);
    GLCALL(::glGenBuffers(1, &mID));
  }
  
  CDataBuffer::~CDataBuffer() {
    // SYS_LOG_NFO("cym::CDataBuffer::~CDataBuffer()::" << this);
    GLCALL(::glDeleteBuffers(1, &mID));
  }
  
  GLcount CDataBuffer::data(cym::CGeometryInput* in) {
    return data(in->data(), in->size());
  }
}
