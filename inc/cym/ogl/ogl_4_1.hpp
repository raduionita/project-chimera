GLAPI int   OGL_VERSION_4_1;

typedef void (APIENTRYP PFNGLRELEASESHADERCOMPILERPROC)(void);
GLAPI PFNGLRELEASESHADERCOMPILERPROC _ptrc_glReleaseShaderCompiler;
#define glReleaseShaderCompiler _ptrc_glReleaseShaderCompiler
typedef void (APIENTRYP PFNGLSHADERBINARYPROC)(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length);
GLAPI PFNGLSHADERBINARYPROC _ptrc_glShaderBinary;
#define glShaderBinary _ptrc_glShaderBinary
typedef void (APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC)(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GLAPI PFNGLGETSHADERPRECISIONFORMATPROC _ptrc_glGetShaderPrecisionFormat;
#define glGetShaderPrecisionFormat _ptrc_glGetShaderPrecisionFormat
typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC)(GLfloat n, GLfloat f);
GLAPI PFNGLDEPTHRANGEFPROC _ptrc_glDepthRangef;
#define glDepthRangef _ptrc_glDepthRangef
typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC)(GLfloat d);
GLAPI PFNGLCLEARDEPTHFPROC _ptrc_glClearDepthf;
#define glClearDepthf _ptrc_glClearDepthf
typedef void (APIENTRYP PFNGLGETPROGRAMBINARYPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
GLAPI PFNGLGETPROGRAMBINARYPROC _ptrc_glGetProgramBinary;
#define glGetProgramBinary _ptrc_glGetProgramBinary
typedef void (APIENTRYP PFNGLPROGRAMBINARYPROC)(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
GLAPI PFNGLPROGRAMBINARYPROC _ptrc_glProgramBinary;
#define glProgramBinary _ptrc_glProgramBinary
typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIPROC)(GLuint program, GLenum pname, GLint value);
GLAPI PFNGLPROGRAMPARAMETERIPROC _ptrc_glProgramParameteri;
#define glProgramParameteri _ptrc_glProgramParameteri
typedef void (APIENTRYP PFNGLUSEPROGRAMSTAGESPROC)(GLuint pipeline, GLbitfield stages, GLuint program);
GLAPI PFNGLUSEPROGRAMSTAGESPROC _ptrc_glUseProgramStages;
#define glUseProgramStages _ptrc_glUseProgramStages
typedef void (APIENTRYP PFNGLACTIVESHADERPROGRAMPROC)(GLuint pipeline, GLuint program);
GLAPI PFNGLACTIVESHADERPROGRAMPROC _ptrc_glActiveShaderProgram;
#define glActiveShaderProgram _ptrc_glActiveShaderProgram
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROGRAMVPROC)(GLenum type, GLsizei count, const GLchar *const*strings);
GLAPI PFNGLCREATESHADERPROGRAMVPROC _ptrc_glCreateShaderProgramv;
#define glCreateShaderProgramv _ptrc_glCreateShaderProgramv
typedef void (APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC)(GLuint pipeline);
GLAPI PFNGLBINDPROGRAMPIPELINEPROC _ptrc_glBindProgramPipeline;
#define glBindProgramPipeline _ptrc_glBindProgramPipeline
typedef void (APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC)(GLsizei n, const GLuint *pipelines);
GLAPI PFNGLDELETEPROGRAMPIPELINESPROC _ptrc_glDeleteProgramPipelines;
#define glDeleteProgramPipelines _ptrc_glDeleteProgramPipelines
typedef void (APIENTRYP PFNGLGENPROGRAMPIPELINESPROC)(GLsizei n, GLuint *pipelines);
GLAPI PFNGLGENPROGRAMPIPELINESPROC _ptrc_glGenProgramPipelines;
#define glGenProgramPipelines _ptrc_glGenProgramPipelines
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPIPELINEPROC)(GLuint pipeline);
GLAPI PFNGLISPROGRAMPIPELINEPROC _ptrc_glIsProgramPipeline;
#define glIsProgramPipeline _ptrc_glIsProgramPipeline
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC)(GLuint pipeline, GLenum pname, GLint *params);
GLAPI PFNGLGETPROGRAMPIPELINEIVPROC _ptrc_glGetProgramPipelineiv;
#define glGetProgramPipelineiv _ptrc_glGetProgramPipelineiv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IPROC)(GLuint program, GLint location, GLint v0);
GLAPI PFNGLPROGRAMUNIFORM1IPROC _ptrc_glProgramUniform1i;
#define glProgramUniform1i _ptrc_glProgramUniform1i
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLPROGRAMUNIFORM1IVPROC _ptrc_glProgramUniform1iv;
#define glProgramUniform1iv _ptrc_glProgramUniform1iv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FPROC)(GLuint program, GLint location, GLfloat v0);
GLAPI PFNGLPROGRAMUNIFORM1FPROC _ptrc_glProgramUniform1f;
#define glProgramUniform1f _ptrc_glProgramUniform1f
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORM1FVPROC _ptrc_glProgramUniform1fv;
#define glProgramUniform1fv _ptrc_glProgramUniform1fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DPROC)(GLuint program, GLint location, GLdouble v0);
GLAPI PFNGLPROGRAMUNIFORM1DPROC _ptrc_glProgramUniform1d;
#define glProgramUniform1d _ptrc_glProgramUniform1d
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORM1DVPROC _ptrc_glProgramUniform1dv;
#define glProgramUniform1dv _ptrc_glProgramUniform1dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC)(GLuint program, GLint location, GLuint v0);
GLAPI PFNGLPROGRAMUNIFORM1UIPROC _ptrc_glProgramUniform1ui;
#define glProgramUniform1ui _ptrc_glProgramUniform1ui
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLPROGRAMUNIFORM1UIVPROC _ptrc_glProgramUniform1uiv;
#define glProgramUniform1uiv _ptrc_glProgramUniform1uiv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IPROC)(GLuint program, GLint location, GLint v0, GLint v1);
GLAPI PFNGLPROGRAMUNIFORM2IPROC _ptrc_glProgramUniform2i;
#define glProgramUniform2i _ptrc_glProgramUniform2i
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLPROGRAMUNIFORM2IVPROC _ptrc_glProgramUniform2iv;
#define glProgramUniform2iv _ptrc_glProgramUniform2iv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
GLAPI PFNGLPROGRAMUNIFORM2FPROC _ptrc_glProgramUniform2f;
#define glProgramUniform2f _ptrc_glProgramUniform2f
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORM2FVPROC _ptrc_glProgramUniform2fv;
#define glProgramUniform2fv _ptrc_glProgramUniform2fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1);
GLAPI PFNGLPROGRAMUNIFORM2DPROC _ptrc_glProgramUniform2d;
#define glProgramUniform2d _ptrc_glProgramUniform2d
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORM2DVPROC _ptrc_glProgramUniform2dv;
#define glProgramUniform2dv _ptrc_glProgramUniform2dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1);
GLAPI PFNGLPROGRAMUNIFORM2UIPROC _ptrc_glProgramUniform2ui;
#define glProgramUniform2ui _ptrc_glProgramUniform2ui
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLPROGRAMUNIFORM2UIVPROC _ptrc_glProgramUniform2uiv;
#define glProgramUniform2uiv _ptrc_glProgramUniform2uiv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
GLAPI PFNGLPROGRAMUNIFORM3IPROC _ptrc_glProgramUniform3i;
#define glProgramUniform3i _ptrc_glProgramUniform3i
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLPROGRAMUNIFORM3IVPROC _ptrc_glProgramUniform3iv;
#define glProgramUniform3iv _ptrc_glProgramUniform3iv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GLAPI PFNGLPROGRAMUNIFORM3FPROC _ptrc_glProgramUniform3f;
#define glProgramUniform3f _ptrc_glProgramUniform3f
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORM3FVPROC _ptrc_glProgramUniform3fv;
#define glProgramUniform3fv _ptrc_glProgramUniform3fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
GLAPI PFNGLPROGRAMUNIFORM3DPROC _ptrc_glProgramUniform3d;
#define glProgramUniform3d _ptrc_glProgramUniform3d
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORM3DVPROC _ptrc_glProgramUniform3dv;
#define glProgramUniform3dv _ptrc_glProgramUniform3dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
GLAPI PFNGLPROGRAMUNIFORM3UIPROC _ptrc_glProgramUniform3ui;
#define glProgramUniform3ui _ptrc_glProgramUniform3ui
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLPROGRAMUNIFORM3UIVPROC _ptrc_glProgramUniform3uiv;
#define glProgramUniform3uiv _ptrc_glProgramUniform3uiv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GLAPI PFNGLPROGRAMUNIFORM4IPROC _ptrc_glProgramUniform4i;
#define glProgramUniform4i _ptrc_glProgramUniform4i
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLPROGRAMUNIFORM4IVPROC _ptrc_glProgramUniform4iv;
#define glProgramUniform4iv _ptrc_glProgramUniform4iv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GLAPI PFNGLPROGRAMUNIFORM4FPROC _ptrc_glProgramUniform4f;
#define glProgramUniform4f _ptrc_glProgramUniform4f
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORM4FVPROC _ptrc_glProgramUniform4fv;
#define glProgramUniform4fv _ptrc_glProgramUniform4fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
GLAPI PFNGLPROGRAMUNIFORM4DPROC _ptrc_glProgramUniform4d;
#define glProgramUniform4d _ptrc_glProgramUniform4d
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORM4DVPROC _ptrc_glProgramUniform4dv;
#define glProgramUniform4dv _ptrc_glProgramUniform4dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GLAPI PFNGLPROGRAMUNIFORM4UIPROC _ptrc_glProgramUniform4ui;
#define glProgramUniform4ui _ptrc_glProgramUniform4ui
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLPROGRAMUNIFORM4UIVPROC _ptrc_glProgramUniform4uiv;
#define glProgramUniform4uiv _ptrc_glProgramUniform4uiv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2FVPROC _ptrc_glProgramUniformMatrix2fv;
#define glProgramUniformMatrix2fv _ptrc_glProgramUniformMatrix2fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3FVPROC _ptrc_glProgramUniformMatrix3fv;
#define glProgramUniformMatrix3fv _ptrc_glProgramUniformMatrix3fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4FVPROC _ptrc_glProgramUniformMatrix4fv;
#define glProgramUniformMatrix4fv _ptrc_glProgramUniformMatrix4fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2DVPROC _ptrc_glProgramUniformMatrix2dv;
#define glProgramUniformMatrix2dv _ptrc_glProgramUniformMatrix2dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3DVPROC _ptrc_glProgramUniformMatrix3dv;
#define glProgramUniformMatrix3dv _ptrc_glProgramUniformMatrix3dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4DVPROC _ptrc_glProgramUniformMatrix4dv;
#define glProgramUniformMatrix4dv _ptrc_glProgramUniformMatrix4dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC _ptrc_glProgramUniformMatrix2x3fv;
#define glProgramUniformMatrix2x3fv _ptrc_glProgramUniformMatrix2x3fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC _ptrc_glProgramUniformMatrix3x2fv;
#define glProgramUniformMatrix3x2fv _ptrc_glProgramUniformMatrix3x2fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC _ptrc_glProgramUniformMatrix2x4fv;
#define glProgramUniformMatrix2x4fv _ptrc_glProgramUniformMatrix2x4fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC _ptrc_glProgramUniformMatrix4x2fv;
#define glProgramUniformMatrix4x2fv _ptrc_glProgramUniformMatrix4x2fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC _ptrc_glProgramUniformMatrix3x4fv;
#define glProgramUniformMatrix3x4fv _ptrc_glProgramUniformMatrix3x4fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC _ptrc_glProgramUniformMatrix4x3fv;
#define glProgramUniformMatrix4x3fv _ptrc_glProgramUniformMatrix4x3fv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC _ptrc_glProgramUniformMatrix2x3dv;
#define glProgramUniformMatrix2x3dv _ptrc_glProgramUniformMatrix2x3dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC _ptrc_glProgramUniformMatrix3x2dv;
#define glProgramUniformMatrix3x2dv _ptrc_glProgramUniformMatrix3x2dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC _ptrc_glProgramUniformMatrix2x4dv;
#define glProgramUniformMatrix2x4dv _ptrc_glProgramUniformMatrix2x4dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC _ptrc_glProgramUniformMatrix4x2dv;
#define glProgramUniformMatrix4x2dv _ptrc_glProgramUniformMatrix4x2dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC _ptrc_glProgramUniformMatrix3x4dv;
#define glProgramUniformMatrix3x4dv _ptrc_glProgramUniformMatrix3x4dv
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC _ptrc_glProgramUniformMatrix4x3dv;
#define glProgramUniformMatrix4x3dv _ptrc_glProgramUniformMatrix4x3dv
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC)(GLuint pipeline);
GLAPI PFNGLVALIDATEPROGRAMPIPELINEPROC _ptrc_glValidateProgramPipeline;
#define glValidateProgramPipeline _ptrc_glValidateProgramPipeline
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC)(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GLAPI PFNGLGETPROGRAMPIPELINEINFOLOGPROC _ptrc_glGetProgramPipelineInfoLog;
#define glGetProgramPipelineInfoLog _ptrc_glGetProgramPipelineInfoLog
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DPROC)(GLuint index, GLdouble x);
GLAPI PFNGLVERTEXATTRIBL1DPROC _ptrc_glVertexAttribL1d;
#define glVertexAttribL1d _ptrc_glVertexAttribL1d
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DPROC)(GLuint index, GLdouble x, GLdouble y);
GLAPI PFNGLVERTEXATTRIBL2DPROC _ptrc_glVertexAttribL2d;
#define glVertexAttribL2d _ptrc_glVertexAttribL2d
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
GLAPI PFNGLVERTEXATTRIBL3DPROC _ptrc_glVertexAttribL3d;
#define glVertexAttribL3d _ptrc_glVertexAttribL3d
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI PFNGLVERTEXATTRIBL4DPROC _ptrc_glVertexAttribL4d;
#define glVertexAttribL4d _ptrc_glVertexAttribL4d
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIBL1DVPROC _ptrc_glVertexAttribL1dv;
#define glVertexAttribL1dv _ptrc_glVertexAttribL1dv
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIBL2DVPROC _ptrc_glVertexAttribL2dv;
#define glVertexAttribL2dv _ptrc_glVertexAttribL2dv
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIBL3DVPROC _ptrc_glVertexAttribL3dv;
#define glVertexAttribL3dv _ptrc_glVertexAttribL3dv
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIBL4DVPROC _ptrc_glVertexAttribL4dv;
#define glVertexAttribL4dv _ptrc_glVertexAttribL4dv
typedef void (APIENTRYP PFNGLVERTEXATTRIBLPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
GLAPI PFNGLVERTEXATTRIBLPOINTERPROC _ptrc_glVertexAttribLPointer;
#define glVertexAttribLPointer _ptrc_glVertexAttribLPointer
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLDVPROC)(GLuint index, GLenum pname, GLdouble *params);
GLAPI PFNGLGETVERTEXATTRIBLDVPROC _ptrc_glGetVertexAttribLdv;
#define glGetVertexAttribLdv _ptrc_glGetVertexAttribLdv
typedef void (APIENTRYP PFNGLVIEWPORTARRAYVPROC)(GLuint first, GLsizei count, const GLfloat *v);
GLAPI PFNGLVIEWPORTARRAYVPROC _ptrc_glViewportArrayv;
#define glViewportArrayv _ptrc_glViewportArrayv
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GLAPI PFNGLVIEWPORTINDEXEDFPROC _ptrc_glViewportIndexedf;
#define glViewportIndexedf _ptrc_glViewportIndexedf
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFVPROC)(GLuint index, const GLfloat *v);
GLAPI PFNGLVIEWPORTINDEXEDFVPROC _ptrc_glViewportIndexedfv;
#define glViewportIndexedfv _ptrc_glViewportIndexedfv
typedef void (APIENTRYP PFNGLSCISSORARRAYVPROC)(GLuint first, GLsizei count, const GLint *v);
GLAPI PFNGLSCISSORARRAYVPROC _ptrc_glScissorArrayv;
#define glScissorArrayv _ptrc_glScissorArrayv
typedef void (APIENTRYP PFNGLSCISSORINDEXEDPROC)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
GLAPI PFNGLSCISSORINDEXEDPROC _ptrc_glScissorIndexed;
#define glScissorIndexed _ptrc_glScissorIndexed
typedef void (APIENTRYP PFNGLSCISSORINDEXEDVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLSCISSORINDEXEDVPROC _ptrc_glScissorIndexedv;
#define glScissorIndexedv _ptrc_glScissorIndexedv
typedef void (APIENTRYP PFNGLDEPTHRANGEARRAYVPROC)(GLuint first, GLsizei count, const GLdouble *v);
GLAPI PFNGLDEPTHRANGEARRAYVPROC _ptrc_glDepthRangeArrayv;
#define glDepthRangeArrayv _ptrc_glDepthRangeArrayv
typedef void (APIENTRYP PFNGLDEPTHRANGEINDEXEDPROC)(GLuint index, GLdouble n, GLdouble f);
GLAPI PFNGLDEPTHRANGEINDEXEDPROC _ptrc_glDepthRangeIndexed;
#define glDepthRangeIndexed _ptrc_glDepthRangeIndexed
typedef void (APIENTRYP PFNGLGETFLOATI_VPROC)(GLenum target, GLuint index, GLfloat *data);
GLAPI PFNGLGETFLOATI_VPROC _ptrc_glGetFloati_v;
#define glGetFloati_v _ptrc_glGetFloati_v
typedef void (APIENTRYP PFNGLGETDOUBLEI_VPROC)(GLenum target, GLuint index, GLdouble *data);
GLAPI PFNGLGETDOUBLEI_VPROC _ptrc_glGetDoublei_v;
#define glGetDoublei_v _ptrc_glGetDoublei_v
