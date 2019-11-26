#ifndef __ogl_cbuffer_hpp__
#define __ogl_cbuffer_hpp__

#include "ogl.hpp"
#include "CObject.hpp"

namespace ogl {
  class CBuffer : public CObject {
    public:
      using CObject::CObject;
  };
  
  class CDataBuffer : public CBuffer {
    public:
      using CBuffer::CBuffer;
    public:
      CDataBuffer();
      template <typename T> CDataBuffer(const T* data, GLcount count, GLenum target, GLenum usage = GL_STATIC_DRAW) { 
        log::nfo << "ogl::CDataBuffer::CDataBuffer(T*,GLcount,GLenum,GLenum)::" << this << log::end;
        GLCALL(::glGenBuffers(1, &mID));
        GLCALL(::glBindBuffer(target, mID));
        GLCALL(::glBufferData(target, count * sizeof(T), data, usage));
      }
      ~CDataBuffer();
  };
  
  /// float vertices[] = { -0.5, -0.5,   +0.5, -0.5,   +0.5, +0.5,   -0.5, +0.5 };
  /// CVertexBuffer vbo{vertices, 4*2*sizeof(float)}; // bound
  /// vbo.bind(false)                                 // unbound
  class CVertexBuffer : public CDataBuffer {
    public:
      using CDataBuffer::CDataBuffer;
    public:
      CVertexBuffer(const GLvoid* data, GLuint size, GLenum usage = GL_STATIC_DRAW);
    public:
      void bind(bool state = true) const override;
  };
  
  /// uint indices[] = { 0,1,2,   2,3,0 };
  // CIndexBuffer ibo{indices, 6); // 6 = 6 vertices // 6 = sizeof(indices) / size(uint)
  class CIndexBuffer : public CDataBuffer {
    public:
      using CDataBuffer::CDataBuffer;
    protected:
      GLuint mCount;
    public:
      CIndexBuffer(const GLuint*, GLuint, GLenum = GL_STATIC_DRAW);
    public:
      void bind(bool state = true) const override;
      // other
      inline GLuint count() const { return mCount; }
  };
}

#endif //__ogl_cbuffer_hpp__
