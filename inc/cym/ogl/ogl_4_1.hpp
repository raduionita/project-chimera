GLAPI int   OGL_VERSION_4_1;

typedef void (APIENTRYP PFNGLRELEASESHADERCOMPILERPROC)(void);
GLAPI PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler;

typedef void (APIENTRYP PFNGLSHADERBINARYPROC)(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length);
GLAPI PFNGLSHADERBINARYPROC glShaderBinary;

typedef void (APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC)(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GLAPI PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat;

typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC)(GLfloat n, GLfloat f);
GLAPI PFNGLDEPTHRANGEFPROC glDepthRangef;

typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC)(GLfloat d);
GLAPI PFNGLCLEARDEPTHFPROC glClearDepthf;

typedef void (APIENTRYP PFNGLGETPROGRAMBINARYPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
GLAPI PFNGLGETPROGRAMBINARYPROC glGetProgramBinary;

typedef void (APIENTRYP PFNGLPROGRAMBINARYPROC)(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
GLAPI PFNGLPROGRAMBINARYPROC glProgramBinary;

typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIPROC)(GLuint program, GLenum pname, GLint value);
GLAPI PFNGLPROGRAMPARAMETERIPROC glProgramParameteri;

typedef void (APIENTRYP PFNGLUSEPROGRAMSTAGESPROC)(GLuint pipeline, GLbitfield stages, GLuint program);
GLAPI PFNGLUSEPROGRAMSTAGESPROC glUseProgramStages;

typedef void (APIENTRYP PFNGLACTIVESHADERPROGRAMPROC)(GLuint pipeline, GLuint program);
GLAPI PFNGLACTIVESHADERPROGRAMPROC glActiveShaderProgram;

typedef GLuint (APIENTRYP PFNGLCREATESHADERPROGRAMVPROC)(GLenum type, GLsizei count, const GLchar *const*strings);
GLAPI PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv;

typedef void (APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC)(GLuint pipeline);
GLAPI PFNGLBINDPROGRAMPIPELINEPROC glBindProgramPipeline;

typedef void (APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC)(GLsizei n, const GLuint *pipelines);
GLAPI PFNGLDELETEPROGRAMPIPELINESPROC glDeleteProgramPipelines;

typedef void (APIENTRYP PFNGLGENPROGRAMPIPELINESPROC)(GLsizei n, GLuint *pipelines);
GLAPI PFNGLGENPROGRAMPIPELINESPROC glGenProgramPipelines;

typedef GLboolean (APIENTRYP PFNGLISPROGRAMPIPELINEPROC)(GLuint pipeline);
GLAPI PFNGLISPROGRAMPIPELINEPROC glIsProgramPipeline;

typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC)(GLuint pipeline, GLenum pname, GLint *params);
GLAPI PFNGLGETPROGRAMPIPELINEIVPROC glGetProgramPipelineiv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IPROC)(GLuint program, GLint location, GLint v0);
GLAPI PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1iv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FPROC)(GLuint program, GLint location, GLfloat v0);
GLAPI PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DPROC)(GLuint program, GLint location, GLdouble v0);
GLAPI PFNGLPROGRAMUNIFORM1DPROC glProgramUniform1d;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORM1DVPROC glProgramUniform1dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC)(GLuint program, GLint location, GLuint v0);
GLAPI PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1ui;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uiv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IPROC)(GLuint program, GLint location, GLint v0, GLint v1);
GLAPI PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2i;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2iv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
GLAPI PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1);
GLAPI PFNGLPROGRAMUNIFORM2DPROC glProgramUniform2d;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORM2DVPROC glProgramUniform2dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1);
GLAPI PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2ui;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uiv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
GLAPI PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3i;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3iv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GLAPI PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
GLAPI PFNGLPROGRAMUNIFORM3DPROC glProgramUniform3d;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORM3DVPROC glProgramUniform3dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
GLAPI PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3ui;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uiv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GLAPI PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4iv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GLAPI PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
GLAPI PFNGLPROGRAMUNIFORM4DPROC glProgramUniform4d;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORM4DVPROC glProgramUniform4dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GLAPI PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4ui;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uiv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2DVPROC glProgramUniformMatrix2dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3DVPROC glProgramUniformMatrix3dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4DVPROC glProgramUniformMatrix4dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glProgramUniformMatrix2x3dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glProgramUniformMatrix3x2dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glProgramUniformMatrix2x4dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glProgramUniformMatrix4x2dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glProgramUniformMatrix3x4dv;

typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
GLAPI PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glProgramUniformMatrix4x3dv;

typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC)(GLuint pipeline);
GLAPI PFNGLVALIDATEPROGRAMPIPELINEPROC glValidateProgramPipeline;

typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC)(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GLAPI PFNGLGETPROGRAMPIPELINEINFOLOGPROC glGetProgramPipelineInfoLog;

typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DPROC)(GLuint index, GLdouble x);
GLAPI PFNGLVERTEXATTRIBL1DPROC glVertexAttribL1d;

typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DPROC)(GLuint index, GLdouble x, GLdouble y);
GLAPI PFNGLVERTEXATTRIBL2DPROC glVertexAttribL2d;

typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
GLAPI PFNGLVERTEXATTRIBL3DPROC glVertexAttribL3d;

typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI PFNGLVERTEXATTRIBL4DPROC glVertexAttribL4d;

typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIBL1DVPROC glVertexAttribL1dv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIBL2DVPROC glVertexAttribL2dv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIBL3DVPROC glVertexAttribL3dv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIBL4DVPROC glVertexAttribL4dv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBLPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
GLAPI PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttribLPointer;

typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLDVPROC)(GLuint index, GLenum pname, GLdouble *params);
GLAPI PFNGLGETVERTEXATTRIBLDVPROC glGetVertexAttribLdv;

typedef void (APIENTRYP PFNGLVIEWPORTARRAYVPROC)(GLuint first, GLsizei count, const GLfloat *v);
GLAPI PFNGLVIEWPORTARRAYVPROC glViewportArrayv;

typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GLAPI PFNGLVIEWPORTINDEXEDFPROC glViewportIndexedf;

typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFVPROC)(GLuint index, const GLfloat *v);
GLAPI PFNGLVIEWPORTINDEXEDFVPROC glViewportIndexedfv;

typedef void (APIENTRYP PFNGLSCISSORARRAYVPROC)(GLuint first, GLsizei count, const GLint *v);
GLAPI PFNGLSCISSORARRAYVPROC glScissorArrayv;

typedef void (APIENTRYP PFNGLSCISSORINDEXEDPROC)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
GLAPI PFNGLSCISSORINDEXEDPROC glScissorIndexed;

typedef void (APIENTRYP PFNGLSCISSORINDEXEDVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLSCISSORINDEXEDVPROC glScissorIndexedv;

typedef void (APIENTRYP PFNGLDEPTHRANGEARRAYVPROC)(GLuint first, GLsizei count, const GLdouble *v);
GLAPI PFNGLDEPTHRANGEARRAYVPROC glDepthRangeArrayv;

typedef void (APIENTRYP PFNGLDEPTHRANGEINDEXEDPROC)(GLuint index, GLdouble n, GLdouble f);
GLAPI PFNGLDEPTHRANGEINDEXEDPROC glDepthRangeIndexed;

typedef void (APIENTRYP PFNGLGETFLOATI_VPROC)(GLenum target, GLuint index, GLfloat *data);
GLAPI PFNGLGETFLOATI_VPROC glGetFloati_v;

typedef void (APIENTRYP PFNGLGETDOUBLEI_VPROC)(GLenum target, GLuint index, GLdouble *data);
GLAPI PFNGLGETDOUBLEI_VPROC glGetDoublei_v;

