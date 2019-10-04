GLAPI int   OGL_VERSION_4_5;

typedef void (APIENTRYP PFNGLCLIPCONTROLPROC)(GLenum origin, GLenum depth);
GLAPI PFNGLCLIPCONTROLPROC _ptrc_glClipControl;
#define glClipControl _ptrc_glClipControl
typedef void (APIENTRYP PFNGLCREATETRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint *ids);
GLAPI PFNGLCREATETRANSFORMFEEDBACKSPROC _ptrc_glCreateTransformFeedbacks;
#define glCreateTransformFeedbacks _ptrc_glCreateTransformFeedbacks
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)(GLuint xfb, GLuint index, GLuint buffer);
GLAPI PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC _ptrc_glTransformFeedbackBufferBase;
#define glTransformFeedbackBufferBase _ptrc_glTransformFeedbackBufferBase
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
GLAPI PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC _ptrc_glTransformFeedbackBufferRange;
#define glTransformFeedbackBufferRange _ptrc_glTransformFeedbackBufferRange
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKIVPROC)(GLuint xfb, GLenum pname, GLint *param);
GLAPI PFNGLGETTRANSFORMFEEDBACKIVPROC _ptrc_glGetTransformFeedbackiv;
#define glGetTransformFeedbackiv _ptrc_glGetTransformFeedbackiv
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI_VPROC)(GLuint xfb, GLenum pname, GLuint index, GLint *param);
GLAPI PFNGLGETTRANSFORMFEEDBACKI_VPROC _ptrc_glGetTransformFeedbacki_v;
#define glGetTransformFeedbacki_v _ptrc_glGetTransformFeedbacki_v
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI64_VPROC)(GLuint xfb, GLenum pname, GLuint index, GLint64 *param);
GLAPI PFNGLGETTRANSFORMFEEDBACKI64_VPROC _ptrc_glGetTransformFeedbacki64_v;
#define glGetTransformFeedbacki64_v _ptrc_glGetTransformFeedbacki64_v
typedef void (APIENTRYP PFNGLCREATEBUFFERSPROC)(GLsizei n, GLuint *buffers);
GLAPI PFNGLCREATEBUFFERSPROC _ptrc_glCreateBuffers;
#define glCreateBuffers _ptrc_glCreateBuffers
typedef void (APIENTRYP PFNGLNAMEDBUFFERSTORAGEPROC)(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);
GLAPI PFNGLNAMEDBUFFERSTORAGEPROC _ptrc_glNamedBufferStorage;
#define glNamedBufferStorage _ptrc_glNamedBufferStorage
typedef void (APIENTRYP PFNGLNAMEDBUFFERDATAPROC)(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);
GLAPI PFNGLNAMEDBUFFERDATAPROC _ptrc_glNamedBufferData;
#define glNamedBufferData _ptrc_glNamedBufferData
typedef void (APIENTRYP PFNGLNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);
GLAPI PFNGLNAMEDBUFFERSUBDATAPROC _ptrc_glNamedBufferSubData;
#define glNamedBufferSubData _ptrc_glNamedBufferSubData
typedef void (APIENTRYP PFNGLCOPYNAMEDBUFFERSUBDATAPROC)(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
GLAPI PFNGLCOPYNAMEDBUFFERSUBDATAPROC _ptrc_glCopyNamedBufferSubData;
#define glCopyNamedBufferSubData _ptrc_glCopyNamedBufferSubData
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERDATAPROC)(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data);
GLAPI PFNGLCLEARNAMEDBUFFERDATAPROC _ptrc_glClearNamedBufferData;
#define glClearNamedBufferData _ptrc_glClearNamedBufferData
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
GLAPI PFNGLCLEARNAMEDBUFFERSUBDATAPROC _ptrc_glClearNamedBufferSubData;
#define glClearNamedBufferSubData _ptrc_glClearNamedBufferSubData
typedef void * (APIENTRYP PFNGLMAPNAMEDBUFFERPROC)(GLuint buffer, GLenum access);
GLAPI PFNGLMAPNAMEDBUFFERPROC _ptrc_glMapNamedBuffer;
#define glMapNamedBuffer _ptrc_glMapNamedBuffer
typedef void * (APIENTRYP PFNGLMAPNAMEDBUFFERRANGEPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
GLAPI PFNGLMAPNAMEDBUFFERRANGEPROC _ptrc_glMapNamedBufferRange;
#define glMapNamedBufferRange _ptrc_glMapNamedBufferRange
typedef GLboolean (APIENTRYP PFNGLUNMAPNAMEDBUFFERPROC)(GLuint buffer);
GLAPI PFNGLUNMAPNAMEDBUFFERPROC _ptrc_glUnmapNamedBuffer;
#define glUnmapNamedBuffer _ptrc_glUnmapNamedBuffer
typedef void (APIENTRYP PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
GLAPI PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC _ptrc_glFlushMappedNamedBufferRange;
#define glFlushMappedNamedBufferRange _ptrc_glFlushMappedNamedBufferRange
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERIVPROC)(GLuint buffer, GLenum pname, GLint *params);
GLAPI PFNGLGETNAMEDBUFFERPARAMETERIVPROC _ptrc_glGetNamedBufferParameteriv;
#define glGetNamedBufferParameteriv _ptrc_glGetNamedBufferParameteriv
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)(GLuint buffer, GLenum pname, GLint64 *params);
GLAPI PFNGLGETNAMEDBUFFERPARAMETERI64VPROC _ptrc_glGetNamedBufferParameteri64v;
#define glGetNamedBufferParameteri64v _ptrc_glGetNamedBufferParameteri64v
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPOINTERVPROC)(GLuint buffer, GLenum pname, void **params);
GLAPI PFNGLGETNAMEDBUFFERPOINTERVPROC _ptrc_glGetNamedBufferPointerv;
#define glGetNamedBufferPointerv _ptrc_glGetNamedBufferPointerv
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, void *data);
GLAPI PFNGLGETNAMEDBUFFERSUBDATAPROC _ptrc_glGetNamedBufferSubData;
#define glGetNamedBufferSubData _ptrc_glGetNamedBufferSubData
typedef void (APIENTRYP PFNGLCREATEFRAMEBUFFERSPROC)(GLsizei n, GLuint *framebuffers);
GLAPI PFNGLCREATEFRAMEBUFFERSPROC _ptrc_glCreateFramebuffers;
#define glCreateFramebuffers _ptrc_glCreateFramebuffers
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GLAPI PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC _ptrc_glNamedFramebufferRenderbuffer;
#define glNamedFramebufferRenderbuffer _ptrc_glNamedFramebufferRenderbuffer
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)(GLuint framebuffer, GLenum pname, GLint param);
GLAPI PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC _ptrc_glNamedFramebufferParameteri;
#define glNamedFramebufferParameteri _ptrc_glNamedFramebufferParameteri
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
GLAPI PFNGLNAMEDFRAMEBUFFERTEXTUREPROC _ptrc_glNamedFramebufferTexture;
#define glNamedFramebufferTexture _ptrc_glNamedFramebufferTexture
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
GLAPI PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC _ptrc_glNamedFramebufferTextureLayer;
#define glNamedFramebufferTextureLayer _ptrc_glNamedFramebufferTextureLayer
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)(GLuint framebuffer, GLenum buf);
GLAPI PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC _ptrc_glNamedFramebufferDrawBuffer;
#define glNamedFramebufferDrawBuffer _ptrc_glNamedFramebufferDrawBuffer
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)(GLuint framebuffer, GLsizei n, const GLenum *bufs);
GLAPI PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC _ptrc_glNamedFramebufferDrawBuffers;
#define glNamedFramebufferDrawBuffers _ptrc_glNamedFramebufferDrawBuffers
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)(GLuint framebuffer, GLenum src);
GLAPI PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC _ptrc_glNamedFramebufferReadBuffer;
#define glNamedFramebufferReadBuffer _ptrc_glNamedFramebufferReadBuffer
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments);
GLAPI PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC _ptrc_glInvalidateNamedFramebufferData;
#define glInvalidateNamedFramebufferData _ptrc_glInvalidateNamedFramebufferData
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC _ptrc_glInvalidateNamedFramebufferSubData;
#define glInvalidateNamedFramebufferSubData _ptrc_glInvalidateNamedFramebufferSubData
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value);
GLAPI PFNGLCLEARNAMEDFRAMEBUFFERIVPROC _ptrc_glClearNamedFramebufferiv;
#define glClearNamedFramebufferiv _ptrc_glClearNamedFramebufferiv
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value);
GLAPI PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC _ptrc_glClearNamedFramebufferuiv;
#define glClearNamedFramebufferuiv _ptrc_glClearNamedFramebufferuiv
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value);
GLAPI PFNGLCLEARNAMEDFRAMEBUFFERFVPROC _ptrc_glClearNamedFramebufferfv;
#define glClearNamedFramebufferfv _ptrc_glClearNamedFramebufferfv
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
GLAPI PFNGLCLEARNAMEDFRAMEBUFFERFIPROC _ptrc_glClearNamedFramebufferfi;
#define glClearNamedFramebufferfi _ptrc_glClearNamedFramebufferfi
typedef void (APIENTRYP PFNGLBLITNAMEDFRAMEBUFFERPROC)(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
GLAPI PFNGLBLITNAMEDFRAMEBUFFERPROC _ptrc_glBlitNamedFramebuffer;
#define glBlitNamedFramebuffer _ptrc_glBlitNamedFramebuffer
typedef GLenum (APIENTRYP PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)(GLuint framebuffer, GLenum target);
GLAPI PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC _ptrc_glCheckNamedFramebufferStatus;
#define glCheckNamedFramebufferStatus _ptrc_glCheckNamedFramebufferStatus
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)(GLuint framebuffer, GLenum pname, GLint *param);
GLAPI PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC _ptrc_glGetNamedFramebufferParameteriv;
#define glGetNamedFramebufferParameteriv _ptrc_glGetNamedFramebufferParameteriv
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params);
GLAPI PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC _ptrc_glGetNamedFramebufferAttachmentParameteriv;
#define glGetNamedFramebufferAttachmentParameteriv _ptrc_glGetNamedFramebufferAttachmentParameteriv
typedef void (APIENTRYP PFNGLCREATERENDERBUFFERSPROC)(GLsizei n, GLuint *renderbuffers);
GLAPI PFNGLCREATERENDERBUFFERSPROC _ptrc_glCreateRenderbuffers;
#define glCreateRenderbuffers _ptrc_glCreateRenderbuffers
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEPROC)(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
GLAPI PFNGLNAMEDRENDERBUFFERSTORAGEPROC _ptrc_glNamedRenderbufferStorage;
#define glNamedRenderbufferStorage _ptrc_glNamedRenderbufferStorage
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GLAPI PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC _ptrc_glNamedRenderbufferStorageMultisample;
#define glNamedRenderbufferStorageMultisample _ptrc_glNamedRenderbufferStorageMultisample
typedef void (APIENTRYP PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)(GLuint renderbuffer, GLenum pname, GLint *params);
GLAPI PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC _ptrc_glGetNamedRenderbufferParameteriv;
#define glGetNamedRenderbufferParameteriv _ptrc_glGetNamedRenderbufferParameteriv
typedef void (APIENTRYP PFNGLCREATETEXTURESPROC)(GLenum target, GLsizei n, GLuint *textures);
GLAPI PFNGLCREATETEXTURESPROC _ptrc_glCreateTextures;
#define glCreateTextures _ptrc_glCreateTextures
typedef void (APIENTRYP PFNGLTEXTUREBUFFERPROC)(GLuint texture, GLenum internalformat, GLuint buffer);
GLAPI PFNGLTEXTUREBUFFERPROC _ptrc_glTextureBuffer;
#define glTextureBuffer _ptrc_glTextureBuffer
typedef void (APIENTRYP PFNGLTEXTUREBUFFERRANGEPROC)(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
GLAPI PFNGLTEXTUREBUFFERRANGEPROC _ptrc_glTextureBufferRange;
#define glTextureBufferRange _ptrc_glTextureBufferRange
typedef void (APIENTRYP PFNGLTEXTURESTORAGE1DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
GLAPI PFNGLTEXTURESTORAGE1DPROC _ptrc_glTextureStorage1D;
#define glTextureStorage1D _ptrc_glTextureStorage1D
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
GLAPI PFNGLTEXTURESTORAGE2DPROC _ptrc_glTextureStorage2D;
#define glTextureStorage2D _ptrc_glTextureStorage2D
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
GLAPI PFNGLTEXTURESTORAGE3DPROC _ptrc_glTextureStorage3D;
#define glTextureStorage3D _ptrc_glTextureStorage3D
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
GLAPI PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC _ptrc_glTextureStorage2DMultisample;
#define glTextureStorage2DMultisample _ptrc_glTextureStorage2DMultisample
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
GLAPI PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC _ptrc_glTextureStorage3DMultisample;
#define glTextureStorage3DMultisample _ptrc_glTextureStorage3DMultisample
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
GLAPI PFNGLTEXTURESUBIMAGE1DPROC _ptrc_glTextureSubImage1D;
#define glTextureSubImage1D _ptrc_glTextureSubImage1D
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
GLAPI PFNGLTEXTURESUBIMAGE2DPROC _ptrc_glTextureSubImage2D;
#define glTextureSubImage2D _ptrc_glTextureSubImage2D
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
GLAPI PFNGLTEXTURESUBIMAGE3DPROC _ptrc_glTextureSubImage3D;
#define glTextureSubImage3D _ptrc_glTextureSubImage3D
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC _ptrc_glCompressedTextureSubImage1D;
#define glCompressedTextureSubImage1D _ptrc_glCompressedTextureSubImage1D
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC _ptrc_glCompressedTextureSubImage2D;
#define glCompressedTextureSubImage2D _ptrc_glCompressedTextureSubImage2D
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC _ptrc_glCompressedTextureSubImage3D;
#define glCompressedTextureSubImage3D _ptrc_glCompressedTextureSubImage3D
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
GLAPI PFNGLCOPYTEXTURESUBIMAGE1DPROC _ptrc_glCopyTextureSubImage1D;
#define glCopyTextureSubImage1D _ptrc_glCopyTextureSubImage1D
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLCOPYTEXTURESUBIMAGE2DPROC _ptrc_glCopyTextureSubImage2D;
#define glCopyTextureSubImage2D _ptrc_glCopyTextureSubImage2D
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLCOPYTEXTURESUBIMAGE3DPROC _ptrc_glCopyTextureSubImage3D;
#define glCopyTextureSubImage3D _ptrc_glCopyTextureSubImage3D
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFPROC)(GLuint texture, GLenum pname, GLfloat param);
GLAPI PFNGLTEXTUREPARAMETERFPROC _ptrc_glTextureParameterf;
#define glTextureParameterf _ptrc_glTextureParameterf
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFVPROC)(GLuint texture, GLenum pname, const GLfloat *param);
GLAPI PFNGLTEXTUREPARAMETERFVPROC _ptrc_glTextureParameterfv;
#define glTextureParameterfv _ptrc_glTextureParameterfv
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIPROC)(GLuint texture, GLenum pname, GLint param);
GLAPI PFNGLTEXTUREPARAMETERIPROC _ptrc_glTextureParameteri;
#define glTextureParameteri _ptrc_glTextureParameteri
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIIVPROC)(GLuint texture, GLenum pname, const GLint *params);
GLAPI PFNGLTEXTUREPARAMETERIIVPROC _ptrc_glTextureParameterIiv;
#define glTextureParameterIiv _ptrc_glTextureParameterIiv
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIUIVPROC)(GLuint texture, GLenum pname, const GLuint *params);
GLAPI PFNGLTEXTUREPARAMETERIUIVPROC _ptrc_glTextureParameterIuiv;
#define glTextureParameterIuiv _ptrc_glTextureParameterIuiv
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIVPROC)(GLuint texture, GLenum pname, const GLint *param);
GLAPI PFNGLTEXTUREPARAMETERIVPROC _ptrc_glTextureParameteriv;
#define glTextureParameteriv _ptrc_glTextureParameteriv
typedef void (APIENTRYP PFNGLGENERATETEXTUREMIPMAPPROC)(GLuint texture);
GLAPI PFNGLGENERATETEXTUREMIPMAPPROC _ptrc_glGenerateTextureMipmap;
#define glGenerateTextureMipmap _ptrc_glGenerateTextureMipmap
typedef void (APIENTRYP PFNGLBINDTEXTUREUNITPROC)(GLuint unit, GLuint texture);
GLAPI PFNGLBINDTEXTUREUNITPROC _ptrc_glBindTextureUnit;
#define glBindTextureUnit _ptrc_glBindTextureUnit
typedef void (APIENTRYP PFNGLGETTEXTUREIMAGEPROC)(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
GLAPI PFNGLGETTEXTUREIMAGEPROC _ptrc_glGetTextureImage;
#define glGetTextureImage _ptrc_glGetTextureImage
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)(GLuint texture, GLint level, GLsizei bufSize, void *pixels);
GLAPI PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC _ptrc_glGetCompressedTextureImage;
#define glGetCompressedTextureImage _ptrc_glGetCompressedTextureImage
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERFVPROC)(GLuint texture, GLint level, GLenum pname, GLfloat *params);
GLAPI PFNGLGETTEXTURELEVELPARAMETERFVPROC _ptrc_glGetTextureLevelParameterfv;
#define glGetTextureLevelParameterfv _ptrc_glGetTextureLevelParameterfv
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERIVPROC)(GLuint texture, GLint level, GLenum pname, GLint *params);
GLAPI PFNGLGETTEXTURELEVELPARAMETERIVPROC _ptrc_glGetTextureLevelParameteriv;
#define glGetTextureLevelParameteriv _ptrc_glGetTextureLevelParameteriv
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERFVPROC)(GLuint texture, GLenum pname, GLfloat *params);
GLAPI PFNGLGETTEXTUREPARAMETERFVPROC _ptrc_glGetTextureParameterfv;
#define glGetTextureParameterfv _ptrc_glGetTextureParameterfv
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIIVPROC)(GLuint texture, GLenum pname, GLint *params);
GLAPI PFNGLGETTEXTUREPARAMETERIIVPROC _ptrc_glGetTextureParameterIiv;
#define glGetTextureParameterIiv _ptrc_glGetTextureParameterIiv
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIUIVPROC)(GLuint texture, GLenum pname, GLuint *params);
GLAPI PFNGLGETTEXTUREPARAMETERIUIVPROC _ptrc_glGetTextureParameterIuiv;
#define glGetTextureParameterIuiv _ptrc_glGetTextureParameterIuiv
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIVPROC)(GLuint texture, GLenum pname, GLint *params);
GLAPI PFNGLGETTEXTUREPARAMETERIVPROC _ptrc_glGetTextureParameteriv;
#define glGetTextureParameteriv _ptrc_glGetTextureParameteriv
typedef void (APIENTRYP PFNGLCREATEVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
GLAPI PFNGLCREATEVERTEXARRAYSPROC _ptrc_glCreateVertexArrays;
#define glCreateVertexArrays _ptrc_glCreateVertexArrays
typedef void (APIENTRYP PFNGLDISABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
GLAPI PFNGLDISABLEVERTEXARRAYATTRIBPROC _ptrc_glDisableVertexArrayAttrib;
#define glDisableVertexArrayAttrib _ptrc_glDisableVertexArrayAttrib
typedef void (APIENTRYP PFNGLENABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
GLAPI PFNGLENABLEVERTEXARRAYATTRIBPROC _ptrc_glEnableVertexArrayAttrib;
#define glEnableVertexArrayAttrib _ptrc_glEnableVertexArrayAttrib
typedef void (APIENTRYP PFNGLVERTEXARRAYELEMENTBUFFERPROC)(GLuint vaobj, GLuint buffer);
GLAPI PFNGLVERTEXARRAYELEMENTBUFFERPROC _ptrc_glVertexArrayElementBuffer;
#define glVertexArrayElementBuffer _ptrc_glVertexArrayElementBuffer
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERPROC)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
GLAPI PFNGLVERTEXARRAYVERTEXBUFFERPROC _ptrc_glVertexArrayVertexBuffer;
#define glVertexArrayVertexBuffer _ptrc_glVertexArrayVertexBuffer
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERSPROC)(GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
GLAPI PFNGLVERTEXARRAYVERTEXBUFFERSPROC _ptrc_glVertexArrayVertexBuffers;
#define glVertexArrayVertexBuffers _ptrc_glVertexArrayVertexBuffers
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBBINDINGPROC)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
GLAPI PFNGLVERTEXARRAYATTRIBBINDINGPROC _ptrc_glVertexArrayAttribBinding;
#define glVertexArrayAttribBinding _ptrc_glVertexArrayAttribBinding
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
GLAPI PFNGLVERTEXARRAYATTRIBFORMATPROC _ptrc_glVertexArrayAttribFormat;
#define glVertexArrayAttribFormat _ptrc_glVertexArrayAttribFormat
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBIFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
GLAPI PFNGLVERTEXARRAYATTRIBIFORMATPROC _ptrc_glVertexArrayAttribIFormat;
#define glVertexArrayAttribIFormat _ptrc_glVertexArrayAttribIFormat
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBLFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
GLAPI PFNGLVERTEXARRAYATTRIBLFORMATPROC _ptrc_glVertexArrayAttribLFormat;
#define glVertexArrayAttribLFormat _ptrc_glVertexArrayAttribLFormat
typedef void (APIENTRYP PFNGLVERTEXARRAYBINDINGDIVISORPROC)(GLuint vaobj, GLuint bindingindex, GLuint divisor);
GLAPI PFNGLVERTEXARRAYBINDINGDIVISORPROC _ptrc_glVertexArrayBindingDivisor;
#define glVertexArrayBindingDivisor _ptrc_glVertexArrayBindingDivisor
typedef void (APIENTRYP PFNGLGETVERTEXARRAYIVPROC)(GLuint vaobj, GLenum pname, GLint *param);
GLAPI PFNGLGETVERTEXARRAYIVPROC _ptrc_glGetVertexArrayiv;
#define glGetVertexArrayiv _ptrc_glGetVertexArrayiv
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXEDIVPROC)(GLuint vaobj, GLuint index, GLenum pname, GLint *param);
GLAPI PFNGLGETVERTEXARRAYINDEXEDIVPROC _ptrc_glGetVertexArrayIndexediv;
#define glGetVertexArrayIndexediv _ptrc_glGetVertexArrayIndexediv
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXED64IVPROC)(GLuint vaobj, GLuint index, GLenum pname, GLint64 *param);
GLAPI PFNGLGETVERTEXARRAYINDEXED64IVPROC _ptrc_glGetVertexArrayIndexed64iv;
#define glGetVertexArrayIndexed64iv _ptrc_glGetVertexArrayIndexed64iv
typedef void (APIENTRYP PFNGLCREATESAMPLERSPROC)(GLsizei n, GLuint *samplers);
GLAPI PFNGLCREATESAMPLERSPROC _ptrc_glCreateSamplers;
#define glCreateSamplers _ptrc_glCreateSamplers
typedef void (APIENTRYP PFNGLCREATEPROGRAMPIPELINESPROC)(GLsizei n, GLuint *pipelines);
GLAPI PFNGLCREATEPROGRAMPIPELINESPROC _ptrc_glCreateProgramPipelines;
#define glCreateProgramPipelines _ptrc_glCreateProgramPipelines
typedef void (APIENTRYP PFNGLCREATEQUERIESPROC)(GLenum target, GLsizei n, GLuint *ids);
GLAPI PFNGLCREATEQUERIESPROC _ptrc_glCreateQueries;
#define glCreateQueries _ptrc_glCreateQueries
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTI64VPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
GLAPI PFNGLGETQUERYBUFFEROBJECTI64VPROC _ptrc_glGetQueryBufferObjecti64v;
#define glGetQueryBufferObjecti64v _ptrc_glGetQueryBufferObjecti64v
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTIVPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
GLAPI PFNGLGETQUERYBUFFEROBJECTIVPROC _ptrc_glGetQueryBufferObjectiv;
#define glGetQueryBufferObjectiv _ptrc_glGetQueryBufferObjectiv
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUI64VPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
GLAPI PFNGLGETQUERYBUFFEROBJECTUI64VPROC _ptrc_glGetQueryBufferObjectui64v;
#define glGetQueryBufferObjectui64v _ptrc_glGetQueryBufferObjectui64v
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUIVPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
GLAPI PFNGLGETQUERYBUFFEROBJECTUIVPROC _ptrc_glGetQueryBufferObjectuiv;
#define glGetQueryBufferObjectuiv _ptrc_glGetQueryBufferObjectuiv
typedef void (APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC)(GLbitfield barriers);
GLAPI PFNGLMEMORYBARRIERBYREGIONPROC _ptrc_glMemoryBarrierByRegion;
#define glMemoryBarrierByRegion _ptrc_glMemoryBarrierByRegion
typedef void (APIENTRYP PFNGLGETTEXTURESUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
GLAPI PFNGLGETTEXTURESUBIMAGEPROC _ptrc_glGetTextureSubImage;
#define glGetTextureSubImage _ptrc_glGetTextureSubImage
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels);
GLAPI PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC _ptrc_glGetCompressedTextureSubImage;
#define glGetCompressedTextureSubImage _ptrc_glGetCompressedTextureSubImage
typedef GLenum (APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC)(void);
GLAPI PFNGLGETGRAPHICSRESETSTATUSPROC _ptrc_glGetGraphicsResetStatus;
#define glGetGraphicsResetStatus _ptrc_glGetGraphicsResetStatus
typedef void (APIENTRYP PFNGLGETNCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint lod, GLsizei bufSize, void *pixels);
GLAPI PFNGLGETNCOMPRESSEDTEXIMAGEPROC _ptrc_glGetnCompressedTexImage;
#define glGetnCompressedTexImage _ptrc_glGetnCompressedTexImage
typedef void (APIENTRYP PFNGLGETNTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
GLAPI PFNGLGETNTEXIMAGEPROC _ptrc_glGetnTexImage;
#define glGetnTexImage _ptrc_glGetnTexImage
typedef void (APIENTRYP PFNGLGETNUNIFORMDVPROC)(GLuint program, GLint location, GLsizei bufSize, GLdouble *params);
GLAPI PFNGLGETNUNIFORMDVPROC _ptrc_glGetnUniformdv;
#define glGetnUniformdv _ptrc_glGetnUniformdv
typedef void (APIENTRYP PFNGLGETNUNIFORMFVPROC)(GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
GLAPI PFNGLGETNUNIFORMFVPROC _ptrc_glGetnUniformfv;
#define glGetnUniformfv _ptrc_glGetnUniformfv
typedef void (APIENTRYP PFNGLGETNUNIFORMIVPROC)(GLuint program, GLint location, GLsizei bufSize, GLint *params);
GLAPI PFNGLGETNUNIFORMIVPROC _ptrc_glGetnUniformiv;
#define glGetnUniformiv _ptrc_glGetnUniformiv
typedef void (APIENTRYP PFNGLGETNUNIFORMUIVPROC)(GLuint program, GLint location, GLsizei bufSize, GLuint *params);
GLAPI PFNGLGETNUNIFORMUIVPROC _ptrc_glGetnUniformuiv;
#define glGetnUniformuiv _ptrc_glGetnUniformuiv
typedef void (APIENTRYP PFNGLREADNPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
GLAPI PFNGLREADNPIXELSPROC _ptrc_glReadnPixels;
#define glReadnPixels _ptrc_glReadnPixels
typedef void (APIENTRYP PFNGLGETNMAPDVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLdouble *v);
GLAPI PFNGLGETNMAPDVPROC _ptrc_glGetnMapdv;
#define glGetnMapdv _ptrc_glGetnMapdv
typedef void (APIENTRYP PFNGLGETNMAPFVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLfloat *v);
GLAPI PFNGLGETNMAPFVPROC _ptrc_glGetnMapfv;
#define glGetnMapfv _ptrc_glGetnMapfv
typedef void (APIENTRYP PFNGLGETNMAPIVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLint *v);
GLAPI PFNGLGETNMAPIVPROC _ptrc_glGetnMapiv;
#define glGetnMapiv _ptrc_glGetnMapiv
typedef void (APIENTRYP PFNGLGETNPIXELMAPFVPROC)(GLenum map, GLsizei bufSize, GLfloat *values);
GLAPI PFNGLGETNPIXELMAPFVPROC _ptrc_glGetnPixelMapfv;
#define glGetnPixelMapfv _ptrc_glGetnPixelMapfv
typedef void (APIENTRYP PFNGLGETNPIXELMAPUIVPROC)(GLenum map, GLsizei bufSize, GLuint *values);
GLAPI PFNGLGETNPIXELMAPUIVPROC _ptrc_glGetnPixelMapuiv;
#define glGetnPixelMapuiv _ptrc_glGetnPixelMapuiv
typedef void (APIENTRYP PFNGLGETNPIXELMAPUSVPROC)(GLenum map, GLsizei bufSize, GLushort *values);
GLAPI PFNGLGETNPIXELMAPUSVPROC _ptrc_glGetnPixelMapusv;
#define glGetnPixelMapusv _ptrc_glGetnPixelMapusv
typedef void (APIENTRYP PFNGLGETNPOLYGONSTIPPLEPROC)(GLsizei bufSize, GLubyte *pattern);
GLAPI PFNGLGETNPOLYGONSTIPPLEPROC _ptrc_glGetnPolygonStipple;
#define glGetnPolygonStipple _ptrc_glGetnPolygonStipple
typedef void (APIENTRYP PFNGLGETNCOLORTABLEPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *table);
GLAPI PFNGLGETNCOLORTABLEPROC _ptrc_glGetnColorTable;
#define glGetnColorTable _ptrc_glGetnColorTable
typedef void (APIENTRYP PFNGLGETNCONVOLUTIONFILTERPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *image);
GLAPI PFNGLGETNCONVOLUTIONFILTERPROC _ptrc_glGetnConvolutionFilter;
#define glGetnConvolutionFilter _ptrc_glGetnConvolutionFilter
typedef void (APIENTRYP PFNGLGETNSEPARABLEFILTERPROC)(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void *row, GLsizei columnBufSize, void *column, void *span);
GLAPI PFNGLGETNSEPARABLEFILTERPROC _ptrc_glGetnSeparableFilter;
#define glGetnSeparableFilter _ptrc_glGetnSeparableFilter
typedef void (APIENTRYP PFNGLGETNHISTOGRAMPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values);
GLAPI PFNGLGETNHISTOGRAMPROC _ptrc_glGetnHistogram;
#define glGetnHistogram _ptrc_glGetnHistogram
typedef void (APIENTRYP PFNGLGETNMINMAXPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values);
GLAPI PFNGLGETNMINMAXPROC _ptrc_glGetnMinmax;
#define glGetnMinmax _ptrc_glGetnMinmax
typedef void (APIENTRYP PFNGLTEXTUREBARRIERPROC)(void);
GLAPI PFNGLTEXTUREBARRIERPROC _ptrc_glTextureBarrier;
#define glTextureBarrier _ptrc_glTextureBarrier
