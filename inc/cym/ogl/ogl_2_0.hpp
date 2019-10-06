GLAPI int   OGL_VERSION_2_0;

typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
GLAPI PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;

typedef void (APIENTRYP PFNGLDRAWBUFFERSPROC)(GLsizei n, const GLenum *bufs);
GLAPI PFNGLDRAWBUFFERSPROC glDrawBuffers;

typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GLAPI PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate;

typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC)(GLenum face, GLenum func, GLint ref, GLuint mask);
GLAPI PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;

typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, GLuint mask);
GLAPI PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;

typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
GLAPI PFNGLATTACHSHADERPROC glAttachShader;

typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar *name);
GLAPI PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;

typedef void (APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint shader);
GLAPI PFNGLCOMPILESHADERPROC glCompileShader;

typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC)(void);
GLAPI PFNGLCREATEPROGRAMPROC glCreateProgram;

typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC)(GLenum type);
GLAPI PFNGLCREATESHADERPROC glCreateShader;

typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC)(GLuint program);
GLAPI PFNGLDELETEPROGRAMPROC glDeleteProgram;

typedef void (APIENTRYP PFNGLDELETESHADERPROC)(GLuint shader);
GLAPI PFNGLDELETESHADERPROC glDeleteShader;

typedef void (APIENTRYP PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
GLAPI PFNGLDETACHSHADERPROC glDetachShader;

typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
GLAPI PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
GLAPI PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
GLAPI PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;

typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
GLAPI PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;

typedef void (APIENTRYP PFNGLGETATTACHEDSHADERSPROC)(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
GLAPI PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;

typedef GLint (APIENTRYP PFNGLGETATTRIBLOCATIONPROC)(GLuint program, const GLchar *name);
GLAPI PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;

typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
GLAPI PFNGLGETPROGRAMIVPROC glGetProgramiv;

typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GLAPI PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

typedef void (APIENTRYP PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
GLAPI PFNGLGETSHADERIVPROC glGetShaderiv;

typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GLAPI PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

typedef void (APIENTRYP PFNGLGETSHADERSOURCEPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
GLAPI PFNGLGETSHADERSOURCEPROC glGetShaderSource;

typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);
GLAPI PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

typedef void (APIENTRYP PFNGLGETUNIFORMFVPROC)(GLuint program, GLint location, GLfloat *params);
GLAPI PFNGLGETUNIFORMFVPROC glGetUniformfv;

typedef void (APIENTRYP PFNGLGETUNIFORMIVPROC)(GLuint program, GLint location, GLint *params);
GLAPI PFNGLGETUNIFORMIVPROC glGetUniformiv;

typedef void (APIENTRYP PFNGLGETVERTEXATTRIBDVPROC)(GLuint index, GLenum pname, GLdouble *params);
GLAPI PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv;

typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC)(GLuint index, GLenum pname, GLfloat *params);
GLAPI PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;

typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC)(GLuint index, GLenum pname, GLint *params);
GLAPI PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;

typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint index, GLenum pname, void **pointer);
GLAPI PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;

typedef GLboolean (APIENTRYP PFNGLISPROGRAMPROC)(GLuint program);
GLAPI PFNGLISPROGRAMPROC glIsProgram;

typedef GLboolean (APIENTRYP PFNGLISSHADERPROC)(GLuint shader);
GLAPI PFNGLISSHADERPROC glIsShader;

typedef void (APIENTRYP PFNGLLINKPROGRAMPROC)(GLuint program);
GLAPI PFNGLLINKPROGRAMPROC glLinkProgram;

