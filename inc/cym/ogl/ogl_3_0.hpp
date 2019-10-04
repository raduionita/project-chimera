GLAPI int   OGL_VERSION_3_0;

typedef void (APIENTRYP PFNGLCOLORMASKIPROC)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GLAPI PFNGLCOLORMASKIPROC _ptrc_glColorMaski;
#define glColorMaski _ptrc_glColorMaski
typedef void (APIENTRYP PFNGLGETBOOLEANI_VPROC)(GLenum target, GLuint index, GLboolean *data);
GLAPI PFNGLGETBOOLEANI_VPROC _ptrc_glGetBooleani_v;
#define glGetBooleani_v _ptrc_glGetBooleani_v
typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC)(GLenum target, GLuint index, GLint *data);
GLAPI PFNGLGETINTEGERI_VPROC _ptrc_glGetIntegeri_v;
#define glGetIntegeri_v _ptrc_glGetIntegeri_v
typedef void (APIENTRYP PFNGLENABLEIPROC)(GLenum target, GLuint index);
GLAPI PFNGLENABLEIPROC _ptrc_glEnablei;
#define glEnablei _ptrc_glEnablei
typedef void (APIENTRYP PFNGLDISABLEIPROC)(GLenum target, GLuint index);
GLAPI PFNGLDISABLEIPROC _ptrc_glDisablei;
#define glDisablei _ptrc_glDisablei
typedef GLboolean (APIENTRYP PFNGLISENABLEDIPROC)(GLenum target, GLuint index);
GLAPI PFNGLISENABLEDIPROC _ptrc_glIsEnabledi;
#define glIsEnabledi _ptrc_glIsEnabledi
typedef void (APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum primitiveMode);
GLAPI PFNGLBEGINTRANSFORMFEEDBACKPROC _ptrc_glBeginTransformFeedback;
#define glBeginTransformFeedback _ptrc_glBeginTransformFeedback
typedef void (APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC)(void);
GLAPI PFNGLENDTRANSFORMFEEDBACKPROC _ptrc_glEndTransformFeedback;
#define glEndTransformFeedback _ptrc_glEndTransformFeedback
typedef void (APIENTRYP PFNGLBINDBUFFERRANGEPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
GLAPI PFNGLBINDBUFFERRANGEPROC _ptrc_glBindBufferRange;
#define glBindBufferRange _ptrc_glBindBufferRange
typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
GLAPI PFNGLBINDBUFFERBASEPROC _ptrc_glBindBufferBase;
#define glBindBufferBase _ptrc_glBindBufferBase
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
GLAPI PFNGLTRANSFORMFEEDBACKVARYINGSPROC _ptrc_glTransformFeedbackVaryings;
#define glTransformFeedbackVaryings _ptrc_glTransformFeedbackVaryings
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
GLAPI PFNGLGETTRANSFORMFEEDBACKVARYINGPROC _ptrc_glGetTransformFeedbackVarying;
#define glGetTransformFeedbackVarying _ptrc_glGetTransformFeedbackVarying
typedef void (APIENTRYP PFNGLCLAMPCOLORPROC)(GLenum target, GLenum clamp);
GLAPI PFNGLCLAMPCOLORPROC _ptrc_glClampColor;
#define glClampColor _ptrc_glClampColor
typedef void (APIENTRYP PFNGLBEGINCONDITIONALRENDERPROC)(GLuint id, GLenum mode);
GLAPI PFNGLBEGINCONDITIONALRENDERPROC _ptrc_glBeginConditionalRender;
#define glBeginConditionalRender _ptrc_glBeginConditionalRender
typedef void (APIENTRYP PFNGLENDCONDITIONALRENDERPROC)(void);
GLAPI PFNGLENDCONDITIONALRENDERPROC _ptrc_glEndConditionalRender;
#define glEndConditionalRender _ptrc_glEndConditionalRender
typedef void (APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
GLAPI PFNGLVERTEXATTRIBIPOINTERPROC _ptrc_glVertexAttribIPointer;
#define glVertexAttribIPointer _ptrc_glVertexAttribIPointer
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC)(GLuint index, GLenum pname, GLint *params);
GLAPI PFNGLGETVERTEXATTRIBIIVPROC _ptrc_glGetVertexAttribIiv;
#define glGetVertexAttribIiv _ptrc_glGetVertexAttribIiv
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC)(GLuint index, GLenum pname, GLuint *params);
GLAPI PFNGLGETVERTEXATTRIBIUIVPROC _ptrc_glGetVertexAttribIuiv;
#define glGetVertexAttribIuiv _ptrc_glGetVertexAttribIuiv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IPROC)(GLuint index, GLint x);
GLAPI PFNGLVERTEXATTRIBI1IPROC _ptrc_glVertexAttribI1i;
#define glVertexAttribI1i _ptrc_glVertexAttribI1i
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IPROC)(GLuint index, GLint x, GLint y);
GLAPI PFNGLVERTEXATTRIBI2IPROC _ptrc_glVertexAttribI2i;
#define glVertexAttribI2i _ptrc_glVertexAttribI2i
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IPROC)(GLuint index, GLint x, GLint y, GLint z);
GLAPI PFNGLVERTEXATTRIBI3IPROC _ptrc_glVertexAttribI3i;
#define glVertexAttribI3i _ptrc_glVertexAttribI3i
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IPROC)(GLuint index, GLint x, GLint y, GLint z, GLint w);
GLAPI PFNGLVERTEXATTRIBI4IPROC _ptrc_glVertexAttribI4i;
#define glVertexAttribI4i _ptrc_glVertexAttribI4i
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIPROC)(GLuint index, GLuint x);
GLAPI PFNGLVERTEXATTRIBI1UIPROC _ptrc_glVertexAttribI1ui;
#define glVertexAttribI1ui _ptrc_glVertexAttribI1ui
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIPROC)(GLuint index, GLuint x, GLuint y);
GLAPI PFNGLVERTEXATTRIBI2UIPROC _ptrc_glVertexAttribI2ui;
#define glVertexAttribI2ui _ptrc_glVertexAttribI2ui
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z);
GLAPI PFNGLVERTEXATTRIBI3UIPROC _ptrc_glVertexAttribI3ui;
#define glVertexAttribI3ui _ptrc_glVertexAttribI3ui
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
GLAPI PFNGLVERTEXATTRIBI4UIPROC _ptrc_glVertexAttribI4ui;
#define glVertexAttribI4ui _ptrc_glVertexAttribI4ui
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIBI1IVPROC _ptrc_glVertexAttribI1iv;
#define glVertexAttribI1iv _ptrc_glVertexAttribI1iv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIBI2IVPROC _ptrc_glVertexAttribI2iv;
#define glVertexAttribI2iv _ptrc_glVertexAttribI2iv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIBI3IVPROC _ptrc_glVertexAttribI3iv;
#define glVertexAttribI3iv _ptrc_glVertexAttribI3iv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IVPROC)(GLuint index, const GLint *v);
GLAPI PFNGLVERTEXATTRIBI4IVPROC _ptrc_glVertexAttribI4iv;
#define glVertexAttribI4iv _ptrc_glVertexAttribI4iv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIBI1UIVPROC _ptrc_glVertexAttribI1uiv;
#define glVertexAttribI1uiv _ptrc_glVertexAttribI1uiv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIBI2UIVPROC _ptrc_glVertexAttribI2uiv;
#define glVertexAttribI2uiv _ptrc_glVertexAttribI2uiv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIBI3UIVPROC _ptrc_glVertexAttribI3uiv;
#define glVertexAttribI3uiv _ptrc_glVertexAttribI3uiv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC)(GLuint index, const GLuint *v);
GLAPI PFNGLVERTEXATTRIBI4UIVPROC _ptrc_glVertexAttribI4uiv;
#define glVertexAttribI4uiv _ptrc_glVertexAttribI4uiv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4BVPROC)(GLuint index, const GLbyte *v);
GLAPI PFNGLVERTEXATTRIBI4BVPROC _ptrc_glVertexAttribI4bv;
#define glVertexAttribI4bv _ptrc_glVertexAttribI4bv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4SVPROC)(GLuint index, const GLshort *v);
GLAPI PFNGLVERTEXATTRIBI4SVPROC _ptrc_glVertexAttribI4sv;
#define glVertexAttribI4sv _ptrc_glVertexAttribI4sv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UBVPROC)(GLuint index, const GLubyte *v);
GLAPI PFNGLVERTEXATTRIBI4UBVPROC _ptrc_glVertexAttribI4ubv;
#define glVertexAttribI4ubv _ptrc_glVertexAttribI4ubv
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4USVPROC)(GLuint index, const GLushort *v);
GLAPI PFNGLVERTEXATTRIBI4USVPROC _ptrc_glVertexAttribI4usv;
#define glVertexAttribI4usv _ptrc_glVertexAttribI4usv
typedef void (APIENTRYP PFNGLGETUNIFORMUIVPROC)(GLuint program, GLint location, GLuint *params);
GLAPI PFNGLGETUNIFORMUIVPROC _ptrc_glGetUniformuiv;
#define glGetUniformuiv _ptrc_glGetUniformuiv
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONPROC)(GLuint program, GLuint color, const GLchar *name);
GLAPI PFNGLBINDFRAGDATALOCATIONPROC _ptrc_glBindFragDataLocation;
#define glBindFragDataLocation _ptrc_glBindFragDataLocation
typedef GLint (APIENTRYP PFNGLGETFRAGDATALOCATIONPROC)(GLuint program, const GLchar *name);
GLAPI PFNGLGETFRAGDATALOCATIONPROC _ptrc_glGetFragDataLocation;
#define glGetFragDataLocation _ptrc_glGetFragDataLocation
typedef void (APIENTRYP PFNGLUNIFORM1UIPROC)(GLint location, GLuint v0);
GLAPI PFNGLUNIFORM1UIPROC _ptrc_glUniform1ui;
#define glUniform1ui _ptrc_glUniform1ui
typedef void (APIENTRYP PFNGLUNIFORM2UIPROC)(GLint location, GLuint v0, GLuint v1);
GLAPI PFNGLUNIFORM2UIPROC _ptrc_glUniform2ui;
#define glUniform2ui _ptrc_glUniform2ui
typedef void (APIENTRYP PFNGLUNIFORM3UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2);
GLAPI PFNGLUNIFORM3UIPROC _ptrc_glUniform3ui;
#define glUniform3ui _ptrc_glUniform3ui
typedef void (APIENTRYP PFNGLUNIFORM4UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GLAPI PFNGLUNIFORM4UIPROC _ptrc_glUniform4ui;
#define glUniform4ui _ptrc_glUniform4ui
typedef void (APIENTRYP PFNGLUNIFORM1UIVPROC)(GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLUNIFORM1UIVPROC _ptrc_glUniform1uiv;
#define glUniform1uiv _ptrc_glUniform1uiv
typedef void (APIENTRYP PFNGLUNIFORM2UIVPROC)(GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLUNIFORM2UIVPROC _ptrc_glUniform2uiv;
#define glUniform2uiv _ptrc_glUniform2uiv
typedef void (APIENTRYP PFNGLUNIFORM3UIVPROC)(GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLUNIFORM3UIVPROC _ptrc_glUniform3uiv;
#define glUniform3uiv _ptrc_glUniform3uiv
typedef void (APIENTRYP PFNGLUNIFORM4UIVPROC)(GLint location, GLsizei count, const GLuint *value);
GLAPI PFNGLUNIFORM4UIVPROC _ptrc_glUniform4uiv;
#define glUniform4uiv _ptrc_glUniform4uiv
typedef void (APIENTRYP PFNGLTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, const GLint *params);
GLAPI PFNGLTEXPARAMETERIIVPROC _ptrc_glTexParameterIiv;
#define glTexParameterIiv _ptrc_glTexParameterIiv
typedef void (APIENTRYP PFNGLTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, const GLuint *params);
GLAPI PFNGLTEXPARAMETERIUIVPROC _ptrc_glTexParameterIuiv;
#define glTexParameterIuiv _ptrc_glTexParameterIuiv
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETTEXPARAMETERIIVPROC _ptrc_glGetTexParameterIiv;
#define glGetTexParameterIiv _ptrc_glGetTexParameterIiv
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, GLuint *params);
GLAPI PFNGLGETTEXPARAMETERIUIVPROC _ptrc_glGetTexParameterIuiv;
#define glGetTexParameterIuiv _ptrc_glGetTexParameterIuiv
typedef void (APIENTRYP PFNGLCLEARBUFFERIVPROC)(GLenum buffer, GLint drawbuffer, const GLint *value);
GLAPI PFNGLCLEARBUFFERIVPROC _ptrc_glClearBufferiv;
#define glClearBufferiv _ptrc_glClearBufferiv
typedef void (APIENTRYP PFNGLCLEARBUFFERUIVPROC)(GLenum buffer, GLint drawbuffer, const GLuint *value);
GLAPI PFNGLCLEARBUFFERUIVPROC _ptrc_glClearBufferuiv;
#define glClearBufferuiv _ptrc_glClearBufferuiv
typedef void (APIENTRYP PFNGLCLEARBUFFERFVPROC)(GLenum buffer, GLint drawbuffer, const GLfloat *value);
GLAPI PFNGLCLEARBUFFERFVPROC _ptrc_glClearBufferfv;
#define glClearBufferfv _ptrc_glClearBufferfv
typedef void (APIENTRYP PFNGLCLEARBUFFERFIPROC)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
GLAPI PFNGLCLEARBUFFERFIPROC _ptrc_glClearBufferfi;
#define glClearBufferfi _ptrc_glClearBufferfi
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGIPROC)(GLenum name, GLuint index);
GLAPI PFNGLGETSTRINGIPROC _ptrc_glGetStringi;
#define glGetStringi _ptrc_glGetStringi
typedef GLboolean (APIENTRYP PFNGLISRENDERBUFFERPROC)(GLuint renderbuffer);
GLAPI PFNGLISRENDERBUFFERPROC _ptrc_glIsRenderbuffer;
#define glIsRenderbuffer _ptrc_glIsRenderbuffer
typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC)(GLenum target, GLuint renderbuffer);
GLAPI PFNGLBINDRENDERBUFFERPROC _ptrc_glBindRenderbuffer;
#define glBindRenderbuffer _ptrc_glBindRenderbuffer
typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSPROC)(GLsizei n, const GLuint *renderbuffers);
GLAPI PFNGLDELETERENDERBUFFERSPROC _ptrc_glDeleteRenderbuffers;
#define glDeleteRenderbuffers _ptrc_glDeleteRenderbuffers
typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC)(GLsizei n, GLuint *renderbuffers);
GLAPI PFNGLGENRENDERBUFFERSPROC _ptrc_glGenRenderbuffers;
#define glGenRenderbuffers _ptrc_glGenRenderbuffers
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GLAPI PFNGLRENDERBUFFERSTORAGEPROC _ptrc_glRenderbufferStorage;
#define glRenderbufferStorage _ptrc_glRenderbufferStorage
typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETRENDERBUFFERPARAMETERIVPROC _ptrc_glGetRenderbufferParameteriv;
#define glGetRenderbufferParameteriv _ptrc_glGetRenderbufferParameteriv
typedef GLboolean (APIENTRYP PFNGLISFRAMEBUFFERPROC)(GLuint framebuffer);
GLAPI PFNGLISFRAMEBUFFERPROC _ptrc_glIsFramebuffer;
#define glIsFramebuffer _ptrc_glIsFramebuffer
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
GLAPI PFNGLBINDFRAMEBUFFERPROC _ptrc_glBindFramebuffer;
#define glBindFramebuffer _ptrc_glBindFramebuffer
typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei n, const GLuint *framebuffers);
GLAPI PFNGLDELETEFRAMEBUFFERSPROC _ptrc_glDeleteFramebuffers;
#define glDeleteFramebuffers _ptrc_glDeleteFramebuffers
typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC)(GLsizei n, GLuint *framebuffers);
GLAPI PFNGLGENFRAMEBUFFERSPROC _ptrc_glGenFramebuffers;
#define glGenFramebuffers _ptrc_glGenFramebuffers
typedef GLenum (APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum target);
GLAPI PFNGLCHECKFRAMEBUFFERSTATUSPROC _ptrc_glCheckFramebufferStatus;
#define glCheckFramebufferStatus _ptrc_glCheckFramebufferStatus
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE1DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GLAPI PFNGLFRAMEBUFFERTEXTURE1DPROC _ptrc_glFramebufferTexture1D;
#define glFramebufferTexture1D _ptrc_glFramebufferTexture1D
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GLAPI PFNGLFRAMEBUFFERTEXTURE2DPROC _ptrc_glFramebufferTexture2D;
#define glFramebufferTexture2D _ptrc_glFramebufferTexture2D
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
GLAPI PFNGLFRAMEBUFFERTEXTURE3DPROC _ptrc_glFramebufferTexture3D;
#define glFramebufferTexture3D _ptrc_glFramebufferTexture3D
typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GLAPI PFNGLFRAMEBUFFERRENDERBUFFERPROC _ptrc_glFramebufferRenderbuffer;
#define glFramebufferRenderbuffer _ptrc_glFramebufferRenderbuffer
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum target, GLenum attachment, GLenum pname, GLint *params);
GLAPI PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC _ptrc_glGetFramebufferAttachmentParameteriv;
#define glGetFramebufferAttachmentParameteriv _ptrc_glGetFramebufferAttachmentParameteriv
typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC)(GLenum target);
GLAPI PFNGLGENERATEMIPMAPPROC _ptrc_glGenerateMipmap;
#define glGenerateMipmap _ptrc_glGenerateMipmap
typedef void (APIENTRYP PFNGLBLITFRAMEBUFFERPROC)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
GLAPI PFNGLBLITFRAMEBUFFERPROC _ptrc_glBlitFramebuffer;
#define glBlitFramebuffer _ptrc_glBlitFramebuffer
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GLAPI PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC _ptrc_glRenderbufferStorageMultisample;
#define glRenderbufferStorageMultisample _ptrc_glRenderbufferStorageMultisample
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
GLAPI PFNGLFRAMEBUFFERTEXTURELAYERPROC _ptrc_glFramebufferTextureLayer;
#define glFramebufferTextureLayer _ptrc_glFramebufferTextureLayer
typedef void * (APIENTRYP PFNGLMAPBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
GLAPI PFNGLMAPBUFFERRANGEPROC _ptrc_glMapBufferRange;
#define glMapBufferRange _ptrc_glMapBufferRange
typedef void (APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length);
GLAPI PFNGLFLUSHMAPPEDBUFFERRANGEPROC _ptrc_glFlushMappedBufferRange;
#define glFlushMappedBufferRange _ptrc_glFlushMappedBufferRange
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC)(GLuint array);
GLAPI PFNGLBINDVERTEXARRAYPROC _ptrc_glBindVertexArray;
#define glBindVertexArray _ptrc_glBindVertexArray
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);
GLAPI PFNGLDELETEVERTEXARRAYSPROC _ptrc_glDeleteVertexArrays;
#define glDeleteVertexArrays _ptrc_glDeleteVertexArrays
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
GLAPI PFNGLGENVERTEXARRAYSPROC _ptrc_glGenVertexArrays;
#define glGenVertexArrays _ptrc_glGenVertexArrays
typedef GLboolean (APIENTRYP PFNGLISVERTEXARRAYPROC)(GLuint array);
GLAPI PFNGLISVERTEXARRAYPROC _ptrc_glIsVertexArray;
#define glIsVertexArray _ptrc_glIsVertexArray
