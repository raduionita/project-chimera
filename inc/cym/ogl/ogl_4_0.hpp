GLAPI int   OGL_VERSION_4_0;
typedef void (APIENTRYP PFNGLMINSAMPLESHADINGPROC)(GLfloat value);
GLAPI PFNGLMINSAMPLESHADINGPROC _ptrc_glMinSampleShading;
#define glMinSampleShading _ptrc_glMinSampleShading
typedef void (APIENTRYP PFNGLBLENDEQUATIONIPROC)(GLuint buf, GLenum mode);
GLAPI PFNGLBLENDEQUATIONIPROC _ptrc_glBlendEquationi;
#define glBlendEquationi _ptrc_glBlendEquationi
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
GLAPI PFNGLBLENDEQUATIONSEPARATEIPROC _ptrc_glBlendEquationSeparatei;
#define glBlendEquationSeparatei _ptrc_glBlendEquationSeparatei
typedef void (APIENTRYP PFNGLBLENDFUNCIPROC)(GLuint buf, GLenum src, GLenum dst);
GLAPI PFNGLBLENDFUNCIPROC _ptrc_glBlendFunci;
#define glBlendFunci _ptrc_glBlendFunci
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GLAPI PFNGLBLENDFUNCSEPARATEIPROC _ptrc_glBlendFuncSeparatei;
#define glBlendFuncSeparatei _ptrc_glBlendFuncSeparatei
typedef void (APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC)(GLenum mode, const void *indirect);
GLAPI PFNGLDRAWARRAYSINDIRECTPROC _ptrc_glDrawArraysIndirect;
#define glDrawArraysIndirect _ptrc_glDrawArraysIndirect
typedef void (APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void *indirect);
GLAPI PFNGLDRAWELEMENTSINDIRECTPROC _ptrc_glDrawElementsIndirect;
#define glDrawElementsIndirect _ptrc_glDrawElementsIndirect
typedef void (APIENTRYP PFNGLUNIFORM1DPROC)(GLint location, GLdouble x);
GLAPI PFNGLUNIFORM1DPROC _ptrc_glUniform1d;
#define glUniform1d _ptrc_glUniform1d
typedef void (APIENTRYP PFNGLUNIFORM2DPROC)(GLint location, GLdouble x, GLdouble y);
GLAPI PFNGLUNIFORM2DPROC _ptrc_glUniform2d;
#define glUniform2d _ptrc_glUniform2d
typedef void (APIENTRYP PFNGLUNIFORM3DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z);
GLAPI PFNGLUNIFORM3DPROC _ptrc_glUniform3d;
#define glUniform3d _ptrc_glUniform3d
typedef void (APIENTRYP PFNGLUNIFORM4DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI PFNGLUNIFORM4DPROC _ptrc_glUniform4d;
#define glUniform4d _ptrc_glUniform4d
typedef void (APIENTRYP PFNGLUNIFORM1DVPROC)(GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLUNIFORM1DVPROC _ptrc_glUniform1dv;
#define glUniform1dv _ptrc_glUniform1dv
typedef void (APIENTRYP PFNGLUNIFORM2DVPROC)(GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLUNIFORM2DVPROC _ptrc_glUniform2dv;
#define glUniform2dv _ptrc_glUniform2dv
typedef void (APIENTRYP PFNGLUNIFORM3DVPROC)(GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLUNIFORM3DVPROC _ptrc_glUniform3dv;
#define glUniform3dv _ptrc_glUniform3dv
typedef void (APIENTRYP PFNGLUNIFORM4DVPROC)(GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLUNIFORM4DVPROC _ptrc_glUniform4dv;
#define glUniform4dv _ptrc_glUniform4dv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX2DVPROC _ptrc_glUniformMatrix2dv;
#define glUniformMatrix2dv _ptrc_glUniformMatrix2dv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX3DVPROC _ptrc_glUniformMatrix3dv;
#define glUniformMatrix3dv _ptrc_glUniformMatrix3dv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX4DVPROC _ptrc_glUniformMatrix4dv;
#define glUniformMatrix4dv _ptrc_glUniformMatrix4dv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX2X3DVPROC _ptrc_glUniformMatrix2x3dv;
#define glUniformMatrix2x3dv _ptrc_glUniformMatrix2x3dv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX2X4DVPROC _ptrc_glUniformMatrix2x4dv;
#define glUniformMatrix2x4dv _ptrc_glUniformMatrix2x4dv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX3X2DVPROC _ptrc_glUniformMatrix3x2dv;
#define glUniformMatrix3x2dv _ptrc_glUniformMatrix3x2dv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX3X4DVPROC _ptrc_glUniformMatrix3x4dv;
#define glUniformMatrix3x4dv _ptrc_glUniformMatrix3x4dv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX4X2DVPROC _ptrc_glUniformMatrix4x2dv;
#define glUniformMatrix4x2dv _ptrc_glUniformMatrix4x2dv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLUNIFORMMATRIX4X3DVPROC _ptrc_glUniformMatrix4x3dv;
#define glUniformMatrix4x3dv _ptrc_glUniformMatrix4x3dv
typedef void (APIENTRYP PFNGLGETUNIFORMDVPROC)(GLuint program, GLint location, GLdouble *params);
GLAPI PFNGLGETUNIFORMDVPROC _ptrc_glGetUniformdv;
#define glGetUniformdv _ptrc_glGetUniformdv
typedef GLint (APIENTRYP PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)(GLuint program, GLenum shadertype, const GLchar *name);
GLAPI PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC _ptrc_glGetSubroutineUniformLocation;
#define glGetSubroutineUniformLocation _ptrc_glGetSubroutineUniformLocation
typedef GLuint (APIENTRYP PFNGLGETSUBROUTINEINDEXPROC)(GLuint program, GLenum shadertype, const GLchar *name);
GLAPI PFNGLGETSUBROUTINEINDEXPROC _ptrc_glGetSubroutineIndex;
#define glGetSubroutineIndex _ptrc_glGetSubroutineIndex
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
GLAPI PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC _ptrc_glGetActiveSubroutineUniformiv;
#define glGetActiveSubroutineUniformiv _ptrc_glGetActiveSubroutineUniformiv
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
GLAPI PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC _ptrc_glGetActiveSubroutineUniformName;
#define glGetActiveSubroutineUniformName _ptrc_glGetActiveSubroutineUniformName
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINENAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
GLAPI PFNGLGETACTIVESUBROUTINENAMEPROC _ptrc_glGetActiveSubroutineName;
#define glGetActiveSubroutineName _ptrc_glGetActiveSubroutineName
typedef void (APIENTRYP PFNGLUNIFORMSUBROUTINESUIVPROC)(GLenum shadertype, GLsizei count, const GLuint *indices);
GLAPI PFNGLUNIFORMSUBROUTINESUIVPROC _ptrc_glUniformSubroutinesuiv;
#define glUniformSubroutinesuiv _ptrc_glUniformSubroutinesuiv
typedef void (APIENTRYP PFNGLGETUNIFORMSUBROUTINEUIVPROC)(GLenum shadertype, GLint location, GLuint *params);
GLAPI PFNGLGETUNIFORMSUBROUTINEUIVPROC _ptrc_glGetUniformSubroutineuiv;
#define glGetUniformSubroutineuiv _ptrc_glGetUniformSubroutineuiv
typedef void (APIENTRYP PFNGLGETPROGRAMSTAGEIVPROC)(GLuint program, GLenum shadertype, GLenum pname, GLint *values);
GLAPI PFNGLGETPROGRAMSTAGEIVPROC _ptrc_glGetProgramStageiv;
#define glGetProgramStageiv _ptrc_glGetProgramStageiv
typedef void (APIENTRYP PFNGLPATCHPARAMETERIPROC)(GLenum pname, GLint value);
GLAPI PFNGLPATCHPARAMETERIPROC _ptrc_glPatchParameteri;
#define glPatchParameteri _ptrc_glPatchParameteri
typedef void (APIENTRYP PFNGLPATCHPARAMETERFVPROC)(GLenum pname, const GLfloat *values);
GLAPI PFNGLPATCHPARAMETERFVPROC _ptrc_glPatchParameterfv;
#define glPatchParameterfv _ptrc_glPatchParameterfv
typedef void (APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC)(GLenum target, GLuint id);
GLAPI PFNGLBINDTRANSFORMFEEDBACKPROC _ptrc_glBindTransformFeedback;
#define glBindTransformFeedback _ptrc_glBindTransformFeedback
typedef void (APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC)(GLsizei n, const GLuint *ids);
GLAPI PFNGLDELETETRANSFORMFEEDBACKSPROC _ptrc_glDeleteTransformFeedbacks;
#define glDeleteTransformFeedbacks _ptrc_glDeleteTransformFeedbacks
typedef void (APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint *ids);
GLAPI PFNGLGENTRANSFORMFEEDBACKSPROC _ptrc_glGenTransformFeedbacks;
#define glGenTransformFeedbacks _ptrc_glGenTransformFeedbacks
typedef GLboolean (APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC)(GLuint id);
GLAPI PFNGLISTRANSFORMFEEDBACKPROC _ptrc_glIsTransformFeedback;
#define glIsTransformFeedback _ptrc_glIsTransformFeedback
typedef void (APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC)(void);
GLAPI PFNGLPAUSETRANSFORMFEEDBACKPROC _ptrc_glPauseTransformFeedback;
#define glPauseTransformFeedback _ptrc_glPauseTransformFeedback
typedef void (APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC)(void);
GLAPI PFNGLRESUMETRANSFORMFEEDBACKPROC _ptrc_glResumeTransformFeedback;
#define glResumeTransformFeedback _ptrc_glResumeTransformFeedback
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKPROC)(GLenum mode, GLuint id);
GLAPI PFNGLDRAWTRANSFORMFEEDBACKPROC _ptrc_glDrawTransformFeedback;
#define glDrawTransformFeedback _ptrc_glDrawTransformFeedback
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum mode, GLuint id, GLuint stream);
GLAPI PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC _ptrc_glDrawTransformFeedbackStream;
#define glDrawTransformFeedbackStream _ptrc_glDrawTransformFeedbackStream
typedef void (APIENTRYP PFNGLBEGINQUERYINDEXEDPROC)(GLenum target, GLuint index, GLuint id);
GLAPI PFNGLBEGINQUERYINDEXEDPROC _ptrc_glBeginQueryIndexed;
#define glBeginQueryIndexed _ptrc_glBeginQueryIndexed
typedef void (APIENTRYP PFNGLENDQUERYINDEXEDPROC)(GLenum target, GLuint index);
GLAPI PFNGLENDQUERYINDEXEDPROC _ptrc_glEndQueryIndexed;
#define glEndQueryIndexed _ptrc_glEndQueryIndexed
typedef void (APIENTRYP PFNGLGETQUERYINDEXEDIVPROC)(GLenum target, GLuint index, GLenum pname, GLint *params);
GLAPI PFNGLGETQUERYINDEXEDIVPROC _ptrc_glGetQueryIndexediv;
#define glGetQueryIndexediv _ptrc_glGetQueryIndexediv
