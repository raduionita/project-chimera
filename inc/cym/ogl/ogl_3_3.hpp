GLAPI int   OGL_VERSION_3_3;

typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name);
GLAPI PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glBindFragDataLocationIndexed;

typedef GLint (APIENTRYP PFNGLGETFRAGDATAINDEXPROC)(GLuint program, const GLchar *name);
GLAPI PFNGLGETFRAGDATAINDEXPROC glGetFragDataIndex;

typedef void (APIENTRYP PFNGLGENSAMPLERSPROC)(GLsizei count, GLuint *samplers);
GLAPI PFNGLGENSAMPLERSPROC glGenSamplers;

typedef void (APIENTRYP PFNGLDELETESAMPLERSPROC)(GLsizei count, const GLuint *samplers);
GLAPI PFNGLDELETESAMPLERSPROC glDeleteSamplers;

typedef GLboolean (APIENTRYP PFNGLISSAMPLERPROC)(GLuint sampler);
GLAPI PFNGLISSAMPLERPROC glIsSampler;

typedef void (APIENTRYP PFNGLBINDSAMPLERPROC)(GLuint unit, GLuint sampler);
GLAPI PFNGLBINDSAMPLERPROC glBindSampler;

typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIPROC)(GLuint sampler, GLenum pname, GLint param);
GLAPI PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri;

typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, const GLint *param);
GLAPI PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv;

typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFPROC)(GLuint sampler, GLenum pname, GLfloat param);
GLAPI PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf;

typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, const GLfloat *param);
GLAPI PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv;

typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, const GLint *param);
GLAPI PFNGLSAMPLERPARAMETERIIVPROC glSamplerParameterIiv;

typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, const GLuint *param);
GLAPI PFNGLSAMPLERPARAMETERIUIVPROC glSamplerParameterIuiv;

typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, GLint *params);
GLAPI PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv;

typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, GLint *params);
GLAPI PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIiv;

typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, GLfloat *params);
GLAPI PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv;

typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, GLuint *params);
GLAPI PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameterIuiv;

typedef void (APIENTRYP PFNGLQUERYCOUNTERPROC)(GLuint id, GLenum target);
GLAPI PFNGLQUERYCOUNTERPROC glQueryCounter;

typedef void (APIENTRYP PFNGLGETQUERYOBJECTI64VPROC)(GLuint id, GLenum pname, GLint64 *params);
GLAPI PFNGLGETQUERYOBJECTI64VPROC glGetQueryObjecti64v;

typedef void (APIENTRYP PFNGLGETQUERYOBJECTUI64VPROC)(GLuint id, GLenum pname, GLuint64 *params);
GLAPI PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v;

typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC)(GLuint index, GLuint divisor);
GLAPI PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor;

typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
GLAPI PFNGLVERTEXATTRIBP1UIPROC glVertexAttribP1ui;

typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
GLAPI PFNGLVERTEXATTRIBP1UIVPROC glVertexAttribP1uiv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
GLAPI PFNGLVERTEXATTRIBP2UIPROC glVertexAttribP2ui;

typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
GLAPI PFNGLVERTEXATTRIBP2UIVPROC glVertexAttribP2uiv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
GLAPI PFNGLVERTEXATTRIBP3UIPROC glVertexAttribP3ui;

typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
GLAPI PFNGLVERTEXATTRIBP3UIVPROC glVertexAttribP3uiv;

typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
GLAPI PFNGLVERTEXATTRIBP4UIPROC glVertexAttribP4ui;

typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
GLAPI PFNGLVERTEXATTRIBP4UIVPROC glVertexAttribP4uiv;

typedef void (APIENTRYP PFNGLVERTEXP2UIPROC)(GLenum type, GLuint value);
GLAPI PFNGLVERTEXP2UIPROC glVertexP2ui;

typedef void (APIENTRYP PFNGLVERTEXP2UIVPROC)(GLenum type, const GLuint *value);
GLAPI PFNGLVERTEXP2UIVPROC glVertexP2uiv;

typedef void (APIENTRYP PFNGLVERTEXP3UIPROC)(GLenum type, GLuint value);
GLAPI PFNGLVERTEXP3UIPROC glVertexP3ui;

typedef void (APIENTRYP PFNGLVERTEXP3UIVPROC)(GLenum type, const GLuint *value);
GLAPI PFNGLVERTEXP3UIVPROC glVertexP3uiv;

typedef void (APIENTRYP PFNGLVERTEXP4UIPROC)(GLenum type, GLuint value);
GLAPI PFNGLVERTEXP4UIPROC glVertexP4ui;

typedef void (APIENTRYP PFNGLVERTEXP4UIVPROC)(GLenum type, const GLuint *value);
GLAPI PFNGLVERTEXP4UIVPROC glVertexP4uiv;

typedef void (APIENTRYP PFNGLTEXCOORDP1UIPROC)(GLenum type, GLuint coords);
GLAPI PFNGLTEXCOORDP1UIPROC glTexCoordP1ui;

