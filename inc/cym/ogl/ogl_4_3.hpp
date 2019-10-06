GLAPI int   OGL_VERSION_4_3;

typedef void (APIENTRYP PFNGLCLEARBUFFERDATAPROC)(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data);
GLAPI PFNGLCLEARBUFFERDATAPROC glClearBufferData;

typedef void (APIENTRYP PFNGLCLEARBUFFERSUBDATAPROC)(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
GLAPI PFNGLCLEARBUFFERSUBDATAPROC glClearBufferSubData;

typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEPROC)(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
GLAPI PFNGLDISPATCHCOMPUTEPROC glDispatchCompute;

typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC)(GLintptr indirect);
GLAPI PFNGLDISPATCHCOMPUTEINDIRECTPROC glDispatchComputeIndirect;

typedef void (APIENTRYP PFNGLCOPYIMAGESUBDATAPROC)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
GLAPI PFNGLCOPYIMAGESUBDATAPROC glCopyImageSubData;

typedef void (APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
GLAPI PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteri;

typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
GLAPI PFNGLGETFRAMEBUFFERPARAMETERIVPROC glGetFramebufferParameteriv;

typedef void (APIENTRYP PFNGLGETINTERNALFORMATI64VPROC)(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params);
GLAPI PFNGLGETINTERNALFORMATI64VPROC glGetInternalformati64v;

typedef void (APIENTRYP PFNGLINVALIDATETEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
GLAPI PFNGLINVALIDATETEXSUBIMAGEPROC glInvalidateTexSubImage;

typedef void (APIENTRYP PFNGLINVALIDATETEXIMAGEPROC)(GLuint texture, GLint level);
GLAPI PFNGLINVALIDATETEXIMAGEPROC glInvalidateTexImage;

typedef void (APIENTRYP PFNGLINVALIDATEBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
GLAPI PFNGLINVALIDATEBUFFERSUBDATAPROC glInvalidateBufferSubData;

typedef void (APIENTRYP PFNGLINVALIDATEBUFFERDATAPROC)(GLuint buffer);
GLAPI PFNGLINVALIDATEBUFFERDATAPROC glInvalidateBufferData;

typedef void (APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum *attachments);
GLAPI PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer;

typedef void (APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer;

typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTPROC)(GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
GLAPI PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirect;

typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirect;

typedef void (APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC)(GLuint program, GLenum programInterface, GLenum pname, GLint *params);
GLAPI PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceiv;

typedef GLuint (APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC)(GLuint program, GLenum programInterface, const GLchar *name);
GLAPI PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndex;

typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
GLAPI PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName;

typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params);
GLAPI PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv;

typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC)(GLuint program, GLenum programInterface, const GLchar *name);
GLAPI PFNGLGETPROGRAMRESOURCELOCATIONPROC glGetProgramResourceLocation;

typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)(GLuint program, GLenum programInterface, const GLchar *name);
GLAPI PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glGetProgramResourceLocationIndex;

typedef void (APIENTRYP PFNGLSHADERSTORAGEBLOCKBINDINGPROC)(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
GLAPI PFNGLSHADERSTORAGEBLOCKBINDINGPROC glShaderStorageBlockBinding;

typedef void (APIENTRYP PFNGLTEXBUFFERRANGEPROC)(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
GLAPI PFNGLTEXBUFFERRANGEPROC glTexBufferRange;

typedef void (APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
GLAPI PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisample;

typedef void (APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
GLAPI PFNGLTEXSTORAGE3DMULTISAMPLEPROC glTexStorage3DMultisample;

typedef void (APIENTRYP PFNGLTEXTUREVIEWPROC)(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
GLAPI PFNGLTEXTUREVIEWPROC glTextureView;

typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
GLAPI PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer;

typedef void (APIENTRYP PFNGLVERTEXATTRIBFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
GLAPI PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormat;

typedef void (APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
GLAPI PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormat;

typedef void (APIENTRYP PFNGLVERTEXATTRIBLFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
GLAPI PFNGLVERTEXATTRIBLFORMATPROC glVertexAttribLFormat;

typedef void (APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC)(GLuint attribindex, GLuint bindingindex);
GLAPI PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBinding;

typedef void (APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC)(GLuint bindingindex, GLuint divisor);
GLAPI PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisor;

typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
GLAPI PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl;

typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
GLAPI PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsert;

typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC callback, const void *userParam);
GLAPI PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback;

typedef GLuint (APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC)(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
GLAPI PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLog;

typedef void (APIENTRYP PFNGLPUSHDEBUGGROUPPROC)(GLenum source, GLuint id, GLsizei length, const GLchar *message);
GLAPI PFNGLPUSHDEBUGGROUPPROC glPushDebugGroup;

typedef void (APIENTRYP PFNGLPOPDEBUGGROUPPROC)(void);
GLAPI PFNGLPOPDEBUGGROUPPROC glPopDebugGroup;

typedef void (APIENTRYP PFNGLOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
GLAPI PFNGLOBJECTLABELPROC glObjectLabel;

typedef void (APIENTRYP PFNGLGETOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
GLAPI PFNGLGETOBJECTLABELPROC glGetObjectLabel;

typedef void (APIENTRYP PFNGLOBJECTPTRLABELPROC)(const void *ptr, GLsizei length, const GLchar *label);
GLAPI PFNGLOBJECTPTRLABELPROC glObjectPtrLabel;

typedef void (APIENTRYP PFNGLGETOBJECTPTRLABELPROC)(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
GLAPI PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabel;

typedef void (APIENTRYP PFNGLGETPOINTERVPROC)(GLenum pname, void **params);
GLAPI PFNGLGETPOINTERVPROC glGetPointerv;

