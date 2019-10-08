GLAPI int   OGL_VERSION_4_4;

typedef void (APIENTRYP PFNGLBUFFERSTORAGEPROC)(GLenum target, GLsizeiptr size, const void *data, GLbitfield flags);
GLAPI PFNGLBUFFERSTORAGEPROC glBufferStorage;

typedef void (APIENTRYP PFNGLCLEARTEXIMAGEPROC)(GLuint texture, GLint level, GLenum format, GLenum type, const void *data);
GLAPI PFNGLCLEARTEXIMAGEPROC glClearTexImage;

typedef void (APIENTRYP PFNGLCLEARTEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);
GLAPI PFNGLCLEARTEXSUBIMAGEPROC glClearTexSubImage;

typedef void (APIENTRYP PFNGLBINDBUFFERSBASEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint *buffers);
GLAPI PFNGLBINDBUFFERSBASEPROC glBindBuffersBase;

typedef void (APIENTRYP PFNGLBINDBUFFERSRANGEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes);
GLAPI PFNGLBINDBUFFERSRANGEPROC glBindBuffersRange;

typedef void (APIENTRYP PFNGLBINDTEXTURESPROC)(GLuint first, GLsizei count, const GLuint *textures);
GLAPI PFNGLBINDTEXTURESPROC glBindTextures;

typedef void (APIENTRYP PFNGLBINDSAMPLERSPROC)(GLuint first, GLsizei count, const GLuint *samplers);
GLAPI PFNGLBINDSAMPLERSPROC glBindSamplers;

typedef void (APIENTRYP PFNGLBINDIMAGETEXTURESPROC)(GLuint first, GLsizei count, const GLuint *textures);
GLAPI PFNGLBINDIMAGETEXTURESPROC glBindImageTextures;

typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERSPROC)(GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
GLAPI PFNGLBINDVERTEXBUFFERSPROC glBindVertexBuffers;

