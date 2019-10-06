GLAPI int   OGL_VERSION_3_0;

typedef void (APIENTRYP PFNGLCOLORMASKIPROC)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GLAPI PFNGLCOLORMASKIPROC glColorMaski;

typedef void (APIENTRYP PFNGLGETBOOLEANI_VPROC)(GLenum target, GLuint index, GLboolean *data);
GLAPI PFNGLGETBOOLEANI_VPROC glGetBooleani_v;

typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC)(GLenum target, GLuint index, GLint *data);
GLAPI PFNGLGETINTEGERI_VPROC glGetIntegeri_v;

typedef void (APIENTRYP PFNGLENABLEIPROC)(GLenum target, GLuint index);
GLAPI PFNGLENABLEIPROC glEnablei;

typedef void (APIENTRYP PFNGLDISABLEIPROC)(GLenum target, GLuint index);
GLAPI PFNGLDISABLEIPROC glDisablei;

typedef GLboolean (APIENTRYP PFNGLISENABLEDIPROC)(GLenum target, GLuint index);
GLAPI PFNGLISENABLEDIPROC glIsEnabledi;

typedef void (APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum primitiveMode);
GLAPI PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback;

typedef void (APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC)(void);
GLAPI PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback;

typedef void (APIENTRYP PFNGLBINDBUFFERRANGEPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
GLAPI PFNGLBINDBUFFERRANGEPROC glBindBufferRange;

typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
GLAPI PFNGLBINDBUFFERBASEPROC glBindBufferBase;

typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
GLAPI PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings;

typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
GLAPI PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying;

typedef void (APIENTRYP PFNGLCLAMPCOLORPROC)(GLenum target, GLenum clamp);
GLAPI PFNGLCLAMPCOLORPROC glClampColor;

typedef void (APIENTRYP PFNGLBEGINCONDITIONALRENDERPROC)(GLuint id, GLenum mode);
GLAPI PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender;

typedef void (APIENTRYP PFNGLENDCONDITIONALRENDERPROC)(void);
GLAPI PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender;

typedef void (APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
GLAPI PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;

typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC)(GLuint index, GLenum pname, GLint *params);
GLAPI PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv;

typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC)(GLuint index, GLenum pname, GLuint *params);
GLAPI PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IPROC)(GLuint index, GLint x);
GLAPI PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IPROC)(GLuint index, GLint x, GLint y);
GLAPI PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IPROC)(GLuint index, GLint x, GLint y, GLint z);
GLAPI PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IPROC)(GLuint index, GLint x, GLint y, GLint z, GLint w);
GLAPI PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIPROC)(GLuint index, GLuint x);
GLAPI PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIPROC)(GLuint index, GLuint x, GLuint y);
GLAPI PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z);
GLAPI PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
GLAPI PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI4BVPROC)(GLuint index, const GLbyte *v);
GLAPI PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI4SVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UBVPROC)(GLuint index, const GLubyte *v);
GLAPI PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBI4USVPROC)(GLuint index, const GLushort *v);
GLAPI PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv;

typedef void (APIENTRYP PFNGLGETUNIFORMUIVPROC)(GLuint program, GLint location, GLuint *params);
GLAPI PFNGLGETUNIFORMUIVPROC glGetUniformuiv;

typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONPROC)(GLuint program, GLuint color, const GLchar *name);
GLAPI PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation;

typedef GLint (APIENTRYP PFNGLGETFRAGDATALOCATIONPROC)(GLuint program, const GLchar *name);
GLAPI PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation;

typedef void (APIENTRYP PFNGLUNIFORM1UIPROC)(GLint location, GLuint v0);
GLAPI PFNGLUNIFORM1UIPROC glUniform1ui;

typedef void (APIENTRYP PFNGLUNIFORM2UIPROC)(GLint location, GLuint v0, GLuint v1);
GLAPI PFNGLUNIFORM2UIPROC glUniform2ui;

typedef void (APIENTRYP PFNGLUNIFORM3UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2);
GLAPI PFNGLUNIFORM3UIPROC glUniform3ui;

