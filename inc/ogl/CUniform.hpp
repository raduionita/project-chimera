#ifndef __ogl_cuniform_hpp__
#define __ogl_cuniform_hpp__

namespace ogl {
  class CUniform {
      
  };
}

// int loc = ::glGetUniformLocation(shader, "u_vColor");
// assert(loc != -1); // either error or opengl optimized it out
// GLCALL(::glUniform4f(loc, 0.2f, 0.3f, 0.5f, 1.0f));

// layout (location = 0) out vec4 o_vColor;
// uniform vec4 u_vColor;
// ...
// o_vColor = u_vColor;

#endif //__ogl_cuniform_hpp__
