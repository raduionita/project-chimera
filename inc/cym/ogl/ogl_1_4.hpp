GLAPI int   OGL_VERSION_1_4;

typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GLAPI PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;

typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSPROC)(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
GLAPI PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays;

typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSPROC)(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
GLAPI PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements;

typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
GLAPI PFNGLPOINTPARAMETERFPROC glPointParameterf;

typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC)(GLenum pname, const GLfloat *params);
GLAPI PFNGLPOINTPARAMETERFVPROC glPointParameterfv;

typedef void (APIENTRYP PFNGLPOINTPARAMETERIPROC)(GLenum pname, GLint param);
GLAPI PFNGLPOINTPARAMETERIPROC glPointParameteri;

typedef void (APIENTRYP PFNGLPOINTPARAMETERIVPROC)(GLenum pname, const GLint *params);
GLAPI PFNGLPOINTPARAMETERIVPROC glPointParameteriv;

typedef void (APIENTRYP PFNGLBLENDCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GLAPI PFNGLBLENDCOLORPROC glBlendColor;

typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC)(GLenum mode);
GLAPI PFNGLBLENDEQUATIONPROC glBlendEquation;

