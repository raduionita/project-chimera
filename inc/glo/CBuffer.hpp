#ifndef __glo_cbuffer_hpp__
#define __glo_cbuffer_hpp__

#include "glo.hpp"
#include "CObject.hpp"

namespace glo {
  class CBuffer : public CObject {
    public:
      ~CBuffer();
  };
  
  /// float vertices[] = { -0.5, -0.5,   +0.5, -0.5,   +0.5, +0.5,   -0.5, +0.5 };
  /// CVertexBuffer vbo{vertices, 4*2*sizeof(float)}; // bound
  /// vbo.bind(false)                                 // unbound
  class CVertexBuffer : public CBuffer {
    public:
      CVertexBuffer(const GLvoid*, GLuint, GLenum = GL_STATIC_DRAW);
    public:
      inline void bind(bool state = true) const override { GLCALL(::glBindBuffer(GL_ARRAY_BUFFER, state ? mID : 0)); }
  };
  
  /// uint indices[] = { 0,1,2,   2,3,0 };
  // CIndexBuffer ibo{indices, 6); // 6 = 6 vertices // 6 = sizeof(indices) / size(uint)
  class CIndexBuffer : public CBuffer {
    protected:
      GLuint mCount;
    public:
      CIndexBuffer(const GLuint*, GLuint, GLenum = GL_STATIC_DRAW);
    public:
      inline void bind(bool state = true) const override { GLCALL(::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state ? mID : 0)); }
      // other
      inline GLuint count() const { return mCount; }
  };
}

#endif //__glo_cbuffer_hpp__
