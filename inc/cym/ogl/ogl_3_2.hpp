GLAPI int   OGL_VERSION_3_2;

typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
GLAPI PFNGLDRAWELEMENTSBASEVERTEXPROC _ptrc_glDrawElementsBaseVertex;
#define glDrawElementsBaseVertex _ptrc_glDrawElementsBaseVertex
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
GLAPI PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC _ptrc_glDrawRangeElementsBaseVertex;
#define glDrawRangeElementsBaseVertex _ptrc_glDrawRangeElementsBaseVertex
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
GLAPI PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC _ptrc_glDrawElementsInstancedBaseVertex;
#define glDrawElementsInstancedBaseVertex _ptrc_glDrawElementsInstancedBaseVertex
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex);
GLAPI PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC _ptrc_glMultiDrawElementsBaseVertex;
#define glMultiDrawElementsBaseVertex _ptrc_glMultiDrawElementsBaseVertex
typedef void (APIENTRYP PFNGLPROVOKINGVERTEXPROC)(GLenum mode);
GLAPI PFNGLPROVOKINGVERTEXPROC _ptrc_glProvokingVertex;
#define glProvokingVertex _ptrc_glProvokingVertex
typedef GLsync (APIENTRYP PFNGLFENCESYNCPROC)(GLenum condition, GLbitfield flags);
GLAPI PFNGLFENCESYNCPROC _ptrc_glFenceSync;
#define glFenceSync _ptrc_glFenceSync
typedef GLboolean (APIENTRYP PFNGLISSYNCPROC)(GLsync sync);
GLAPI PFNGLISSYNCPROC _ptrc_glIsSync;
#define glIsSync _ptrc_glIsSync
typedef void (APIENTRYP PFNGLDELETESYNCPROC)(GLsync sync);
GLAPI PFNGLDELETESYNCPROC _ptrc_glDeleteSync;
#define glDeleteSync _ptrc_glDeleteSync
typedef GLenum (APIENTRYP PFNGLCLIENTWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
GLAPI PFNGLCLIENTWAITSYNCPROC _ptrc_glClientWaitSync;
#define glClientWaitSync _ptrc_glClientWaitSync
typedef void (APIENTRYP PFNGLWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
GLAPI PFNGLWAITSYNCPROC _ptrc_glWaitSync;
#define glWaitSync _ptrc_glWaitSync
typedef void (APIENTRYP PFNGLGETINTEGER64VPROC)(GLenum pname, GLint64 *data);
GLAPI PFNGLGETINTEGER64VPROC _ptrc_glGetInteger64v;
#define glGetInteger64v _ptrc_glGetInteger64v
typedef void (APIENTRYP PFNGLGETSYNCIVPROC)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
GLAPI PFNGLGETSYNCIVPROC _ptrc_glGetSynciv;
#define glGetSynciv _ptrc_glGetSynciv
typedef void (APIENTRYP PFNGLGETINTEGER64I_VPROC)(GLenum target, GLuint index, GLint64 *data);
GLAPI PFNGLGETINTEGER64I_VPROC _ptrc_glGetInteger64i_v;
#define glGetInteger64i_v _ptrc_glGetInteger64i_v
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC)(GLenum target, GLenum pname, GLint64 *params);
GLAPI PFNGLGETBUFFERPARAMETERI64VPROC _ptrc_glGetBufferParameteri64v;
#define glGetBufferParameteri64v _ptrc_glGetBufferParameteri64v
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
GLAPI PFNGLFRAMEBUFFERTEXTUREPROC _ptrc_glFramebufferTexture;
#define glFramebufferTexture _ptrc_glFramebufferTexture
typedef void (APIENTRYP PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
GLAPI PFNGLTEXIMAGE2DMULTISAMPLEPROC _ptrc_glTexImage2DMultisample;
#define glTexImage2DMultisample _ptrc_glTexImage2DMultisample
typedef void (APIENTRYP PFNGLTEXIMAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
GLAPI PFNGLTEXIMAGE3DMULTISAMPLEPROC _ptrc_glTexImage3DMultisample;
#define glTexImage3DMultisample _ptrc_glTexImage3DMultisample
typedef void (APIENTRYP PFNGLGETMULTISAMPLEFVPROC)(GLenum pname, GLuint index, GLfloat *val);
GLAPI PFNGLGETMULTISAMPLEFVPROC _ptrc_glGetMultisamplefv;
#define glGetMultisamplefv _ptrc_glGetMultisamplefv
typedef void (APIENTRYP PFNGLSAMPLEMASKIPROC)(GLuint maskNumber, GLbitfield mask);
GLAPI PFNGLSAMPLEMASKIPROC _ptrc_glSampleMaski;
#define glSampleMaski _ptrc_glSampleMaski
