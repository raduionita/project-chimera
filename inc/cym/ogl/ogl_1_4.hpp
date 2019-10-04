GLAPI int   OGL_VERSION_1_4;

typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GLAPI PFNGLBLENDFUNCSEPARATEPROC _ptrc_glBlendFuncSeparate;
#define glBlendFuncSeparate _ptrc_glBlendFuncSeparate
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSPROC)(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
GLAPI PFNGLMULTIDRAWARRAYSPROC _ptrc_glMultiDrawArrays;
#define glMultiDrawArrays _ptrc_glMultiDrawArrays
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSPROC)(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
GLAPI PFNGLMULTIDRAWELEMENTSPROC _ptrc_glMultiDrawElements;
#define glMultiDrawElements _ptrc_glMultiDrawElements
typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
GLAPI PFNGLPOINTPARAMETERFPROC _ptrc_glPointParameterf;
#define glPointParameterf _ptrc_glPointParameterf
typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC)(GLenum pname, const GLfloat *params);
GLAPI PFNGLPOINTPARAMETERFVPROC _ptrc_glPointParameterfv;
#define glPointParameterfv _ptrc_glPointParameterfv
typedef void (APIENTRYP PFNGLPOINTPARAMETERIPROC)(GLenum pname, GLint param);
GLAPI PFNGLPOINTPARAMETERIPROC _ptrc_glPointParameteri;
#define glPointParameteri _ptrc_glPointParameteri
typedef void (APIENTRYP PFNGLPOINTPARAMETERIVPROC)(GLenum pname, const GLint *params);
GLAPI PFNGLPOINTPARAMETERIVPROC _ptrc_glPointParameteriv;
#define glPointParameteriv _ptrc_glPointParameteriv
typedef void (APIENTRYP PFNGLBLENDCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GLAPI PFNGLBLENDCOLORPROC _ptrc_glBlendColor;
#define glBlendColor _ptrc_glBlendColor
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC)(GLenum mode);
GLAPI PFNGLBLENDEQUATIONPROC _ptrc_glBlendEquation;
#define glBlendEquation _ptrc_glBlendEquation
