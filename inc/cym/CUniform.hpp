#ifndef __cym_cuniform_hpp__
#define __cym_cuniform_hpp__

#include "cym/cym.hpp"

namespace cym {
  class CUniform {
      friend class CShader;
    private:
      std::string mName;
      GLenum      mType       {GL_NONE};
      CShader*    mShader     {nullptr};
      GLint       mLocation   {GL_NOT_FOUND};
      GLboolean   mTransposed {GL_FALSE};
      GLushort    mComponents {0};
    public:
      CUniform();
      ~CUniform();
    public:
      CUniform& operator =(const GLvoid*);
    public:
      void        name(const std::string&);
      std::string name() const;
      void        type(GLenum);
      GLenum      type() const;
      void        shader(CShader*);
      CShader*    shader() const;
      void        location(GLint);
      GLint       location() const;
      void        transposed(GLboolean);
      GLboolean   transposed() const;
      void        components(GLushort);
      GLushort    components() const;
  };
}

// int loc = ::glGetUniformLocation(shader, "u_vColor");
// assert(loc != -1); // either error or opengl optimized it out
// GLCALL(::glUniform4f(loc, 0.2f, 0.3f, 0.5f, 1.0f));

// layout (location = 0) out vec4 o_vColor;
// uniform vec4 u_vColor;
// ...
// o_vColor = u_vColor;

#endif //__cym_cuniform_hpp__
