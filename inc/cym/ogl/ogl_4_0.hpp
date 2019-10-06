GLAPI int   OGL_VERSION_4_0;
typedef void (APIENTRYP PFNGLMINSAMPLESHADINGPROC)(GLfloat value);
GLAPI PFNGLMINSAMPLESHADINGPROC glMinSampleShading;

typedef void (APIENTRYP PFNGLBLENDEQUATIONIPROC)(GLuint buf, GLenum mode);
GLAPI PFNGLBLENDEQUATIONIPROC glBlendEquationi;

typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
GLAPI PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei;

typedef void (APIENTRYP PFNGLBLENDFUNCIPROC)(GLuint buf, GLenum src, GLenum dst);
GLAPI PFNGLBLENDFUNCIPROC glBlendFunci;

typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GLAPI PFNGLBLENDFUNCSEPARATEIPROC glBlendFuncSeparatei;

typedef void (APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC)(GLenum mode, const void *indirect);
GLAPI PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirect;

typedef void (APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void *indirect);
GLAPI PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirect;

typedef void (APIENTRYP PFNGLUNIFORM1DPROC)(GLint location, GLdouble x);
GLAPI PFNGLUNIFORM1DPROC glUniform1d;

typedef void (APIENTRYP PFNGLUNIFORM2DPROC)(GLint location, GLdouble x, GLdouble y);
GLAPI PFNGLUNIFORM2DPROC glUniform2d;

typedef void (APIENTRYP PFNGLUNIFORM3DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z);
GLAPI PFNGLUNIFORM3DPROC glUniform3d;

typedef void (APIENTRYP PFNGLUNIFORM4DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI PFNGLUNIFORM4DPROC glUniform4d;

typedef void (APIENTRYP PFNGLUNIFORM1DVPROC)(GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLUNIFORM1DVPROC glUniform1dv;

typedef void (APIENTRYP PFNGLUNIFORM2DVPROC)(GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLUNIFORM2DVPROC glUniform2dv;

typedef void (APIENTRYP PFNGLUNIFORM3DVPROC)(GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLUNIFORM3DVPROC glUniform3dv;

typedef void (APIENTRYP PFNGLUNIFORM4DVPROC)(GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLUNIFORM4DVPROC glUniform4dv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX2DVPROC glUniformMatrix2dv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX3DVPROC glUniformMatrix3dv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX4DVPROC glUniformMatrix4dv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX2X3DVPROC glUniformMatrix2x3dv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX2X4DVPROC glUniformMatrix2x4dv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX3X2DVPROC glUniformMatrix3x2dv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX3X4DVPROC glUniformMatrix3x4dv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX4X2DVPROC glUniformMatrix4x2dv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX4X3DVPROC glUniformMatrix4x3dv;

typedef void (APIENTRYP PFNGLGETUNIFORMDVPROC)(GLuint program, GLint location, GLdouble *params);
GLAPI PFNGLGETUNIFORMDVPROC glGetUniformdv;

typedef GLint (APIENTRYP PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)(GLuint program, GLenum shadertype, const GLchar *name);
GLAPI PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glGetSubroutineUniformLocation;

typedef GLuint (APIENTRYP PFNGLGETSUBROUTINEINDEXPROC)(GLuint program, GLenum shadertype, const GLchar *name);
GLAPI PFNGLGETSUBROUTINEINDEXPROC glGetSubroutineIndex;

typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
GLAPI PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformiv;

typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
GLAPI PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformName;

typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINENAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
GLAPI PFNGLGETACTIVESUBROUTINENAMEPROC glGetActiveSubroutineName;

typedef void (APIENTRYP PFNGLUNIFORMSUBROUTINESUIVPROC)(GLenum shadertype, GLsizei count, const GLuint *indices);
GLAPI PFNGLUNIFORMSUBROUTINESUIVPROC glUniformSubroutinesuiv;

typedef void (APIENTRYP PFNGLGETUNIFORMSUBROUTINEUIVPROC)(GLenum shadertype, GLint location, GLuint *params);
GLAPI PFNGLGETUNIFORMSUBROUTINEUIVPROC glGetUniformSubroutineuiv;

typedef void (APIENTRYP PFNGLGETPROGRAMSTAGEIVPROC)(GLuint program, GLenum shadertype, GLenum pname, GLint *values);
GLAPI PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageiv;

typedef void (APIENTRYP PFNGLPATCHPARAMETERIPROC)(GLenum pname, GLint value);
GLAPI PFNGLPATCHPARAMETERIPROC glPatchParameteri;

typedef void (APIENTRYP PFNGLPATCHPARAMETERFVPROC)(GLenum pname, const GLfloat *values);
GLAPI PFNGLPATCHPARAMETERFVPROC glPatchParameterfv;

typedef void (APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC)(GLenum target, GLuint id);
GLAPI PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback;

typedef void (APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC)(GLsizei n, const GLuint *ids);
GLAPI PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks;

typedef void (APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint *ids);
GLAPI PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks;

typedef GLboolean (APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC)(GLuint id);
GLAPI PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback;

typedef void (APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC)(void);
GLAPI PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback;

typedef void (APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC)(void);
GLAPI PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback;

typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKPROC)(GLenum mode, GLuint id);
GLAPI PFNGLDRAWTRANSFORMFEEDBACKPROC glDrawTransformFeedback;

typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum mode, GLuint id, GLuint stream);
GLAPI PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glDrawTransformFeedbackStream;

typedef void (APIENTRYP PFNGLBEGINQUERYINDEXEDPROC)(GLenum target, GLuint index, GLuint id);
GLAPI PFNGLBEGINQUERYINDEXEDPROC glBeginQueryIndexed;

typedef void (APIENTRYP PFNGLENDQUERYINDEXEDPROC)(GLenum target, GLuint index);
GLAPI PFNGLENDQUERYINDEXEDPROC glEndQueryIndexed;

typedef void (APIENTRYP PFNGLGETQUERYINDEXEDIVPROC)(GLenum target, GLuint index, GLenum pname, GLint *params);
GLAPI PFNGLGETQUERYINDEXEDIVPROC glGetQueryIndexediv;

