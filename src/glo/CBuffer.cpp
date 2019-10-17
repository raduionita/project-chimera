#include "glo/CBuffer.hpp"

namespace glo {
  
  CBuffer::~CBuffer() {
    GLCALL(::glDeleteBuffers(1, &mID));
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CVertexBuffer::CVertexBuffer(const GLvoid* data, GLuint size, GLenum usage/*=GL_STATIC_DRAW*/) {
    GLCALL(::glGenBuffers(1, &mID));
    GLCALL(::glBindBuffer(GL_ARRAY_BUFFER, mID));
    GLCALL(::glBufferData(GL_ARRAY_BUFFER, size, data, usage));
    // size = vert_count * components_per_vert * sizeof(float)
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CIndexBuffer::CIndexBuffer(const GLuint* data, GLuint count, GLenum usage/*=GL_STATIC_DRAW*/) : mCount{count} {
    GLCALL(::glGenBuffers(1, &mID));
    GLCALL(::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID));
    GLCALL(::glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, usage));
  }
}
