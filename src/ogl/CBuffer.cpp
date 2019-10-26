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
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CVertexBuffer::CVertexBuffer(const GLvoid* data, GLuint size, GLenum usage/*=GL_STATIC_DRAW*/) {
    log::nfo << "ogl::CVertexBuffer::CVertexBuffer(GLvoid*,GLuint,GLenum)::" << this << " ID:" << mID << " TARGET:" << GL_ARRAY_BUFFER << log::end;
    // @see: CDataBuffer::CDataBuffer() for GLCALL(::glGenBuffers(1, &mID));
    GLCALL(::glBindBuffer(GL_ARRAY_BUFFER, mID));
    GLCALL(::glBufferData(GL_ARRAY_BUFFER, size, data, usage));
    // size = vert_count * components_per_vert * sizeof(float)
  }
  
  void CVertexBuffer::bind(bool state/*=true*/) const { 
    log::dbg << "ogl::CVertexBuffer::bind(bool)::" << this << " ID:" << mID << " TARGET:" << GL_ARRAY_BUFFER << log::end;
    GLCALL(::glBindBuffer(GL_ARRAY_BUFFER, state ? mID : 0)); 
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CIndexBuffer::CIndexBuffer(const GLuint* data, GLuint count, GLenum usage/*=GL_STATIC_DRAW*/) : mCount{count} {
    log::nfo << "ogl::CIndexBuffer::CIndexBuffer(GLuint*,GLuint,GLenum)::" << this << " ID:" << mID << " TARGET:" << GL_ELEMENT_ARRAY_BUFFER << log::end;
    // @see: CDataBuffer::CDataBuffer() for GLCALL(::glGenBuffers(1, &mID));
    GLCALL(::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID));
    GLCALL(::glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, usage));
  }
  
  void CIndexBuffer::bind(bool state/*=true*/) const { 
    log::dbg << "ogl::CIndexBuffer::bind(bool)::" << this << " ID:" << mID << " TARGET:" << GL_ELEMENT_ARRAY_BUFFER << log::end;
    GLCALL(::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state ? mID : 0)); 
  }
}
