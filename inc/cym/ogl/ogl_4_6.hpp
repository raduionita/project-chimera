GLAPI int   OGL_VERSION_4_6;

typedef void (APIENTRYP PFNGLSPECIALIZESHADERPROC)(GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue);
GLAPI PFNGLSPECIALIZESHADERPROC glSpecializeShader;

typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)(GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
GLAPI PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC glMultiDrawArraysIndirectCount;

typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)(GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC glMultiDrawElementsIndirectCount;

typedef void (APIENTRYP PFNGLPOLYGONOFFSETCLAMPPROC)(GLfloat factor, GLfloat units, GLfloat clamp);
GLAPI PFNGLPOLYGONOFFSETCLAMPPROC glPolygonOffsetClamp;

