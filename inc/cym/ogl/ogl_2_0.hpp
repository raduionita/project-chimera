GLAPI int   OGL_VERSION_2_0;

typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
GLAPI PFNGLBLENDEQUATIONSEPARATEPROC _ptrc_glBlendEquationSeparate;
#define glBlendEquationSeparate _ptrc_glBlendEquationSeparate
typedef void (APIENTRYP PFNGLDRAWBUFFERSPROC)(GLsizei n, const GLenum *bufs);
GLAPI PFNGLDRAWBUFFERSPROC _ptrc_glDrawBuffers;
#define glDrawBuffers _ptrc_glDrawBuffers
typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GLAPI PFNGLSTENCILOPSEPARATEPROC _ptrc_glStencilOpSeparate;
#define glStencilOpSeparate _ptrc_glStencilOpSeparate
typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC)(GLenum face, GLenum func, GLint ref, GLuint mask);
GLAPI PFNGLSTENCILFUNCSEPARATEPROC _ptrc_glStencilFuncSeparate;
#define glStencilFuncSeparate _ptrc_glStencilFuncSeparate
typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, GLuint mask);
GLAPI PFNGLSTENCILMASKSEPARATEPROC _ptrc_glStencilMaskSeparate;
#define glStencilMaskSeparate _ptrc_glStencilMaskSeparate
typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
GLAPI PFNGLATTACHSHADERPROC _ptrc_glAttachShader;
#define glAttachShader _ptrc_glAttachShader
typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar *name);
GLAPI PFNGLBINDATTRIBLOCATIONPROC _ptrc_glBindAttribLocation;
#define glBindAttribLocation _ptrc_glBindAttribLocation
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint shader);
GLAPI PFNGLCOMPILESHADERPROC _ptrc_glCompileShader;
#define glCompileShader _ptrc_glCompileShader
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC)(void);
GLAPI PFNGLCREATEPROGRAMPROC _ptrc_glCreateProgram;
#define glCreateProgram _ptrc_glCreateProgram
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC)(GLenum type);
GLAPI PFNGLCREATESHADERPROC _ptrc_glCreateShader;
#define glCreateShader _ptrc_glCreateShader
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC)(GLuint program);
GLAPI PFNGLDELETEPROGRAMPROC _ptrc_glDeleteProgram;
#define glDeleteProgram _ptrc_glDeleteProgram
typedef void (APIENTRYP PFNGLDELETESHADERPROC)(GLuint shader);
GLAPI PFNGLDELETESHADERPROC _ptrc_glDeleteShader;
#define glDeleteShader _ptrc_glDeleteShader
typedef void (APIENTRYP PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
GLAPI PFNGLDETACHSHADERPROC _ptrc_glDetachShader;
#define glDetachShader _ptrc_glDetachShader
typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
GLAPI PFNGLDISABLEVERTEXATTRIBARRAYPROC _ptrc_glDisableVertexAttribArray;
#define glDisableVertexAttribArray _ptrc_glDisableVertexAttribArray
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
GLAPI PFNGLENABLEVERTEXATTRIBARRAYPROC _ptrc_glEnableVertexAttribArray;
#define glEnableVertexAttribArray _ptrc_glEnableVertexAttribArray
typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
GLAPI PFNGLGETACTIVEATTRIBPROC _ptrc_glGetActiveAttrib;
#define glGetActiveAttrib _ptrc_glGetActiveAttrib
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
GLAPI PFNGLGETACTIVEUNIFORMPROC _ptrc_glGetActiveUniform;
#define glGetActiveUniform _ptrc_glGetActiveUniform
typedef void (APIENTRYP PFNGLGETATTACHEDSHADERSPROC)(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
GLAPI PFNGLGETATTACHEDSHADERSPROC _ptrc_glGetAttachedShaders;
#define glGetAttachedShaders _ptrc_glGetAttachedShaders
typedef GLint (APIENTRYP PFNGLGETATTRIBLOCATIONPROC)(GLuint program, const GLchar *name);
GLAPI PFNGLGETATTRIBLOCATIONPROC _ptrc_glGetAttribLocation;
#define glGetAttribLocation _ptrc_glGetAttribLocation
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
GLAPI PFNGLGETPROGRAMIVPROC _ptrc_glGetProgramiv;
#define glGetProgramiv _ptrc_glGetProgramiv
typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GLAPI PFNGLGETPROGRAMINFOLOGPROC _ptrc_glGetProgramInfoLog;
#define glGetProgramInfoLog _ptrc_glGetProgramInfoLog
typedef void (APIENTRYP PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
GLAPI PFNGLGETSHADERIVPROC _ptrc_glGetShaderiv;
#define glGetShaderiv _ptrc_glGetShaderiv
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GLAPI PFNGLGETSHADERINFOLOGPROC _ptrc_glGetShaderInfoLog;
#define glGetShaderInfoLog _ptrc_glGetShaderInfoLog
typedef void (APIENTRYP PFNGLGETSHADERSOURCEPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
GLAPI PFNGLGETSHADERSOURCEPROC _ptrc_glGetShaderSource;
#define glGetShaderSource _ptrc_glGetShaderSource
typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);
GLAPI PFNGLGETUNIFORMLOCATIONPROC _ptrc_glGetUniformLocation;
#define glGetUniformLocation _ptrc_glGetUniformLocation
typedef void (APIENTRYP PFNGLGETUNIFORMFVPROC)(GLuint program, GLint location, GLfloat *params);
GLAPI PFNGLGETUNIFORMFVPROC _ptrc_glGetUniformfv;
#define glGetUniformfv _ptrc_glGetUniformfv
typedef void (APIENTRYP PFNGLGETUNIFORMIVPROC)(GLuint program, GLint location, GLint *params);
GLAPI PFNGLGETUNIFORMIVPROC _ptrc_glGetUniformiv;
#define glGetUniformiv _ptrc_glGetUniformiv
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBDVPROC)(GLuint index, GLenum pname, GLdouble *params);
GLAPI PFNGLGETVERTEXATTRIBDVPROC _ptrc_glGetVertexAttribdv;
#define glGetVertexAttribdv _ptrc_glGetVertexAttribdv
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC)(GLuint index, GLenum pname, GLfloat *params);
GLAPI PFNGLGETVERTEXATTRIBFVPROC _ptrc_glGetVertexAttribfv;
#define glGetVertexAttribfv _ptrc_glGetVertexAttribfv
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC)(GLuint index, GLenum pname, GLint *params);
GLAPI PFNGLGETVERTEXATTRIBIVPROC _ptrc_glGetVertexAttribiv;
#define glGetVertexAttribiv _ptrc_glGetVertexAttribiv
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint index, GLenum pname, void **pointer);
GLAPI PFNGLGETVERTEXATTRIBPOINTERVPROC _ptrc_glGetVertexAttribPointerv;
#define glGetVertexAttribPointerv _ptrc_glGetVertexAttribPointerv
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPROC)(GLuint program);
GLAPI PFNGLISPROGRAMPROC _ptrc_glIsProgram;
#define glIsProgram _ptrc_glIsProgram
typedef GLboolean (APIENTRYP PFNGLISSHADERPROC)(GLuint shader);
GLAPI PFNGLISSHADERPROC _ptrc_glIsShader;
#define glIsShader _ptrc_glIsShader
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC)(GLuint program);
GLAPI PFNGLLINKPROGRAMPROC _ptrc_glLinkProgram;
#define glLinkProgram _ptrc_glLinkProgram
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
GLAPI PFNGLSHADERSOURCEPROC _ptrc_glShaderSource;
#define glShaderSource _ptrc_glShaderSource
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC)(GLuint program);
GLAPI PFNGLUSEPROGRAMPROC _ptrc_glUseProgram;
#define glUseProgram _ptrc_glUseProgram
typedef void (APIENTRYP PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
GLAPI PFNGLUNIFORM1FPROC _ptrc_glUniform1f;
#define glUniform1f _ptrc_glUniform1f
typedef void (APIENTRYP PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
GLAPI PFNGLUNIFORM2FPROC _ptrc_glUniform2f;
#define glUniform2f _ptrc_glUniform2f
typedef void (APIENTRYP PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GLAPI PFNGLUNIFORM3FPROC _ptrc_glUniform3f;
#define glUniform3f _ptrc_glUniform3f
typedef void (APIENTRYP PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GLAPI PFNGLUNIFORM4FPROC _ptrc_glUniform4f;
#define glUniform4f _ptrc_glUniform4f
typedef void (APIENTRYP PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
GLAPI PFNGLUNIFORM1IPROC _ptrc_glUniform1i;
#define glUniform1i _ptrc_glUniform1i
typedef void (APIENTRYP PFNGLUNIFORM2IPROC)(GLint location, GLint v0, GLint v1);
GLAPI PFNGLUNIFORM2IPROC _ptrc_glUniform2i;
#define glUniform2i _ptrc_glUniform2i
typedef void (APIENTRYP PFNGLUNIFORM3IPROC)(GLint location, GLint v0, GLint v1, GLint v2);
GLAPI PFNGLUNIFORM3IPROC _ptrc_glUniform3i;
#define glUniform3i _ptrc_glUniform3i
typedef void (APIENTRYP PFNGLUNIFORM4IPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GLAPI PFNGLUNIFORM4IPROC _ptrc_glUniform4i;
#define glUniform4i _ptrc_glUniform4i
typedef void (APIENTRYP PFNGLUNIFORM1FVPROC)(GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLUNIFORM1FVPROC _ptrc_glUniform1fv;
#define glUniform1fv _ptrc_glUniform1fv
typedef void (APIENTRYP PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLUNIFORM2FVPROC _ptrc_glUniform2fv;
#define glUniform2fv _ptrc_glUniform2fv
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLUNIFORM3FVPROC _ptrc_glUniform3fv;
#define glUniform3fv _ptrc_glUniform3fv
typedef void (APIENTRYP PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat *value);
GLAPI PFNGLUNIFORM4FVPROC _ptrc_glUniform4fv;
#define glUniform4fv _ptrc_glUniform4fv
typedef void (APIENTRYP PFNGLUNIFORM1IVPROC)(GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLUNIFORM1IVPROC _ptrc_glUniform1iv;
#define glUniform1iv _ptrc_glUniform1iv
typedef void (APIENTRYP PFNGLUNIFORM2IVPROC)(GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLUNIFORM2IVPROC _ptrc_glUniform2iv;
#define glUniform2iv _ptrc_glUniform2iv
typedef void (APIENTRYP PFNGLUNIFORM3IVPROC)(GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLUNIFORM3IVPROC _ptrc_glUniform3iv;
#define glUniform3iv _ptrc_glUniform3iv
typedef void (APIENTRYP PFNGLUNIFORM4IVPROC)(GLint location, GLsizei count, const GLint *value);
GLAPI PFNGLUNIFORM4IVPROC _ptrc_glUniform4iv;
#define glUniform4iv _ptrc_glUniform4iv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLUNIFORMMATRIX2FVPROC _ptrc_glUniformMatrix2fv;
#define glUniformMatrix2fv _ptrc_glUniformMatrix2fv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLUNIFORMMATRIX3FVPROC _ptrc_glUniformMatrix3fv;
#define glUniformMatrix3fv _ptrc_glUniformMatrix3fv
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
GLAPI PFNGLUNIFORMMATRIX4FVPROC _ptrc_glUniformMatrix4fv;
#define glUniformMatrix4fv _ptrc_glUniformMatrix4fv
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC)(GLuint program);
GLAPI PFNGLVALIDATEPROGRAMPROC _ptrc_glValidateProgram;
#define glValidateProgram _ptrc_glValidateProgram
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DPROC)(GLuint index, GLdouble x);
GLAPI PFNGLVERTEXATTRIB1DPROC _ptrc_glVertexAttrib1d;
#define glVertexAttrib1d _ptrc_glVertexAttrib1d
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIB1DVPROC _ptrc_glVertexAttrib1dv;
#define glVertexAttrib1dv _ptrc_glVertexAttrib1dv
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
GLAPI PFNGLVERTEXATTRIB1FPROC _ptrc_glVertexAttrib1f;
#define glVertexAttrib1f _ptrc_glVertexAttrib1f
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC)(GLuint index, const GLfloat *v);
GLAPI PFNGLVERTEXATTRIB1FVPROC _ptrc_glVertexAttrib1fv;
#define glVertexAttrib1fv _ptrc_glVertexAttrib1fv
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SPROC)(GLuint index, GLshort x);
GLAPI PFNGLVERTEXATTRIB1SPROC _ptrc_glVertexAttrib1s;
#define glVertexAttrib1s _ptrc_glVertexAttrib1s
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIB1SVPROC _ptrc_glVertexAttrib1sv;
#define glVertexAttrib1sv _ptrc_glVertexAttrib1sv
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DPROC)(GLuint index, GLdouble x, GLdouble y);
GLAPI PFNGLVERTEXATTRIB2DPROC _ptrc_glVertexAttrib2d;
#define glVertexAttrib2d _ptrc_glVertexAttrib2d
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIB2DVPROC _ptrc_glVertexAttrib2dv;
#define glVertexAttrib2dv _ptrc_glVertexAttrib2dv
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
GLAPI PFNGLVERTEXATTRIB2FPROC _ptrc_glVertexAttrib2f;
#define glVertexAttrib2f _ptrc_glVertexAttrib2f
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC)(GLuint index, const GLfloat *v);
GLAPI PFNGLVERTEXATTRIB2FVPROC _ptrc_glVertexAttrib2fv;
#define glVertexAttrib2fv _ptrc_glVertexAttrib2fv
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SPROC)(GLuint index, GLshort x, GLshort y);
GLAPI PFNGLVERTEXATTRIB2SPROC _ptrc_glVertexAttrib2s;
#define glVertexAttrib2s _ptrc_glVertexAttrib2s
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIB2SVPROC _ptrc_glVertexAttrib2sv;
#define glVertexAttrib2sv _ptrc_glVertexAttrib2sv
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
GLAPI PFNGLVERTEXATTRIB3DPROC _ptrc_glVertexAttrib3d;
#define glVertexAttrib3d _ptrc_glVertexAttrib3d
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIB3DVPROC _ptrc_glVertexAttrib3dv;
#define glVertexAttrib3dv _ptrc_glVertexAttrib3dv
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
GLAPI PFNGLVERTEXATTRIB3FPROC _ptrc_glVertexAttrib3f;
#define glVertexAttrib3f _ptrc_glVertexAttrib3f
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC)(GLuint index, const GLfloat *v);
GLAPI PFNGLVERTEXATTRIB3FVPROC _ptrc_glVertexAttrib3fv;
#define glVertexAttrib3fv _ptrc_glVertexAttrib3fv
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SPROC)(GLuint index, GLshort x, GLshort y, GLshort z);
GLAPI PFNGLVERTEXATTRIB3SPROC _ptrc_glVertexAttrib3s;
#define glVertexAttrib3s _ptrc_glVertexAttrib3s
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIB3SVPROC _ptrc_glVertexAttrib3sv;
#define glVertexAttrib3sv _ptrc_glVertexAttrib3sv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NBVPROC)(GLuint index, const GLbyte *v);
GLAPI PFNGLVERTEXATTRIB4NBVPROC _ptrc_glVertexAttrib4Nbv;
#define glVertexAttrib4Nbv _ptrc_glVertexAttrib4Nbv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NIVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIB4NIVPROC _ptrc_glVertexAttrib4Niv;
#define glVertexAttrib4Niv _ptrc_glVertexAttrib4Niv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NSVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIB4NSVPROC _ptrc_glVertexAttrib4Nsv;
#define glVertexAttrib4Nsv _ptrc_glVertexAttrib4Nsv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBPROC)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
GLAPI PFNGLVERTEXATTRIB4NUBPROC _ptrc_glVertexAttrib4Nub;
#define glVertexAttrib4Nub _ptrc_glVertexAttrib4Nub
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBVPROC)(GLuint index, const GLubyte *v);
GLAPI PFNGLVERTEXATTRIB4NUBVPROC _ptrc_glVertexAttrib4Nubv;
#define glVertexAttrib4Nubv _ptrc_glVertexAttrib4Nubv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIB4NUIVPROC _ptrc_glVertexAttrib4Nuiv;
#define glVertexAttrib4Nuiv _ptrc_glVertexAttrib4Nuiv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUSVPROC)(GLuint index, const GLushort *v);
GLAPI PFNGLVERTEXATTRIB4NUSVPROC _ptrc_glVertexAttrib4Nusv;
#define glVertexAttrib4Nusv _ptrc_glVertexAttrib4Nusv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4BVPROC)(GLuint index, const GLbyte *v);
GLAPI PFNGLVERTEXATTRIB4BVPROC _ptrc_glVertexAttrib4bv;
#define glVertexAttrib4bv _ptrc_glVertexAttrib4bv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI PFNGLVERTEXATTRIB4DPROC _ptrc_glVertexAttrib4d;
#define glVertexAttrib4d _ptrc_glVertexAttrib4d
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DVPROC)(GLuint index, const GLdouble *v);
GLAPI PFNGLVERTEXATTRIB4DVPROC _ptrc_glVertexAttrib4dv;
#define glVertexAttrib4dv _ptrc_glVertexAttrib4dv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLAPI PFNGLVERTEXATTRIB4FPROC _ptrc_glVertexAttrib4f;
#define glVertexAttrib4f _ptrc_glVertexAttrib4f
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC)(GLuint index, const GLfloat *v);
GLAPI PFNGLVERTEXATTRIB4FVPROC _ptrc_glVertexAttrib4fv;
#define glVertexAttrib4fv _ptrc_glVertexAttrib4fv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4IVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIB4IVPROC _ptrc_glVertexAttrib4iv;
#define glVertexAttrib4iv _ptrc_glVertexAttrib4iv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SPROC)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
GLAPI PFNGLVERTEXATTRIB4SPROC _ptrc_glVertexAttrib4s;
#define glVertexAttrib4s _ptrc_glVertexAttrib4s
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIB4SVPROC _ptrc_glVertexAttrib4sv;
#define glVertexAttrib4sv _ptrc_glVertexAttrib4sv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UBVPROC)(GLuint index, const GLubyte *v);
GLAPI PFNGLVERTEXATTRIB4UBVPROC _ptrc_glVertexAttrib4ubv;
#define glVertexAttrib4ubv _ptrc_glVertexAttrib4ubv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIB4UIVPROC _ptrc_glVertexAttrib4uiv;
#define glVertexAttrib4uiv _ptrc_glVertexAttrib4uiv
typedef void (APIENTRYP PFNGLVERTEXATTRIB4USVPROC)(GLuint index, const GLushort *v);
GLAPI PFNGLVERTEXATTRIB4USVPROC _ptrc_glVertexAttrib4usv;
#define glVertexAttrib4usv _ptrc_glVertexAttrib4usv
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
GLAPI PFNGLVERTEXATTRIBPOINTERPROC _ptrc_glVertexAttribPointer;
#define glVertexAttribPointer _ptrc_glVertexAttribPointer
