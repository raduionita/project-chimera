GLAPI int   OGL_VERSION_1_5;

typedef void (APIENTRYP PFNGLGENQUERIESPROC)(GLsizei n, GLuint *ids);
GLAPI PFNGLGENQUERIESPROC _ptrc_glGenQueries;
#define glGenQueries _ptrc_glGenQueries
typedef void (APIENTRYP PFNGLDELETEQUERIESPROC)(GLsizei n, const GLuint *ids);
GLAPI PFNGLDELETEQUERIESPROC _ptrc_glDeleteQueries;
#define glDeleteQueries _ptrc_glDeleteQueries
typedef GLboolean (APIENTRYP PFNGLISQUERYPROC)(GLuint id);
GLAPI PFNGLISQUERYPROC _ptrc_glIsQuery;
#define glIsQuery _ptrc_glIsQuery
typedef void (APIENTRYP PFNGLBEGINQUERYPROC)(GLenum target, GLuint id);
GLAPI PFNGLBEGINQUERYPROC _ptrc_glBeginQuery;
#define glBeginQuery _ptrc_glBeginQuery
typedef void (APIENTRYP PFNGLENDQUERYPROC)(GLenum target);
GLAPI PFNGLENDQUERYPROC _ptrc_glEndQuery;
#define glEndQuery _ptrc_glEndQuery
typedef void (APIENTRYP PFNGLGETQUERYIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETQUERYIVPROC _ptrc_glGetQueryiv;
#define glGetQueryiv _ptrc_glGetQueryiv
typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC)(GLuint id, GLenum pname, GLint *params);
GLAPI PFNGLGETQUERYOBJECTIVPROC _ptrc_glGetQueryObjectiv;
#define glGetQueryObjectiv _ptrc_glGetQueryObjectiv
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC)(GLuint id, GLenum pname, GLuint *params);
GLAPI PFNGLGETQUERYOBJECTUIVPROC _ptrc_glGetQueryObjectuiv;
#define glGetQueryObjectuiv _ptrc_glGetQueryObjectuiv
typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
GLAPI PFNGLBINDBUFFERPROC _ptrc_glBindBuffer;
#define glBindBuffer _ptrc_glBindBuffer
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
GLAPI PFNGLDELETEBUFFERSPROC _ptrc_glDeleteBuffers;
#define glDeleteBuffers _ptrc_glDeleteBuffers
typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
GLAPI PFNGLGENBUFFERSPROC _ptrc_glGenBuffers;
#define glGenBuffers _ptrc_glGenBuffers
typedef GLboolean (APIENTRYP PFNGLISBUFFERPROC)(GLuint buffer);
GLAPI PFNGLISBUFFERPROC _ptrc_glIsBuffer;
#define glIsBuffer _ptrc_glIsBuffer
typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
GLAPI PFNGLBUFFERDATAPROC _ptrc_glBufferData;
#define glBufferData _ptrc_glBufferData
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
GLAPI PFNGLBUFFERSUBDATAPROC _ptrc_glBufferSubData;
#define glBufferSubData _ptrc_glBufferSubData
typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, void *data);
GLAPI PFNGLGETBUFFERSUBDATAPROC _ptrc_glGetBufferSubData;
#define glGetBufferSubData _ptrc_glGetBufferSubData
typedef void * (APIENTRYP PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
GLAPI PFNGLMAPBUFFERPROC _ptrc_glMapBuffer;
#define glMapBuffer _ptrc_glMapBuffer
typedef GLboolean (APIENTRYP PFNGLUNMAPBUFFERPROC)(GLenum target);
GLAPI PFNGLUNMAPBUFFERPROC _ptrc_glUnmapBuffer;
#define glUnmapBuffer _ptrc_glUnmapBuffer
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETBUFFERPARAMETERIVPROC _ptrc_glGetBufferParameteriv;
#define glGetBufferParameteriv _ptrc_glGetBufferParameteriv
typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC)(GLenum target, GLenum pname, void **params);
GLAPI PFNGLGETBUFFERPOINTERVPROC _ptrc_glGetBufferPointerv;
#define glGetBufferPointerv _ptrc_glGetBufferPointerv
