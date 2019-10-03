#ifndef __cym_ogl_ccontext_hpp__
#define __cym_ogl_ccontext_hpp__

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>

#include "khr.hpp"

#include <stdio.h>

typedef HGLRC(WINAPI * wglCreateContextAttribsARB_t) (HDC,HGLRC,CONST INT*);
typedef BOOL (WINAPI * wglChoosePixelFormatARB_t)    (HDC,CONST INT*,CONST FLOAT*,UINT,INT*,UINT*);

#define DEFINE_WGL_FUNCTION(name) name##_t name = reinterpret_cast<name##_t>(::wglGetProcAddress(#name))

#define OGL_SUCCESS 0

namespace cym::ogl {
  extern int OGL_VERSION_MAJOR;
  extern int OGL_VERSION_MINOR;
  extern int OGL_VERSION_1_0;
  extern int OGL_VERSION_1_1;
  extern int OGL_VERSION_1_2;
  extern int OGL_VERSION_1_3;
  extern int OGL_VERSION_1_4;
  extern int OGL_VERSION_1_5;
  extern int OGL_VERSION_2_0;
  extern int OGL_VERSION_2_1;
  extern int OGL_VERSION_3_0;
  extern int OGL_VERSION_3_1;
  extern int OGL_VERSION_3_2;
  extern int OGL_VERSION_3_3;
  extern int OGL_VERSION_4_0;
  extern int OGL_VERSION_4_1;
  extern int OGL_VERSION_4_2;
  extern int OGL_VERSION_4_3;
  extern int OGL_VERSION_4_4;
  extern int OGL_VERSION_4_5;
  extern int OGL_VERSION_4_6;
  
  struct SVersion { int major{0}, minor{0}; };
  
  extern void     version(int&, int&);
  
  extern SVersion version();
  
  extern bool     load();
}

#endif //__cym_ogl_ccontext_hpp__
