GLAPI int   OGL_VERSION_4_6;

typedef void (APIENTRYP PFNGLSPECIALIZESHADERPROC)(GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue);
GLAPI PFNGLSPECIALIZESHADERPROC _ptrc_glSpecializeShader;
#define glSpecializeShader _ptrc_glSpecializeShader
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)(GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
GLAPI PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC _ptrc_glMultiDrawArraysIndirectCount;
#define glMultiDrawArraysIndirectCount _ptrc_glMultiDrawArraysIndirectCount
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)(GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC _ptrc_glMultiDrawElementsIndirectCount;
#define glMultiDrawElementsIndirectCount _ptrc_glMultiDrawElementsIndirectCount
typedef void (APIENTRYP PFNGLPOLYGONOFFSETCLAMPPROC)(GLfloat factor, GLfloat units, GLfloat clamp);
GLAPI PFNGLPOLYGONOFFSETCLAMPPROC _ptrc_glPolygonOffsetClamp;
#define glPolygonOffsetClamp _ptrc_glPolygonOffsetClamp
