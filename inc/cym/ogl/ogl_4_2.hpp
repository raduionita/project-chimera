GLAPI int   OGL_VERSION_4_2;

typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
GLAPI PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC _ptrc_glDrawArraysInstancedBaseInstance;
#define glDrawArraysInstancedBaseInstance _ptrc_glDrawArraysInstancedBaseInstance
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance);
GLAPI PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC _ptrc_glDrawElementsInstancedBaseInstance;
#define glDrawElementsInstancedBaseInstance _ptrc_glDrawElementsInstancedBaseInstance
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
GLAPI PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC _ptrc_glDrawElementsInstancedBaseVertexBaseInstance;
#define glDrawElementsInstancedBaseVertexBaseInstance _ptrc_glDrawElementsInstancedBaseVertexBaseInstance
typedef void (APIENTRYP PFNGLGETINTERNALFORMATIVPROC)(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params);
GLAPI PFNGLGETINTERNALFORMATIVPROC _ptrc_glGetInternalformativ;
#define glGetInternalformativ _ptrc_glGetInternalformativ
typedef void (APIENTRYP PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)(GLuint program, GLuint bufferIndex, GLenum pname, GLint *params);
GLAPI PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC _ptrc_glGetActiveAtomicCounterBufferiv;
#define glGetActiveAtomicCounterBufferiv _ptrc_glGetActiveAtomicCounterBufferiv
typedef void (APIENTRYP PFNGLBINDIMAGETEXTUREPROC)(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
GLAPI PFNGLBINDIMAGETEXTUREPROC _ptrc_glBindImageTexture;
#define glBindImageTexture _ptrc_glBindImageTexture
typedef void (APIENTRYP PFNGLMEMORYBARRIERPROC)(GLbitfield barriers);
GLAPI PFNGLMEMORYBARRIERPROC _ptrc_glMemoryBarrier;
#define glMemoryBarrier _ptrc_glMemoryBarrier
typedef void (APIENTRYP PFNGLTEXSTORAGE1DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
GLAPI PFNGLTEXSTORAGE1DPROC _ptrc_glTexStorage1D;
#define glTexStorage1D _ptrc_glTexStorage1D
typedef void (APIENTRYP PFNGLTEXSTORAGE2DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
GLAPI PFNGLTEXSTORAGE2DPROC _ptrc_glTexStorage2D;
#define glTexStorage2D _ptrc_glTexStorage2D
typedef void (APIENTRYP PFNGLTEXSTORAGE3DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
GLAPI PFNGLTEXSTORAGE3DPROC _ptrc_glTexStorage3D;
#define glTexStorage3D _ptrc_glTexStorage3D
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)(GLenum mode, GLuint id, GLsizei instancecount);
GLAPI PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC _ptrc_glDrawTransformFeedbackInstanced;
#define glDrawTransformFeedbackInstanced _ptrc_glDrawTransformFeedbackInstanced
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
GLAPI PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC _ptrc_glDrawTransformFeedbackStreamInstanced;
#define glDrawTransformFeedbackStreamInstanced _ptrc_glDrawTransformFeedbackStreamInstanced
