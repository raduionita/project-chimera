GLAPI int   OGL_VERSION_4_3;

typedef void (APIENTRYP PFNGLCLEARBUFFERDATAPROC)(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data);
GLAPI PFNGLCLEARBUFFERDATAPROC _ptrc_glClearBufferData;
#define glClearBufferData _ptrc_glClearBufferData
typedef void (APIENTRYP PFNGLCLEARBUFFERSUBDATAPROC)(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
GLAPI PFNGLCLEARBUFFERSUBDATAPROC _ptrc_glClearBufferSubData;
#define glClearBufferSubData _ptrc_glClearBufferSubData
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEPROC)(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
GLAPI PFNGLDISPATCHCOMPUTEPROC _ptrc_glDispatchCompute;
#define glDispatchCompute _ptrc_glDispatchCompute
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC)(GLintptr indirect);
GLAPI PFNGLDISPATCHCOMPUTEINDIRECTPROC _ptrc_glDispatchComputeIndirect;
#define glDispatchComputeIndirect _ptrc_glDispatchComputeIndirect
typedef void (APIENTRYP PFNGLCOPYIMAGESUBDATAPROC)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
GLAPI PFNGLCOPYIMAGESUBDATAPROC _ptrc_glCopyImageSubData;
#define glCopyImageSubData _ptrc_glCopyImageSubData
typedef void (APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
GLAPI PFNGLFRAMEBUFFERPARAMETERIPROC _ptrc_glFramebufferParameteri;
#define glFramebufferParameteri _ptrc_glFramebufferParameteri
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETFRAMEBUFFERPARAMETERIVPROC _ptrc_glGetFramebufferParameteriv;
#define glGetFramebufferParameteriv _ptrc_glGetFramebufferParameteriv
typedef void (APIENTRYP PFNGLGETINTERNALFORMATI64VPROC)(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params);
GLAPI PFNGLGETINTERNALFORMATI64VPROC _ptrc_glGetInternalformati64v;
#define glGetInternalformati64v _ptrc_glGetInternalformati64v
typedef void (APIENTRYP PFNGLINVALIDATETEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
GLAPI PFNGLINVALIDATETEXSUBIMAGEPROC _ptrc_glInvalidateTexSubImage;
#define glInvalidateTexSubImage _ptrc_glInvalidateTexSubImage
typedef void (APIENTRYP PFNGLINVALIDATETEXIMAGEPROC)(GLuint texture, GLint level);
GLAPI PFNGLINVALIDATETEXIMAGEPROC _ptrc_glInvalidateTexImage;
#define glInvalidateTexImage _ptrc_glInvalidateTexImage
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
GLAPI PFNGLINVALIDATEBUFFERSUBDATAPROC _ptrc_glInvalidateBufferSubData;
#define glInvalidateBufferSubData _ptrc_glInvalidateBufferSubData
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERDATAPROC)(GLuint buffer);
GLAPI PFNGLINVALIDATEBUFFERDATAPROC _ptrc_glInvalidateBufferData;
#define glInvalidateBufferData _ptrc_glInvalidateBufferData
typedef void (APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum *attachments);
GLAPI PFNGLINVALIDATEFRAMEBUFFERPROC _ptrc_glInvalidateFramebuffer;
#define glInvalidateFramebuffer _ptrc_glInvalidateFramebuffer
typedef void (APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLINVALIDATESUBFRAMEBUFFERPROC _ptrc_glInvalidateSubFramebuffer;
#define glInvalidateSubFramebuffer _ptrc_glInvalidateSubFramebuffer
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTPROC)(GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
GLAPI PFNGLMULTIDRAWARRAYSINDIRECTPROC _ptrc_glMultiDrawArraysIndirect;
#define glMultiDrawArraysIndirect _ptrc_glMultiDrawArraysIndirect
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTPROC _ptrc_glMultiDrawElementsIndirect;
#define glMultiDrawElementsIndirect _ptrc_glMultiDrawElementsIndirect
typedef void (APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC)(GLuint program, GLenum programInterface, GLenum pname, GLint *params);
GLAPI PFNGLGETPROGRAMINTERFACEIVPROC _ptrc_glGetProgramInterfaceiv;
#define glGetProgramInterfaceiv _ptrc_glGetProgramInterfaceiv
typedef GLuint (APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC)(GLuint program, GLenum programInterface, const GLchar *name);
GLAPI PFNGLGETPROGRAMRESOURCEINDEXPROC _ptrc_glGetProgramResourceIndex;
#define glGetProgramResourceIndex _ptrc_glGetProgramResourceIndex
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
GLAPI PFNGLGETPROGRAMRESOURCENAMEPROC _ptrc_glGetProgramResourceName;
#define glGetProgramResourceName _ptrc_glGetProgramResourceName
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params);
GLAPI PFNGLGETPROGRAMRESOURCEIVPROC _ptrc_glGetProgramResourceiv;
#define glGetProgramResourceiv _ptrc_glGetProgramResourceiv
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC)(GLuint program, GLenum programInterface, const GLchar *name);
GLAPI PFNGLGETPROGRAMRESOURCELOCATIONPROC _ptrc_glGetProgramResourceLocation;
#define glGetProgramResourceLocation _ptrc_glGetProgramResourceLocation
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)(GLuint program, GLenum programInterface, const GLchar *name);
GLAPI PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC _ptrc_glGetProgramResourceLocationIndex;
#define glGetProgramResourceLocationIndex _ptrc_glGetProgramResourceLocationIndex
typedef void (APIENTRYP PFNGLSHADERSTORAGEBLOCKBINDINGPROC)(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
GLAPI PFNGLSHADERSTORAGEBLOCKBINDINGPROC _ptrc_glShaderStorageBlockBinding;
#define glShaderStorageBlockBinding _ptrc_glShaderStorageBlockBinding
typedef void (APIENTRYP PFNGLTEXBUFFERRANGEPROC)(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
GLAPI PFNGLTEXBUFFERRANGEPROC _ptrc_glTexBufferRange;
#define glTexBufferRange _ptrc_glTexBufferRange
typedef void (APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
GLAPI PFNGLTEXSTORAGE2DMULTISAMPLEPROC _ptrc_glTexStorage2DMultisample;
#define glTexStorage2DMultisample _ptrc_glTexStorage2DMultisample
typedef void (APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
GLAPI PFNGLTEXSTORAGE3DMULTISAMPLEPROC _ptrc_glTexStorage3DMultisample;
#define glTexStorage3DMultisample _ptrc_glTexStorage3DMultisample
typedef void (APIENTRYP PFNGLTEXTUREVIEWPROC)(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
GLAPI PFNGLTEXTUREVIEWPROC _ptrc_glTextureView;
#define glTextureView _ptrc_glTextureView
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
GLAPI PFNGLBINDVERTEXBUFFERPROC _ptrc_glBindVertexBuffer;
#define glBindVertexBuffer _ptrc_glBindVertexBuffer
typedef void (APIENTRYP PFNGLVERTEXATTRIBFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
GLAPI PFNGLVERTEXATTRIBFORMATPROC _ptrc_glVertexAttribFormat;
#define glVertexAttribFormat _ptrc_glVertexAttribFormat
typedef void (APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
GLAPI PFNGLVERTEXATTRIBIFORMATPROC _ptrc_glVertexAttribIFormat;
#define glVertexAttribIFormat _ptrc_glVertexAttribIFormat
typedef void (APIENTRYP PFNGLVERTEXATTRIBLFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
GLAPI PFNGLVERTEXATTRIBLFORMATPROC _ptrc_glVertexAttribLFormat;
#define glVertexAttribLFormat _ptrc_glVertexAttribLFormat
typedef void (APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC)(GLuint attribindex, GLuint bindingindex);
GLAPI PFNGLVERTEXATTRIBBINDINGPROC _ptrc_glVertexAttribBinding;
#define glVertexAttribBinding _ptrc_glVertexAttribBinding
typedef void (APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC)(GLuint bindingindex, GLuint divisor);
GLAPI PFNGLVERTEXBINDINGDIVISORPROC _ptrc_glVertexBindingDivisor;
#define glVertexBindingDivisor _ptrc_glVertexBindingDivisor
typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
GLAPI PFNGLDEBUGMESSAGECONTROLPROC _ptrc_glDebugMessageControl;
#define glDebugMessageControl _ptrc_glDebugMessageControl
typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
GLAPI PFNGLDEBUGMESSAGEINSERTPROC _ptrc_glDebugMessageInsert;
#define glDebugMessageInsert _ptrc_glDebugMessageInsert
typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC callback, const void *userParam);
GLAPI PFNGLDEBUGMESSAGECALLBACKPROC _ptrc_glDebugMessageCallback;
#define glDebugMessageCallback _ptrc_glDebugMessageCallback
typedef GLuint (APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC)(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
GLAPI PFNGLGETDEBUGMESSAGELOGPROC _ptrc_glGetDebugMessageLog;
#define glGetDebugMessageLog _ptrc_glGetDebugMessageLog
typedef void (APIENTRYP PFNGLPUSHDEBUGGROUPPROC)(GLenum source, GLuint id, GLsizei length, const GLchar *message);
GLAPI PFNGLPUSHDEBUGGROUPPROC _ptrc_glPushDebugGroup;
#define glPushDebugGroup _ptrc_glPushDebugGroup
typedef void (APIENTRYP PFNGLPOPDEBUGGROUPPROC)(void);
GLAPI PFNGLPOPDEBUGGROUPPROC _ptrc_glPopDebugGroup;
#define glPopDebugGroup _ptrc_glPopDebugGroup
typedef void (APIENTRYP PFNGLOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
GLAPI PFNGLOBJECTLABELPROC _ptrc_glObjectLabel;
#define glObjectLabel _ptrc_glObjectLabel
typedef void (APIENTRYP PFNGLGETOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
GLAPI PFNGLGETOBJECTLABELPROC _ptrc_glGetObjectLabel;
#define glGetObjectLabel _ptrc_glGetObjectLabel
typedef void (APIENTRYP PFNGLOBJECTPTRLABELPROC)(const void *ptr, GLsizei length, const GLchar *label);
GLAPI PFNGLOBJECTPTRLABELPROC _ptrc_glObjectPtrLabel;
#define glObjectPtrLabel _ptrc_glObjectPtrLabel
typedef void (APIENTRYP PFNGLGETOBJECTPTRLABELPROC)(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
GLAPI PFNGLGETOBJECTPTRLABELPROC _ptrc_glGetObjectPtrLabel;
#define glGetObjectPtrLabel _ptrc_glGetObjectPtrLabel
typedef void (APIENTRYP PFNGLGETPOINTERVPROC)(GLenum pname, void **params);
GLAPI PFNGLGETPOINTERVPROC _ptrc_glGetPointerv;
#define glGetPointerv _ptrc_glGetPointerv