typedef void (APIENTRYP PFNGLUNIFORM4UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GLAPI PFNGLUNIFORM4UIPROC glUniform4ui;

typedef void (APIENTRYP PFNGLUNIFORM1UIVPROC)(GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLUNIFORM1UIVPROC glUniform1uiv;

typedef void (APIENTRYP PFNGLUNIFORM2UIVPROC)(GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLUNIFORM2UIVPROC glUniform2uiv;

typedef void (APIENTRYP PFNGLUNIFORM3UIVPROC)(GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLUNIFORM3UIVPROC glUniform3uiv;

typedef void (APIENTRYP PFNGLUNIFORM4UIVPROC)(GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLUNIFORM4UIVPROC glUniform4uiv;

typedef void (APIENTRYP PFNGLTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, const GLint *params);
GLAPI PFNGLTEXPARAMETERIIVPROC glTexParameterIiv;

typedef void (APIENTRYP PFNGLTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, const GLuint *params);
GLAPI PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv;

typedef void (APIENTRYP PFNGLGETTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv;

typedef void (APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, GLuint *params);
GLAPI PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv;

typedef void (APIENTRYP PFNGLCLEARBUFFERIVPROC)(GLenum buffer, GLint drawbuffer, const GLint *value);
GLAPI PFNGLCLEARBUFFERIVPROC glClearBufferiv;

typedef void (APIENTRYP PFNGLCLEARBUFFERUIVPROC)(GLenum buffer, GLint drawbuffer, const GLuint *value);
GLAPI PFNGLCLEARBUFFERUIVPROC glClearBufferuiv;

typedef void (APIENTRYP PFNGLCLEARBUFFERFVPROC)(GLenum buffer, GLint drawbuffer, const GLfloat *value);
GLAPI PFNGLCLEARBUFFERFVPROC glClearBufferfv;

typedef void (APIENTRYP PFNGLCLEARBUFFERFIPROC)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
GLAPI PFNGLCLEARBUFFERFIPROC glClearBufferfi;

typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGIPROC)(GLenum name, GLuint index);
GLAPI PFNGLGETSTRINGIPROC glGetStringi;

typedef GLboolean (APIENTRYP PFNGLISRENDERBUFFERPROC)(GLuint renderbuffer);
GLAPI PFNGLISRENDERBUFFERPROC glIsRenderbuffer;

typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC)(GLenum target, GLuint renderbuffer);
GLAPI PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;

typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSPROC)(GLsizei n, const GLuint *renderbuffers);
GLAPI PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;

typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC)(GLsizei n, GLuint *renderbuffers);
GLAPI PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;

typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GLAPI PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;

typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv;

typedef GLboolean (APIENTRYP PFNGLISFRAMEBUFFERPROC)(GLuint framebuffer);
GLAPI PFNGLISFRAMEBUFFERPROC glIsFramebuffer;

typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
GLAPI PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;

typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei n, const GLuint *framebuffers);
GLAPI PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;

typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC)(GLsizei n, GLuint *framebuffers);
GLAPI PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;

typedef GLenum (APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum target);
GLAPI PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;

typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE1DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GLAPI PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D;

typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GLAPI PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;

typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
GLAPI PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D;

typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GLAPI PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;

typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum target, GLenum attachment, GLenum pname, GLint *params);
GLAPI PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;

typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC)(GLenum target);
GLAPI PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

typedef void (APIENTRYP PFNGLBLITFRAMEBUFFERPROC)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
GLAPI PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;

typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GLAPI PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample;

typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
GLAPI PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer;

typedef void * (APIENTRYP PFNGLMAPBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
GLAPI PFNGLMAPBUFFERRANGEPROC glMapBufferRange;

typedef void (APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length);
GLAPI PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange;

typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC)(GLuint array);
GLAPI PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);
GLAPI PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
GLAPI PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

typedef GLboolean (APIENTRYP PFNGLISVERTEXARRAYPROC)(GLuint array);
GLAPI PFNGLISVERTEXARRAYPROC glIsVertexArray;