typedef void (APIENTRYP PFNGLTEXCOORDP1UIVPROC)(GLenum type, const GLuint *coords);
GLAPI PFNGLTEXCOORDP1UIVPROC glTexCoordP1uiv;

typedef void (APIENTRYP PFNGLTEXCOORDP2UIPROC)(GLenum type, GLuint coords);
GLAPI PFNGLTEXCOORDP2UIPROC glTexCoordP2ui;

typedef void (APIENTRYP PFNGLTEXCOORDP2UIVPROC)(GLenum type, const GLuint *coords);
GLAPI PFNGLTEXCOORDP2UIVPROC glTexCoordP2uiv;

typedef void (APIENTRYP PFNGLTEXCOORDP3UIPROC)(GLenum type, GLuint coords);
GLAPI PFNGLTEXCOORDP3UIPROC glTexCoordP3ui;

typedef void (APIENTRYP PFNGLTEXCOORDP3UIVPROC)(GLenum type, const GLuint *coords);
GLAPI PFNGLTEXCOORDP3UIVPROC glTexCoordP3uiv;

typedef void (APIENTRYP PFNGLTEXCOORDP4UIPROC)(GLenum type, GLuint coords);
GLAPI PFNGLTEXCOORDP4UIPROC glTexCoordP4ui;

typedef void (APIENTRYP PFNGLTEXCOORDP4UIVPROC)(GLenum type, const GLuint *coords);
GLAPI PFNGLTEXCOORDP4UIVPROC glTexCoordP4uiv;

typedef void (APIENTRYP PFNGLMULTITEXCOORDP1UIPROC)(GLenum texture, GLenum type, GLuint coords);
GLAPI PFNGLMULTITEXCOORDP1UIPROC glMultiTexCoordP1ui;

typedef void (APIENTRYP PFNGLMULTITEXCOORDP1UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
GLAPI PFNGLMULTITEXCOORDP1UIVPROC glMultiTexCoordP1uiv;

typedef void (APIENTRYP PFNGLMULTITEXCOORDP2UIPROC)(GLenum texture, GLenum type, GLuint coords);
GLAPI PFNGLMULTITEXCOORDP2UIPROC glMultiTexCoordP2ui;

typedef void (APIENTRYP PFNGLMULTITEXCOORDP2UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
GLAPI PFNGLMULTITEXCOORDP2UIVPROC glMultiTexCoordP2uiv;

typedef void (APIENTRYP PFNGLMULTITEXCOORDP3UIPROC)(GLenum texture, GLenum type, GLuint coords);
GLAPI PFNGLMULTITEXCOORDP3UIPROC glMultiTexCoordP3ui;

typedef void (APIENTRYP PFNGLMULTITEXCOORDP3UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
GLAPI PFNGLMULTITEXCOORDP3UIVPROC glMultiTexCoordP3uiv;

typedef void (APIENTRYP PFNGLMULTITEXCOORDP4UIPROC)(GLenum texture, GLenum type, GLuint coords);
GLAPI PFNGLMULTITEXCOORDP4UIPROC glMultiTexCoordP4ui;

typedef void (APIENTRYP PFNGLMULTITEXCOORDP4UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
GLAPI PFNGLMULTITEXCOORDP4UIVPROC glMultiTexCoordP4uiv;

typedef void (APIENTRYP PFNGLNORMALP3UIPROC)(GLenum type, GLuint coords);
GLAPI PFNGLNORMALP3UIPROC glNormalP3ui;

typedef void (APIENTRYP PFNGLNORMALP3UIVPROC)(GLenum type, const GLuint *coords);
GLAPI PFNGLNORMALP3UIVPROC glNormalP3uiv;

typedef void (APIENTRYP PFNGLCOLORP3UIPROC)(GLenum type, GLuint color);
GLAPI PFNGLCOLORP3UIPROC glColorP3ui;

typedef void (APIENTRYP PFNGLCOLORP3UIVPROC)(GLenum type, const GLuint *color);
GLAPI PFNGLCOLORP3UIVPROC glColorP3uiv;

typedef void (APIENTRYP PFNGLCOLORP4UIPROC)(GLenum type, GLuint color);
GLAPI PFNGLCOLORP4UIPROC glColorP4ui;

typedef void (APIENTRYP PFNGLCOLORP4UIVPROC)(GLenum type, const GLuint *color);
GLAPI PFNGLCOLORP4UIVPROC glColorP4uiv;

typedef void (APIENTRYP PFNGLSECONDARYCOLORP3UIPROC)(GLenum type, GLuint color);
GLAPI PFNGLSECONDARYCOLORP3UIPROC glSecondaryColorP3ui;

typedef void (APIENTRYP PFNGLSECONDARYCOLORP3UIVPROC)(GLenum type, const GLuint *color);
GLAPI PFNGLSECONDARYCOLORP3UIVPROC glSecondaryColorP3uiv;

