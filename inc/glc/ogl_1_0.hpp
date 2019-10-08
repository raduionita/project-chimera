GLAPI int   OGL_VERSION_1_0;

typedef void (APIENTRYP PFNGLLOADIDENTITYPROC)(void);
GLAPI PFNGLLOADIDENTITYPROC glLoadIdentity;

typedef void (APIENTRYP PFNGLORTHOPROC)(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble zNear,GLdouble zFar);
GLAPI PFNGLORTHOPROC glOrtho;

typedef void (APIENTRYP PFNGLMATRIXMODEPROC)(GLenum);
GLAPI PFNGLMATRIXMODEPROC glMatrixMode;

typedef void (APIENTRYP PFNGLBEGINPROC)(GLenum mode);
GLAPI PFNGLBEGINPROC glBegin;

typedef void (APIENTRYP PFNGLENDPROC)();
GLAPI PFNGLENDPROC glEnd;

typedef void (APIENTRYP PFNGLCOLOR3FPROC)(GLfloat,GLfloat,GLfloat);
GLAPI PFNGLCOLOR3FPROC glColor3f;

typedef void (APIENTRYP PFNGLVERTEX3FPROC)(GLfloat,GLfloat,GLfloat);
GLAPI PFNGLVERTEX3FPROC glVertex3f;

typedef void (APIENTRYP PFNGLCULLFACEPROC)(GLenum mode);
GLAPI PFNGLCULLFACEPROC glCullFace;

typedef void (APIENTRYP PFNGLFRONTFACEPROC)(GLenum mode);
GLAPI PFNGLFRONTFACEPROC glFrontFace;

typedef void (APIENTRYP PFNGLHINTPROC)(GLenum target, GLenum mode);
GLAPI PFNGLHINTPROC glHint;

typedef void (APIENTRYP PFNGLLINEWIDTHPROC)(GLfloat width);
GLAPI PFNGLLINEWIDTHPROC glLineWidth;

typedef void (APIENTRYP PFNGLPOINTSIZEPROC)(GLfloat size);
GLAPI PFNGLPOINTSIZEPROC glPointSize;

typedef void (APIENTRYP PFNGLPOLYGONMODEPROC)(GLenum face, GLenum mode);
GLAPI PFNGLPOLYGONMODEPROC glPolygonMode;

typedef void (APIENTRYP PFNGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLSCISSORPROC glScissor;

typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
GLAPI PFNGLTEXPARAMETERFPROC glTexParameterf;

typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
GLAPI PFNGLTEXPARAMETERFVPROC glTexParameterfv;

typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
GLAPI PFNGLTEXPARAMETERIPROC glTexParameteri;

typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint *params);
GLAPI PFNGLTEXPARAMETERIVPROC glTexParameteriv;

