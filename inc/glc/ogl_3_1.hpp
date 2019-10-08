GLAPI int   OGL_VERSION_3_1;

typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
GLAPI PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;

typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
GLAPI PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced;

typedef void (APIENTRYP PFNGLTEXBUFFERPROC)(GLenum target, GLenum internalformat, GLuint buffer);
GLAPI PFNGLTEXBUFFERPROC glTexBuffer;

typedef void (APIENTRYP PFNGLPRIMITIVERESTARTINDEXPROC)(GLuint index);
GLAPI PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex;

typedef void (APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
GLAPI PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData;

typedef void (APIENTRYP PFNGLGETUNIFORMINDICESPROC)(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices);
GLAPI PFNGLGETUNIFORMINDICESPROC glGetUniformIndices;

typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC)(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
GLAPI PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv;

typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMNAMEPROC)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
GLAPI PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName;

typedef GLuint (APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar *uniformBlockName);
GLAPI PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;

typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
GLAPI PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv;

typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
GLAPI PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName;

typedef void (APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
GLAPI PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;

