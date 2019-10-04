GLAPI int   OGL_VERSION_3_1;

typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
GLAPI PFNGLDRAWARRAYSINSTANCEDPROC _ptrc_glDrawArraysInstanced;
#define glDrawArraysInstanced _ptrc_glDrawArraysInstanced
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
GLAPI PFNGLDRAWELEMENTSINSTANCEDPROC _ptrc_glDrawElementsInstanced;
#define glDrawElementsInstanced _ptrc_glDrawElementsInstanced
typedef void (APIENTRYP PFNGLTEXBUFFERPROC)(GLenum target, GLenum internalformat, GLuint buffer);
GLAPI PFNGLTEXBUFFERPROC _ptrc_glTexBuffer;
#define glTexBuffer _ptrc_glTexBuffer
typedef void (APIENTRYP PFNGLPRIMITIVERESTARTINDEXPROC)(GLuint index);
GLAPI PFNGLPRIMITIVERESTARTINDEXPROC _ptrc_glPrimitiveRestartIndex;
#define glPrimitiveRestartIndex _ptrc_glPrimitiveRestartIndex
typedef void (APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
GLAPI PFNGLCOPYBUFFERSUBDATAPROC _ptrc_glCopyBufferSubData;
#define glCopyBufferSubData _ptrc_glCopyBufferSubData
typedef void (APIENTRYP PFNGLGETUNIFORMINDICESPROC)(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices);
GLAPI PFNGLGETUNIFORMINDICESPROC _ptrc_glGetUniformIndices;
#define glGetUniformIndices _ptrc_glGetUniformIndices
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC)(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
GLAPI PFNGLGETACTIVEUNIFORMSIVPROC _ptrc_glGetActiveUniformsiv;
#define glGetActiveUniformsiv _ptrc_glGetActiveUniformsiv
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMNAMEPROC)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
GLAPI PFNGLGETACTIVEUNIFORMNAMEPROC _ptrc_glGetActiveUniformName;
#define glGetActiveUniformName _ptrc_glGetActiveUniformName
typedef GLuint (APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar *uniformBlockName);
GLAPI PFNGLGETUNIFORMBLOCKINDEXPROC _ptrc_glGetUniformBlockIndex;
#define glGetUniformBlockIndex _ptrc_glGetUniformBlockIndex
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
GLAPI PFNGLGETACTIVEUNIFORMBLOCKIVPROC _ptrc_glGetActiveUniformBlockiv;
#define glGetActiveUniformBlockiv _ptrc_glGetActiveUniformBlockiv
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
GLAPI PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC _ptrc_glGetActiveUniformBlockName;
#define glGetActiveUniformBlockName _ptrc_glGetActiveUniformBlockName
typedef void (APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
GLAPI PFNGLUNIFORMBLOCKBINDINGPROC _ptrc_glUniformBlockBinding;
#define glUniformBlockBinding _ptrc_glUniformBlockBinding
