GLAPI int   OGL_VERSION_1_3;

typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum texture);
GLAPI PFNGLACTIVETEXTUREPROC glActiveTexture;

typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC)(GLfloat value, GLboolean invert);
GLAPI PFNGLSAMPLECOVERAGEPROC glSampleCoverage;

typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D;

typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;

typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D;

typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D;

typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;

typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D;

typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint level, void *img);
GLAPI PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage;

