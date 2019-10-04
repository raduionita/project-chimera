GLAPI int   OGL_VERSION_1_0;

typedef void (APIENTRYP PFNGLCULLFACEPROC)(GLenum mode);
GLAPI PFNGLCULLFACEPROC _ptrc_glCullFace;
#define glCullFace _ptrc_glCullFace
typedef void (APIENTRYP PFNGLFRONTFACEPROC)(GLenum mode);
GLAPI PFNGLFRONTFACEPROC _ptrc_glFrontFace;
#define glFrontFace _ptrc_glFrontFace
typedef void (APIENTRYP PFNGLHINTPROC)(GLenum target, GLenum mode);
GLAPI PFNGLHINTPROC _ptrc_glHint;
#define glHint _ptrc_glHint
typedef void (APIENTRYP PFNGLLINEWIDTHPROC)(GLfloat width);
GLAPI PFNGLLINEWIDTHPROC _ptrc_glLineWidth;
#define glLineWidth _ptrc_glLineWidth
typedef void (APIENTRYP PFNGLPOINTSIZEPROC)(GLfloat size);
GLAPI PFNGLPOINTSIZEPROC _ptrc_glPointSize;
#define glPointSize _ptrc_glPointSize
typedef void (APIENTRYP PFNGLPOLYGONMODEPROC)(GLenum face, GLenum mode);
GLAPI PFNGLPOLYGONMODEPROC _ptrc_glPolygonMode;
#define glPolygonMode _ptrc_glPolygonMode
typedef void (APIENTRYP PFNGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLSCISSORPROC _ptrc_glScissor;
#define glScissor _ptrc_glScissor
typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
GLAPI PFNGLTEXPARAMETERFPROC _ptrc_glTexParameterf;
#define glTexParameterf _ptrc_glTexParameterf
typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
GLAPI PFNGLTEXPARAMETERFVPROC _ptrc_glTexParameterfv;
#define glTexParameterfv _ptrc_glTexParameterfv
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
GLAPI PFNGLTEXPARAMETERIPROC _ptrc_glTexParameteri;
#define glTexParameteri _ptrc_glTexParameteri
typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint *params);
GLAPI PFNGLTEXPARAMETERIVPROC _ptrc_glTexParameteriv;
#define glTexParameteriv _ptrc_glTexParameteriv
typedef void (APIENTRYP PFNGLTEXIMAGE1DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
GLAPI PFNGLTEXIMAGE1DPROC _ptrc_glTexImage1D;
#define glTexImage1D _ptrc_glTexImage1D
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
GLAPI PFNGLTEXIMAGE2DPROC _ptrc_glTexImage2D;
#define glTexImage2D _ptrc_glTexImage2D
typedef void (APIENTRYP PFNGLDRAWBUFFERPROC)(GLenum buf);
GLAPI PFNGLDRAWBUFFERPROC _ptrc_glDrawBuffer;
#define glDrawBuffer _ptrc_glDrawBuffer
typedef void (APIENTRYP PFNGLCLEARPROC)(GLbitfield mask);
GLAPI PFNGLCLEARPROC _ptrc_glClear;
#define glClear _ptrc_glClear
typedef void (APIENTRYP PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GLAPI PFNGLCLEARCOLORPROC _ptrc_glClearColor;
#define glClearColor _ptrc_glClearColor
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC)(GLint s);
GLAPI PFNGLCLEARSTENCILPROC _ptrc_glClearStencil;
#define glClearStencil _ptrc_glClearStencil
typedef void (APIENTRYP PFNGLCLEARDEPTHPROC)(GLdouble depth);
GLAPI PFNGLCLEARDEPTHPROC _ptrc_glClearDepth;
#define glClearDepth _ptrc_glClearDepth
typedef void (APIENTRYP PFNGLSTENCILMASKPROC)(GLuint mask);
GLAPI PFNGLSTENCILMASKPROC _ptrc_glStencilMask;
#define glStencilMask _ptrc_glStencilMask
typedef void (APIENTRYP PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GLAPI PFNGLCOLORMASKPROC _ptrc_glColorMask;
#define glColorMask _ptrc_glColorMask
typedef void (APIENTRYP PFNGLDEPTHMASKPROC)(GLboolean flag);
GLAPI PFNGLDEPTHMASKPROC _ptrc_glDepthMask;
#define glDepthMask _ptrc_glDepthMask
typedef void (APIENTRYP PFNGLDISABLEPROC)(GLenum cap);
GLAPI PFNGLDISABLEPROC _ptrc_glDisable;
#define glDisable _ptrc_glDisable
typedef void (APIENTRYP PFNGLENABLEPROC)(GLenum cap);
GLAPI PFNGLENABLEPROC _ptrc_glEnable;
#define glEnable _ptrc_glEnable
typedef void (APIENTRYP PFNGLFINISHPROC)(void);
GLAPI PFNGLFINISHPROC _ptrc_glFinish;
#define glFinish _ptrc_glFinish
typedef void (APIENTRYP PFNGLFLUSHPROC)(void);
GLAPI PFNGLFLUSHPROC _ptrc_glFlush;
#define glFlush _ptrc_glFlush
typedef void (APIENTRYP PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
GLAPI PFNGLBLENDFUNCPROC _ptrc_glBlendFunc;
#define glBlendFunc _ptrc_glBlendFunc
typedef void (APIENTRYP PFNGLLOGICOPPROC)(GLenum opcode);
GLAPI PFNGLLOGICOPPROC _ptrc_glLogicOp;
#define glLogicOp _ptrc_glLogicOp
typedef void (APIENTRYP PFNGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
GLAPI PFNGLSTENCILFUNCPROC _ptrc_glStencilFunc;
#define glStencilFunc _ptrc_glStencilFunc
typedef void (APIENTRYP PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
GLAPI PFNGLSTENCILOPPROC _ptrc_glStencilOp;
#define glStencilOp _ptrc_glStencilOp
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC)(GLenum func);
GLAPI PFNGLDEPTHFUNCPROC _ptrc_glDepthFunc;
#define glDepthFunc _ptrc_glDepthFunc
typedef void (APIENTRYP PFNGLPIXELSTOREFPROC)(GLenum pname, GLfloat param);
GLAPI PFNGLPIXELSTOREFPROC _ptrc_glPixelStoref;
#define glPixelStoref _ptrc_glPixelStoref
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC)(GLenum pname, GLint param);
GLAPI PFNGLPIXELSTOREIPROC _ptrc_glPixelStorei;
#define glPixelStorei _ptrc_glPixelStorei
typedef void (APIENTRYP PFNGLREADBUFFERPROC)(GLenum src);
GLAPI PFNGLREADBUFFERPROC _ptrc_glReadBuffer;
#define glReadBuffer _ptrc_glReadBuffer
typedef void (APIENTRYP PFNGLREADPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
GLAPI PFNGLREADPIXELSPROC _ptrc_glReadPixels;
#define glReadPixels _ptrc_glReadPixels
typedef void (APIENTRYP PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean *data);
GLAPI PFNGLGETBOOLEANVPROC _ptrc_glGetBooleanv;
#define glGetBooleanv _ptrc_glGetBooleanv
typedef void (APIENTRYP PFNGLGETDOUBLEVPROC)(GLenum pname, GLdouble *data);
GLAPI PFNGLGETDOUBLEVPROC _ptrc_glGetDoublev;
#define glGetDoublev _ptrc_glGetDoublev
typedef GLenum (APIENTRYP PFNGLGETERRORPROC)(void);
GLAPI PFNGLGETERRORPROC _ptrc_glGetError;
#define glGetError _ptrc_glGetError
typedef void (APIENTRYP PFNGLGETFLOATVPROC)(GLenum pname, GLfloat *data);
GLAPI PFNGLGETFLOATVPROC _ptrc_glGetFloatv;
#define glGetFloatv _ptrc_glGetFloatv
typedef void (APIENTRYP PFNGLGETINTEGERVPROC)(GLenum pname, GLint *data);
GLAPI PFNGLGETINTEGERVPROC _ptrc_glGetIntegerv;
#define glGetIntegerv _ptrc_glGetIntegerv
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGPROC)(GLenum name);
GLAPI PFNGLGETSTRINGPROC _ptrc_glGetString;
#define glGetString _ptrc_glGetString
typedef void (APIENTRYP PFNGLGETTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
GLAPI PFNGLGETTEXIMAGEPROC _ptrc_glGetTexImage;
#define glGetTexImage _ptrc_glGetTexImage
typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
GLAPI PFNGLGETTEXPARAMETERFVPROC _ptrc_glGetTexParameterfv;
#define glGetTexParameterfv _ptrc_glGetTexParameterfv
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETTEXPARAMETERIVPROC _ptrc_glGetTexParameteriv;
#define glGetTexParameteriv _ptrc_glGetTexParameteriv
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC)(GLenum target, GLint level, GLenum pname, GLfloat *params);
GLAPI PFNGLGETTEXLEVELPARAMETERFVPROC _ptrc_glGetTexLevelParameterfv;
#define glGetTexLevelParameterfv _ptrc_glGetTexLevelParameterfv
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC)(GLenum target, GLint level, GLenum pname, GLint *params);
GLAPI PFNGLGETTEXLEVELPARAMETERIVPROC _ptrc_glGetTexLevelParameteriv;
#define glGetTexLevelParameteriv _ptrc_glGetTexLevelParameteriv
typedef GLboolean (APIENTRYP PFNGLISENABLEDPROC)(GLenum cap);
GLAPI PFNGLISENABLEDPROC _ptrc_glIsEnabled;
#define glIsEnabled _ptrc_glIsEnabled
typedef void (APIENTRYP PFNGLDEPTHRANGEPROC)(GLdouble n, GLdouble f);
GLAPI PFNGLDEPTHRANGEPROC _ptrc_glDepthRange;
#define glDepthRange _ptrc_glDepthRange
typedef void (APIENTRYP PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLVIEWPORTPROC _ptrc_glViewport;
#define glViewport _ptrc_glViewport
