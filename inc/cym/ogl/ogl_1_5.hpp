GLAPI int   OGL_VERSION_1_5;

typedef void (APIENTRYP PFNGLGENQUERIESPROC)(GLsizei n, GLuint *ids);
GLAPI PFNGLGENQUERIESPROC glGenQueries;

typedef void (APIENTRYP PFNGLDELETEQUERIESPROC)(GLsizei n, const GLuint *ids);
GLAPI PFNGLDELETEQUERIESPROC glDeleteQueries;

typedef GLboolean (APIENTRYP PFNGLISQUERYPROC)(GLuint id);
GLAPI PFNGLISQUERYPROC glIsQuery;

typedef void (APIENTRYP PFNGLBEGINQUERYPROC)(GLenum target, GLuint id);
GLAPI PFNGLBEGINQUERYPROC glBeginQuery;

typedef void (APIENTRYP PFNGLENDQUERYPROC)(GLenum target);
GLAPI PFNGLENDQUERYPROC glEndQuery;

typedef void (APIENTRYP PFNGLGETQUERYIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETQUERYIVPROC glGetQueryiv;

typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC)(GLuint id, GLenum pname, GLint *params);
GLAPI PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv;

typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC)(GLuint id, GLenum pname, GLuint *params);
GLAPI PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv;

typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
GLAPI PFNGLBINDBUFFERPROC glBindBuffer;

typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
GLAPI PFNGLDELETEBUFFERSPROC glDeleteBuffers;

typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
GLAPI PFNGLGENBUFFERSPROC glGenBuffers;

typedef GLboolean (APIENTRYP PFNGLISBUFFERPROC)(GLuint buffer);
GLAPI PFNGLISBUFFERPROC glIsBuffer;

typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
GLAPI PFNGLBUFFERDATAPROC glBufferData;

typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
GLAPI PFNGLBUFFERSUBDATAPROC glBufferSubData;

typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, void *data);
GLAPI PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData;

typedef void * (APIENTRYP PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
GLAPI PFNGLMAPBUFFERPROC glMapBuffer;

typedef GLboolean (APIENTRYP PFNGLUNMAPBUFFERPROC)(GLenum target);
GLAPI PFNGLUNMAPBUFFERPROC glUnmapBuffer;

typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;

typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC)(GLenum target, GLenum pname, void **params);
GLAPI PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv;