typedef void (APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
GLAPI PFNGLSHADERSOURCEPROC glShaderSource;

typedef void (APIENTRYP PFNGLUSEPROGRAMPROC)(GLuint program);
GLAPI PFNGLUSEPROGRAMPROC glUseProgram;

typedef void (APIENTRYP PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
GLAPI PFNGLUNIFORM1FPROC glUniform1f;

typedef void (APIENTRYP PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
GLAPI PFNGLUNIFORM2FPROC glUniform2f;

typedef void (APIENTRYP PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GLAPI PFNGLUNIFORM3FPROC glUniform3f;

typedef void (APIENTRYP PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GLAPI PFNGLUNIFORM4FPROC glUniform4f;

typedef void (APIENTRYP PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
GLAPI PFNGLUNIFORM1IPROC glUniform1i;

typedef void (APIENTRYP PFNGLUNIFORM2IPROC)(GLint location, GLint v0, GLint v1);
GLAPI PFNGLUNIFORM2IPROC glUniform2i;

typedef void (APIENTRYP PFNGLUNIFORM3IPROC)(GLint location, GLint v0, GLint v1, GLint v2);
GLAPI PFNGLUNIFORM3IPROC glUniform3i;

typedef void (APIENTRYP PFNGLUNIFORM4IPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GLAPI PFNGLUNIFORM4IPROC glUniform4i;

typedef void (APIENTRYP PFNGLUNIFORM1FVPROC)(GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLUNIFORM1FVPROC glUniform1fv;

typedef void (APIENTRYP PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLUNIFORM2FVPROC glUniform2fv;

typedef void (APIENTRYP PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLUNIFORM3FVPROC glUniform3fv;

typedef void (APIENTRYP PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLUNIFORM4FVPROC glUniform4fv;

typedef void (APIENTRYP PFNGLUNIFORM1IVPROC)(GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLUNIFORM1IVPROC glUniform1iv;

typedef void (APIENTRYP PFNGLUNIFORM2IVPROC)(GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLUNIFORM2IVPROC glUniform2iv;

typedef void (APIENTRYP PFNGLUNIFORM3IVPROC)(GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLUNIFORM3IVPROC glUniform3iv;

typedef void (APIENTRYP PFNGLUNIFORM4IVPROC)(GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLUNIFORM4IVPROC glUniform4iv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;

typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC)(GLuint program);
GLAPI PFNGLVALIDATEPROGRAMPROC glValidateProgram;

typedef void (APIENTRYP PFNGLVERTEXATTRIB1DPROC)(GLuint index, GLdouble x);
GLAPI PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d;

typedef void (APIENTRYP PFNGLVERTEXATTRIB1DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
GLAPI PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;

typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC)(GLuint index, const GLfloat *v);
GLAPI PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB1SPROC)(GLuint index, GLshort x);
GLAPI PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s;

typedef void (APIENTRYP PFNGLVERTEXATTRIB1SVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB2DPROC)(GLuint index, GLdouble x, GLdouble y);
GLAPI PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d;

typedef void (APIENTRYP PFNGLVERTEXATTRIB2DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
GLAPI PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;

typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC)(GLuint index, const GLfloat *v);
GLAPI PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB2SPROC)(GLuint index, GLshort x, GLshort y);
GLAPI PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s;

typedef void (APIENTRYP PFNGLVERTEXATTRIB2SVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
GLAPI PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d;

typedef void (APIENTRYP PFNGLVERTEXATTRIB3DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
GLAPI PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;

typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC)(GLuint index, const GLfloat *v);
GLAPI PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB3SPROC)(GLuint index, GLshort x, GLshort y, GLshort z);
GLAPI PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s;

typedef void (APIENTRYP PFNGLVERTEXATTRIB3SVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4NBVPROC)(GLuint index, const GLbyte *v);
GLAPI PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4NIVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4NSVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBPROC)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
GLAPI PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBVPROC)(GLuint index, const GLubyte *v);
GLAPI PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUSVPROC)(GLuint index, const GLushort *v);
GLAPI PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4BVPROC)(GLuint index, const GLbyte *v);
GLAPI PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLAPI PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC)(GLuint index, const GLfloat *v);
GLAPI PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4IVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4SPROC)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
GLAPI PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4SVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4UBVPROC)(GLuint index, const GLubyte *v);
GLAPI PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4UIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv;

typedef void (APIENTRYP PFNGLVERTEXATTRIB4USVPROC)(GLuint index, const GLushort *v);
GLAPI PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
GLAPI PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

