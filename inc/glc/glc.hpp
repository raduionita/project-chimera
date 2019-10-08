#ifndef __ogl_hpp__
#define __ogl_hpp__

#if defined(__glew_h__) || defined(__GLEW_H__)
#error Attempt to include auto-generated header after including glew.h
#endif
#if defined(__gl_h_) || defined(__GL_H__)
#error Attempt to include auto-generated header after including gl.h
#endif
#if defined(__glext_h_) || defined(__GLEXT_H_)
#error Attempt to include auto-generated header after including glext.h
#endif
#if defined(__gltypes_h_)
#error Attempt to include auto-generated header after gltypes.h
#endif
#if defined(__gl_ATI_h_)
#error Attempt to include auto-generated header after including glATI.h
#endif

#define __glew_h__
#define __GLEW_H__
#define __gl_h_
#define __GL_H__
#define __glext_h_
#define __GLEXT_H_
#define __gltypes_h_
#define __gl_ATI_h_

#define OGL_SUCCESS 0

#include "khr.hpp"
#include "ogl_common.hpp"
#include "ogl_debug.hpp"

#include "ogl_1_0.hpp"

#include "ogl_1_1.hpp"

#include "ogl_1_2.hpp"

#include "ogl_1_3.hpp"

#include "ogl_1_4.hpp"

#include "ogl_1_5.hpp"

#include "ogl_2_0.hpp"

#include "ogl_2_1.hpp"

#include "ogl_3_0.hpp"

#include "ogl_3_1.hpp"

#include "ogl_3_2.hpp"

#include "ogl_3_3.hpp"

#include "ogl_4_0.hpp"

#include "ogl_4_1.hpp"

#include "ogl_4_2.hpp"

#include "ogl_4_3.hpp"

#include "ogl_4_4.hpp"

#include "ogl_4_5.hpp"

#include "ogl_4_6.hpp"

#include <stdio.h>

extern bool glVersion(int&, int&);

extern bool glLoad(int=-1,int=-1);

#endif //__ogl_hpp__
