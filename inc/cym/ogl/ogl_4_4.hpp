GLAPI int   OGL_VERSION_4_4;

typedef void (APIENTRYP PFNGLBUFFERSTORAGEPROC)(GLenum target, GLsizeiptr size, const void *data, GLbitfield flags);
GLAPI PFNGLBUFFERSTORAGEPROC _ptrc_glBufferStorage;
#define glBufferStorage _ptrc_glBufferStorage
typedef void (APIENTRYP PFNGLCLEARTEXIMAGEPROC)(GLuint texture, GLint level, GLenum format, GLenum type, const void *data);
GLAPI PFNGLCLEARTEXIMAGEPROC _ptrc_glClearTexImage;
#define glClearTexImage _ptrc_glClearTexImage
typedef void (APIENTRYP PFNGLCLEARTEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);
GLAPI PFNGLCLEARTEXSUBIMAGEPROC _ptrc_glClearTexSubImage;
#define glClearTexSubImage _ptrc_glClearTexSubImage
typedef void (APIENTRYP PFNGLBINDBUFFERSBASEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint *buffers);
GLAPI PFNGLBINDBUFFERSBASEPROC _ptrc_glBindBuffersBase;
#define glBindBuffersBase _ptrc_glBindBuffersBase
typedef void (APIENTRYP PFNGLBINDBUFFERSRANGEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes);
GLAPI PFNGLBINDBUFFERSRANGEPROC _ptrc_glBindBuffersRange;
#define glBindBuffersRange _ptrc_glBindBuffersRange
typedef void (APIENTRYP PFNGLBINDTEXTURESPROC)(GLuint first, GLsizei count, const GLuint *textures);
GLAPI PFNGLBINDTEXTURESPROC _ptrc_glBindTextures;
#define glBindTextures _ptrc_glBindTextures
typedef void (APIENTRYP PFNGLBINDSAMPLERSPROC)(GLuint first, GLsizei count, const GLuint *samplers);
GLAPI PFNGLBINDSAMPLERSPROC _ptrc_glBindSamplers;
#define glBindSamplers _ptrc_glBindSamplers
typedef void (APIENTRYP PFNGLBINDIMAGETEXTURESPROC)(GLuint first, GLsizei count, const GLuint *textures);
GLAPI PFNGLBINDIMAGETEXTURESPROC _ptrc_glBindImageTextures;
#define glBindImageTextures _ptrc_glBindImageTextures
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERSPROC)(GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
GLAPI PFNGLBINDVERTEXBUFFERSPROC _ptrc_glBindVertexBuffers;
#define glBindVertexBuffers _ptrc_glBindVertexBuffers
