#ifndef __glo_cbuffer_hpp__
#define __glo_cbuffer_hpp__

#include "glo.hpp"

namespace glo {
  class CBuffer {
    protected:
      GLuint mID;
    public:
      virtual ~CBuffer();
    public:
      virtual void bind(bool=true) const = 0;
      virtual void link()          const = 0;
      virtual void free()          const = 0;
  };
  
  template <typename T>
  class TBuffer : public CBuffer {
      
  };
  
  /// float vertices[] = { -0.5, -0.5,   +0.5, -0.5,   +0.5, +0.5,   -0.5, +0.5 };
  /// CVertexBuffer vbo{vertices, 4*2*sizeof(float)}; // bound
  /// vbo.bind(false)                                 // unbound
  class CVertexBuffer : public TBuffer<GLfloat> {
    public:
      CVertexBuffer(const GLvoid*, GLuint, GLenum = GL_STATIC_DRAW);
    public:
      inline void bind(bool state = true) const { GLCALL(::glBindBuffer(GL_ARRAY_BUFFER, state ? mID : 0)); }
      inline void link()                  const { bind(true);  }
      inline void free()                  const { bind(false); }
  };
  
  /// uint indices[] = { 0,1,2,   2,3,0 };
  // CIndexBuffer ibo{indices, 6); // 6 = 6 vertices // 6 = sizeof(indices) / size(uint)
  class CIndexBuffer : public TBuffer<GLuint> {
    protected:
      GLuint mCount;
    public:
      CIndexBuffer(const GLuint*, GLuint, GLenum = GL_STATIC_DRAW);
    public:
      inline void bind(bool state = true) const { GLCALL(::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state ? mID : 0)); }
      inline void link()                  const { bind(true);  }
      inline void free()                  const { bind(false); }
      // other
      inline GLuint count() const { return mCount; }
  };
}

#endif //__glo_cbuffer_hpp__
