GLAPI int   OGL_VERSION_3_2;

typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
GLAPI PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex;

typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
GLAPI PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glDrawRangeElementsBaseVertex;

typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
GLAPI PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glDrawElementsInstancedBaseVertex;

typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex);
GLAPI PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertex;

typedef void (APIENTRYP PFNGLPROVOKINGVERTEXPROC)(GLenum mode);
GLAPI PFNGLPROVOKINGVERTEXPROC glProvokingVertex;

typedef GLsync (APIENTRYP PFNGLFENCESYNCPROC)(GLenum condition, GLbitfield flags);
GLAPI PFNGLFENCESYNCPROC glFenceSync;

typedef GLboolean (APIENTRYP PFNGLISSYNCPROC)(GLsync sync);
GLAPI PFNGLISSYNCPROC glIsSync;

typedef void (APIENTRYP PFNGLDELETESYNCPROC)(GLsync sync);
GLAPI PFNGLDELETESYNCPROC glDeleteSync;

typedef GLenum (APIENTRYP PFNGLCLIENTWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
GLAPI PFNGLCLIENTWAITSYNCPROC glClientWaitSync;

typedef void (APIENTRYP PFNGLWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
GLAPI PFNGLWAITSYNCPROC glWaitSync;

typedef void (APIENTRYP PFNGLGETINTEGER64VPROC)(GLenum pname, GLint64 *data);
GLAPI PFNGLGETINTEGER64VPROC glGetInteger64v;

typedef void (APIENTRYP PFNGLGETSYNCIVPROC)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
GLAPI PFNGLGETSYNCIVPROC glGetSynciv;

typedef void (APIENTRYP PFNGLGETINTEGER64I_VPROC)(GLenum target, GLuint index, GLint64 *data);
GLAPI PFNGLGETINTEGER64I_VPROC glGetInteger64i_v;

typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC)(GLenum target, GLenum pname, GLint64 *params);
GLAPI PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v;

typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
GLAPI PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;

typedef void (APIENTRYP PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
GLAPI PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample;

typedef void (APIENTRYP PFNGLTEXIMAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
GLAPI PFNGLTEXIMAGE3DMULTISAMPLEPROC glTexImage3DMultisample;

typedef void (APIENTRYP PFNGLGETMULTISAMPLEFVPROC)(GLenum pname, GLuint index, GLfloat *val);
GLAPI PFNGLGETMULTISAMPLEFVPROC glGetMultisamplefv;

typedef void (APIENTRYP PFNGLSAMPLEMASKIPROC)(GLuint maskNumber, GLbitfield mask);
GLAPI PFNGLSAMPLEMASKIPROC glSampleMaski;

