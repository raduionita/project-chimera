GLAPI int   OGL_VERSION_1_3;

typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum texture);
GLAPI PFNGLACTIVETEXTUREPROC _ptrc_glActiveTexture;
#define glActiveTexture _ptrc_glActiveTexture
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC)(GLfloat value, GLboolean invert);
GLAPI PFNGLSAMPLECOVERAGEPROC _ptrc_glSampleCoverage;
#define glSampleCoverage _ptrc_glSampleCoverage
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXIMAGE3DPROC _ptrc_glCompressedTexImage3D;
#define glCompressedTexImage3D _ptrc_glCompressedTexImage3D
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXIMAGE2DPROC _ptrc_glCompressedTexImage2D;
#define glCompressedTexImage2D _ptrc_glCompressedTexImage2D
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXIMAGE1DPROC _ptrc_glCompressedTexImage1D;
#define glCompressedTexImage1D _ptrc_glCompressedTexImage1D
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC _ptrc_glCompressedTexSubImage3D;
#define glCompressedTexSubImage3D _ptrc_glCompressedTexSubImage3D
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC _ptrc_glCompressedTexSubImage2D;
#define glCompressedTexSubImage2D _ptrc_glCompressedTexSubImage2D
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
GLAPI PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC _ptrc_glCompressedTexSubImage1D;
#define glCompressedTexSubImage1D _ptrc_glCompressedTexSubImage1D
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint level, void *img);
GLAPI PFNGLGETCOMPRESSEDTEXIMAGEPROC _ptrc_glGetCompressedTexImage;
#define glGetCompressedTexImage _ptrc_glGetCompressedTexImage
