GLAPI int   OGL_VERSION_1_1;

typedef void (APIENTRYP PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
GLAPI PFNGLDRAWARRAYSPROC _ptrc_glDrawArrays;
#define glDrawArrays _ptrc_glDrawArrays
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices);
GLAPI PFNGLDRAWELEMENTSPROC _ptrc_glDrawElements;
#define glDrawElements _ptrc_glDrawElements
typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
GLAPI PFNGLPOLYGONOFFSETPROC _ptrc_glPolygonOffset;
#define glPolygonOffset _ptrc_glPolygonOffset
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
GLAPI PFNGLCOPYTEXIMAGE1DPROC _ptrc_glCopyTexImage1D;
#define glCopyTexImage1D _ptrc_glCopyTexImage1D
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
GLAPI PFNGLCOPYTEXIMAGE2DPROC _ptrc_glCopyTexImage2D;
#define glCopyTexImage2D _ptrc_glCopyTexImage2D
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
GLAPI PFNGLCOPYTEXSUBIMAGE1DPROC _ptrc_glCopyTexSubImage1D;
#define glCopyTexSubImage1D _ptrc_glCopyTexSubImage1D
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLCOPYTEXSUBIMAGE2DPROC _ptrc_glCopyTexSubImage2D;
#define glCopyTexSubImage2D _ptrc_glCopyTexSubImage2D
typedef void (APIENTRYP PFNGLTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
GLAPI PFNGLTEXSUBIMAGE1DPROC _ptrc_glTexSubImage1D;
#define glTexSubImage1D _ptrc_glTexSubImage1D
typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
GLAPI PFNGLTEXSUBIMAGE2DPROC _ptrc_glTexSubImage2D;
#define glTexSubImage2D _ptrc_glTexSubImage2D
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
GLAPI PFNGLBINDTEXTUREPROC _ptrc_glBindTexture;
#define glBindTexture _ptrc_glBindTexture
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint *textures);
GLAPI PFNGLDELETETEXTURESPROC _ptrc_glDeleteTextures;
#define glDeleteTextures _ptrc_glDeleteTextures
typedef void (APIENTRYP PFNGLGENTEXTURESPROC)(GLsizei n, GLuint *textures);
GLAPI PFNGLGENTEXTURESPROC _ptrc_glGenTextures;
#define glGenTextures _ptrc_glGenTextures
typedef GLboolean (APIENTRYP PFNGLISTEXTUREPROC)(GLuint texture);
GLAPI PFNGLISTEXTUREPROC _ptrc_glIsTexture;
#define glIsTexture _ptrc_glIsTexture