typedef void (APIENTRYP PFNGLTEXIMAGE1DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
GLAPI PFNGLTEXIMAGE1DPROC glTexImage1D;

typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
GLAPI PFNGLTEXIMAGE2DPROC glTexImage2D;

typedef void (APIENTRYP PFNGLDRAWBUFFERPROC)(GLenum buf);
GLAPI PFNGLDRAWBUFFERPROC glDrawBuffer;

typedef void (APIENTRYP PFNGLCLEARPROC)(GLbitfield mask);
GLAPI PFNGLCLEARPROC glClear;

typedef void (APIENTRYP PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GLAPI PFNGLCLEARCOLORPROC glClearColor;

typedef void (APIENTRYP PFNGLCLEARSTENCILPROC)(GLint s);
GLAPI PFNGLCLEARSTENCILPROC glClearStencil;

typedef void (APIENTRYP PFNGLCLEARDEPTHPROC)(GLdouble depth);
GLAPI PFNGLCLEARDEPTHPROC glClearDepth;

typedef void (APIENTRYP PFNGLSTENCILMASKPROC)(GLuint mask);
GLAPI PFNGLSTENCILMASKPROC glStencilMask;

typedef void (APIENTRYP PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GLAPI PFNGLCOLORMASKPROC glColorMask;

typedef void (APIENTRYP PFNGLDEPTHMASKPROC)(GLboolean flag);
GLAPI PFNGLDEPTHMASKPROC glDepthMask;

typedef void (APIENTRYP PFNGLDISABLEPROC)(GLenum cap);
GLAPI PFNGLDISABLEPROC glDisable;

typedef void (APIENTRYP PFNGLENABLEPROC)(GLenum cap);
GLAPI PFNGLENABLEPROC glEnable;

typedef void (APIENTRYP PFNGLFINISHPROC)(void);
GLAPI PFNGLFINISHPROC glFinish;

typedef void (APIENTRYP PFNGLFLUSHPROC)(void);
GLAPI PFNGLFLUSHPROC glFlush;

typedef void (APIENTRYP PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
GLAPI PFNGLBLENDFUNCPROC glBlendFunc;

typedef void (APIENTRYP PFNGLLOGICOPPROC)(GLenum opcode);
GLAPI PFNGLLOGICOPPROC glLogicOp;

typedef void (APIENTRYP PFNGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
GLAPI PFNGLSTENCILFUNCPROC glStencilFunc;

typedef void (APIENTRYP PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
GLAPI PFNGLSTENCILOPPROC glStencilOp;

typedef void (APIENTRYP PFNGLDEPTHFUNCPROC)(GLenum func);
GLAPI PFNGLDEPTHFUNCPROC glDepthFunc;

typedef void (APIENTRYP PFNGLPIXELSTOREFPROC)(GLenum pname, GLfloat param);
GLAPI PFNGLPIXELSTOREFPROC glPixelStoref;

typedef void (APIENTRYP PFNGLPIXELSTOREIPROC)(GLenum pname, GLint param);
GLAPI PFNGLPIXELSTOREIPROC glPixelStorei;

typedef void (APIENTRYP PFNGLREADBUFFERPROC)(GLenum src);
GLAPI PFNGLREADBUFFERPROC glReadBuffer;

typedef void (APIENTRYP PFNGLREADPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
GLAPI PFNGLREADPIXELSPROC glReadPixels;

typedef void (APIENTRYP PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean *data);
GLAPI PFNGLGETBOOLEANVPROC glGetBooleanv;

typedef void (APIENTRYP PFNGLGETDOUBLEVPROC)(GLenum pname, GLdouble *data);
GLAPI PFNGLGETDOUBLEVPROC glGetDoublev;

typedef GLenum (APIENTRYP PFNGLGETERRORPROC)(void);
GLAPI PFNGLGETERRORPROC glGetError;

typedef void (APIENTRYP PFNGLGETFLOATVPROC)(GLenum pname, GLfloat *data);
GLAPI PFNGLGETFLOATVPROC glGetFloatv;

typedef void (APIENTRYP PFNGLGETINTEGERVPROC)(GLenum pname, GLint *data);
GLAPI PFNGLGETINTEGERVPROC glGetIntegerv;

typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGPROC)(GLenum name);
GLAPI PFNGLGETSTRINGPROC glGetString;

typedef void (APIENTRYP PFNGLGETTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
GLAPI PFNGLGETTEXIMAGEPROC glGetTexImage;

typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
GLAPI PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfv;

typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETTEXPARAMETERIVPROC glGetTexParameteriv;

typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC)(GLenum target, GLint level, GLenum pname, GLfloat *params);
GLAPI PFNGLGETTEXLEVELPARAMETERFVPROC glGetTexLevelParameterfv;

typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC)(GLenum target, GLint level, GLenum pname, GLint *params);
GLAPI PFNGLGETTEXLEVELPARAMETERIVPROC glGetTexLevelParameteriv;

typedef GLboolean (APIENTRYP PFNGLISENABLEDPROC)(GLenum cap);
GLAPI PFNGLISENABLEDPROC glIsEnabled;

typedef void (APIENTRYP PFNGLDEPTHRANGEPROC)(GLdouble n, GLdouble f);
GLAPI PFNGLDEPTHRANGEPROC glDepthRange;

typedef void (APIENTRYP PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLVIEWPORTPROC glViewport;

