#include "glc/glc.hpp"

#if defined(__APPLE__)
#include <dlfcn.h>
static void* aplGLGetProcAddress (const char *name) {
  static void* image = NULL;
  
  if (NULL == image)
    image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);

  return (image ? dlsym(image, name) : NULL);
}
#endif /* __APPLE__ */

#if defined(__sgi) || defined (__sun)
#include <dlfcn.h>
#include <stdio.h>
static void* sunGetProcAddress (const GLubyte* name) {
  static void* h = NULL;
  static void* gpa;

  if (h == NULL)
  {
    if ((h = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL)) == NULL) return NULL;
    gpa = dlsym(h, "glXGetProcAddress");
  }

  if (gpa != NULL)
    return ((void*(*)(const GLubyte*))gpa)(name);
  else
    return dlsym(h, (const char*)name);
}
#endif /* __sgi || __sun */

#if defined(_WIN32)

#ifdef _MSC_VER
#pragma warning(disable: 4055)
#pragma warning(disable: 4054)
#pragma warning(disable: 4996)
#endif

static int testPointer(const PROC pTest) {
  ptrdiff_t iTest;
  if (!pTest) return 0;
  iTest = (ptrdiff_t) pTest;
  
  if (iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1) return 0;
  
  return 1;
}

static PROC winGetProcAddress(const char* name) {
  static HMODULE hModule = NULL;
  PROC pFunc = wglGetProcAddress((LPCSTR) name);
  if (testPointer(pFunc)) { 
    return pFunc; 
  }
  if (hModule == NULL) {
    hModule = ::GetModuleHandleA("OpenGL32.dll");
  }
  return (PROC) ::GetProcAddress(hModule, (LPCSTR) name);
}

#define glGetProcAddress(name) winGetProcAddress(name)
#else
#if defined(__APPLE__)
#define glGetProcAddress(name) aplGLGetProcAddress(name)
#else
#if defined(__sgi) || defined(__sun)
#define glGetProcAddress(name) sunGetProcAddress(name)
#else /* GLX */
#include <GL/glx.h>

#define glGetProcAddress(name) (*glXGetProcAddressARB)((const GLubyte*)name)
#endif
#endif
#endif

PFNGLLOADIDENTITYPROC                                glLoadIdentity                                = NULL;
PFNGLORTHOPROC                                       glOrtho                                       = NULL;
PFNGLMATRIXMODEPROC                                  glMatrixMode                                  = NULL;
PFNGLBEGINPROC                                       glBegin                                       = NULL;
PFNGLENDPROC                                         glEnd                                         = NULL;
PFNGLCOLOR3FPROC                                     glColor3f                                     = NULL;
PFNGLVERTEX3FPROC                                    glVertex3f                                    = NULL;
PFNGLACTIVESHADERPROGRAMPROC                         glActiveShaderProgram                         = NULL;
PFNGLACTIVETEXTUREPROC                               glActiveTexture                               = NULL;
PFNGLATTACHSHADERPROC                                glAttachShader                                = NULL;
PFNGLBEGINCONDITIONALRENDERPROC                      glBeginConditionalRender                      = NULL;
PFNGLBEGINQUERYPROC                                  glBeginQuery                                  = NULL;
PFNGLBEGINQUERYINDEXEDPROC                           glBeginQueryIndexed                           = NULL;
PFNGLBEGINTRANSFORMFEEDBACKPROC                      glBeginTransformFeedback                      = NULL;
PFNGLBINDATTRIBLOCATIONPROC                          glBindAttribLocation                          = NULL;
PFNGLBINDBUFFERPROC                                  glBindBuffer                                  = NULL;
PFNGLBINDBUFFERBASEPROC                              glBindBufferBase                              = NULL;
PFNGLBINDBUFFERRANGEPROC                             glBindBufferRange                             = NULL;
PFNGLBINDBUFFERSBASEPROC                             glBindBuffersBase                             = NULL;
PFNGLBINDBUFFERSRANGEPROC                            glBindBuffersRange                            = NULL;
PFNGLBINDFRAGDATALOCATIONPROC                        glBindFragDataLocation                        = NULL;
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC                 glBindFragDataLocationIndexed                 = NULL;
PFNGLBINDFRAMEBUFFERPROC                             glBindFramebuffer                             = NULL;
PFNGLBINDIMAGETEXTUREPROC                            glBindImageTexture                            = NULL;
PFNGLBINDIMAGETEXTURESPROC                           glBindImageTextures                           = NULL;
PFNGLBINDPROGRAMPIPELINEPROC                         glBindProgramPipeline                         = NULL;
PFNGLBINDRENDERBUFFERPROC                            glBindRenderbuffer                            = NULL;
PFNGLBINDSAMPLERPROC                                 glBindSampler                                 = NULL;
PFNGLBINDSAMPLERSPROC                                glBindSamplers                                = NULL;
PFNGLBINDTEXTUREPROC                                 glBindTexture                                 = NULL;
PFNGLBINDTEXTUREUNITPROC                             glBindTextureUnit                             = NULL;
PFNGLBINDTEXTURESPROC                                glBindTextures                                = NULL;
PFNGLBINDTRANSFORMFEEDBACKPROC                       glBindTransformFeedback                       = NULL;
PFNGLBINDVERTEXARRAYPROC                             glBindVertexArray                             = NULL;
PFNGLBINDVERTEXBUFFERPROC                            glBindVertexBuffer                            = NULL;
PFNGLBINDVERTEXBUFFERSPROC                           glBindVertexBuffers                           = NULL;
PFNGLBLENDCOLORPROC                                  glBlendColor                                  = NULL;
PFNGLBLENDEQUATIONPROC                               glBlendEquation                               = NULL;
PFNGLBLENDEQUATIONSEPARATEPROC                       glBlendEquationSeparate                       = NULL;
PFNGLBLENDEQUATIONSEPARATEIPROC                      glBlendEquationSeparatei                      = NULL;
PFNGLBLENDEQUATIONIPROC                              glBlendEquationi                              = NULL;
PFNGLBLENDFUNCPROC                                   glBlendFunc                                   = NULL;
PFNGLBLENDFUNCSEPARATEPROC                           glBlendFuncSeparate                           = NULL;
PFNGLBLENDFUNCSEPARATEIPROC                          glBlendFuncSeparatei                          = NULL;
PFNGLBLENDFUNCIPROC                                  glBlendFunci                                  = NULL;
PFNGLBLITFRAMEBUFFERPROC                             glBlitFramebuffer                             = NULL;
PFNGLBLITNAMEDFRAMEBUFFERPROC                        glBlitNamedFramebuffer                        = NULL;
PFNGLBUFFERDATAPROC                                  glBufferData                                  = NULL;
PFNGLBUFFERSTORAGEPROC                               glBufferStorage                               = NULL;
PFNGLBUFFERSUBDATAPROC                               glBufferSubData                               = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC                      glCheckFramebufferStatus                      = NULL;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC                 glCheckNamedFramebufferStatus                 = NULL;
PFNGLCLAMPCOLORPROC                                  glClampColor                                  = NULL;
PFNGLCLEARPROC                                       glClear                                       = NULL;
PFNGLCLEARBUFFERDATAPROC                             glClearBufferData                             = NULL;
PFNGLCLEARBUFFERSUBDATAPROC                          glClearBufferSubData                          = NULL;
PFNGLCLEARBUFFERFIPROC                               glClearBufferfi                               = NULL;
PFNGLCLEARBUFFERFVPROC                               glClearBufferfv                               = NULL;
PFNGLCLEARBUFFERIVPROC                               glClearBufferiv                               = NULL;
PFNGLCLEARBUFFERUIVPROC                              glClearBufferuiv                              = NULL;
PFNGLCLEARCOLORPROC                                  glClearColor                                  = NULL;
PFNGLCLEARDEPTHPROC                                  glClearDepth                                  = NULL;
PFNGLCLEARDEPTHFPROC                                 glClearDepthf                                 = NULL;
PFNGLCLEARNAMEDBUFFERDATAPROC                        glClearNamedBufferData                        = NULL;
PFNGLCLEARNAMEDBUFFERSUBDATAPROC                     glClearNamedBufferSubData                     = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERFIPROC                     glClearNamedFramebufferfi                     = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERFVPROC                     glClearNamedFramebufferfv                     = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERIVPROC                     glClearNamedFramebufferiv                     = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC                    glClearNamedFramebufferuiv                    = NULL;
PFNGLCLEARSTENCILPROC                                glClearStencil                                = NULL;
PFNGLCLEARTEXIMAGEPROC                               glClearTexImage                               = NULL;
PFNGLCLEARTEXSUBIMAGEPROC                            glClearTexSubImage                            = NULL;
PFNGLCLIENTWAITSYNCPROC                              glClientWaitSync                              = NULL;
PFNGLCLIPCONTROLPROC                                 glClipControl                                 = NULL;
PFNGLCOLORMASKPROC                                   glColorMask                                   = NULL;
PFNGLCOLORMASKIPROC                                  glColorMaski                                  = NULL;
PFNGLCOLORP3UIPROC                                   glColorP3ui                                   = NULL;
PFNGLCOLORP3UIVPROC                                  glColorP3uiv                                  = NULL;
PFNGLCOLORP4UIPROC                                   glColorP4ui                                   = NULL;
PFNGLCOLORP4UIVPROC                                  glColorP4uiv                                  = NULL;
PFNGLCOMPILESHADERPROC                               glCompileShader                               = NULL;
PFNGLCOMPRESSEDTEXIMAGE1DPROC                        glCompressedTexImage1D                        = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC                        glCompressedTexImage2D                        = NULL;
PFNGLCOMPRESSEDTEXIMAGE3DPROC                        glCompressedTexImage3D                        = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC                     glCompressedTexSubImage1D                     = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC                     glCompressedTexSubImage2D                     = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC                     glCompressedTexSubImage3D                     = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC                 glCompressedTextureSubImage1D                 = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC                 glCompressedTextureSubImage2D                 = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC                 glCompressedTextureSubImage3D                 = NULL;
PFNGLCOPYBUFFERSUBDATAPROC                           glCopyBufferSubData                           = NULL;
PFNGLCOPYIMAGESUBDATAPROC                            glCopyImageSubData                            = NULL;
PFNGLCOPYNAMEDBUFFERSUBDATAPROC                      glCopyNamedBufferSubData                      = NULL;
PFNGLCOPYTEXIMAGE1DPROC                              glCopyTexImage1D                              = NULL;
PFNGLCOPYTEXIMAGE2DPROC                              glCopyTexImage2D                              = NULL;
PFNGLCOPYTEXSUBIMAGE1DPROC                           glCopyTexSubImage1D                           = NULL;
PFNGLCOPYTEXSUBIMAGE2DPROC                           glCopyTexSubImage2D                           = NULL;
PFNGLCOPYTEXSUBIMAGE3DPROC                           glCopyTexSubImage3D                           = NULL;
PFNGLCOPYTEXTURESUBIMAGE1DPROC                       glCopyTextureSubImage1D                       = NULL;
PFNGLCOPYTEXTURESUBIMAGE2DPROC                       glCopyTextureSubImage2D                       = NULL;
PFNGLCOPYTEXTURESUBIMAGE3DPROC                       glCopyTextureSubImage3D                       = NULL;
PFNGLCREATEBUFFERSPROC                               glCreateBuffers                               = NULL;
PFNGLCREATEFRAMEBUFFERSPROC                          glCreateFramebuffers                          = NULL;
PFNGLCREATEPROGRAMPROC                               glCreateProgram                               = NULL;
PFNGLCREATEPROGRAMPIPELINESPROC                      glCreateProgramPipelines                      = NULL;
PFNGLCREATEQUERIESPROC                               glCreateQueries                               = NULL;
PFNGLCREATERENDERBUFFERSPROC                         glCreateRenderbuffers                         = NULL;
PFNGLCREATESAMPLERSPROC                              glCreateSamplers                              = NULL;
PFNGLCREATESHADERPROC                                glCreateShader                                = NULL;
PFNGLCREATESHADERPROGRAMVPROC                        glCreateShaderProgramv                        = NULL;
PFNGLCREATETEXTURESPROC                              glCreateTextures                              = NULL;
PFNGLCREATETRANSFORMFEEDBACKSPROC                    glCreateTransformFeedbacks                    = NULL;
PFNGLCREATEVERTEXARRAYSPROC                          glCreateVertexArrays                          = NULL;
PFNGLCULLFACEPROC                                    glCullFace                                    = NULL;
PFNGLDEBUGMESSAGECALLBACKPROC                        glDebugMessageCallback                        = NULL;
PFNGLDEBUGMESSAGECONTROLPROC                         glDebugMessageControl                         = NULL;
PFNGLDEBUGMESSAGEINSERTPROC                          glDebugMessageInsert                          = NULL;
PFNGLDELETEBUFFERSPROC                               glDeleteBuffers                               = NULL;
PFNGLDELETEFRAMEBUFFERSPROC                          glDeleteFramebuffers                          = NULL;
PFNGLDELETEPROGRAMPROC                               glDeleteProgram                               = NULL;
PFNGLDELETEPROGRAMPIPELINESPROC                      glDeleteProgramPipelines                      = NULL;
PFNGLDELETEQUERIESPROC                               glDeleteQueries                               = NULL;
PFNGLDELETERENDERBUFFERSPROC                         glDeleteRenderbuffers                         = NULL;
PFNGLDELETESAMPLERSPROC                              glDeleteSamplers                              = NULL;
PFNGLDELETESHADERPROC                                glDeleteShader                                = NULL;
PFNGLDELETESYNCPROC                                  glDeleteSync                                  = NULL;
PFNGLDELETETEXTURESPROC                              glDeleteTextures                              = NULL;
PFNGLDELETETRANSFORMFEEDBACKSPROC                    glDeleteTransformFeedbacks                    = NULL;
PFNGLDELETEVERTEXARRAYSPROC                          glDeleteVertexArrays                          = NULL;
PFNGLDEPTHFUNCPROC                                   glDepthFunc                                   = NULL;
PFNGLDEPTHMASKPROC                                   glDepthMask                                   = NULL;
PFNGLDEPTHRANGEPROC                                  glDepthRange                                  = NULL;
PFNGLDEPTHRANGEARRAYVPROC                            glDepthRangeArrayv                            = NULL;
PFNGLDEPTHRANGEINDEXEDPROC                           glDepthRangeIndexed                           = NULL;
PFNGLDEPTHRANGEFPROC                                 glDepthRangef                                 = NULL;
PFNGLDETACHSHADERPROC                                glDetachShader                                = NULL;
PFNGLDISABLEPROC                                     glDisable                                     = NULL;
PFNGLDISABLEVERTEXARRAYATTRIBPROC                    glDisableVertexArrayAttrib                    = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC                    glDisableVertexAttribArray                    = NULL;
PFNGLDISABLEIPROC                                    glDisablei                                    = NULL;
PFNGLDISPATCHCOMPUTEPROC                             glDispatchCompute                             = NULL;
PFNGLDISPATCHCOMPUTEINDIRECTPROC                     glDispatchComputeIndirect                     = NULL;
PFNGLDRAWARRAYSPROC                                  glDrawArrays                                  = NULL;
PFNGLDRAWARRAYSINDIRECTPROC                          glDrawArraysIndirect                          = NULL;
PFNGLDRAWARRAYSINSTANCEDPROC                         glDrawArraysInstanced                         = NULL;
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC             glDrawArraysInstancedBaseInstance             = NULL;
PFNGLDRAWBUFFERPROC                                  glDrawBuffer                                  = NULL;
PFNGLDRAWBUFFERSPROC                                 glDrawBuffers                                 = NULL;
PFNGLDRAWELEMENTSPROC                                glDrawElements                                = NULL;
PFNGLDRAWELEMENTSBASEVERTEXPROC                      glDrawElementsBaseVertex                      = NULL;
PFNGLDRAWELEMENTSINDIRECTPROC                        glDrawElementsIndirect                        = NULL;
PFNGLDRAWELEMENTSINSTANCEDPROC                       glDrawElementsInstanced                       = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC           glDrawElementsInstancedBaseInstance           = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC             glDrawElementsInstancedBaseVertex             = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glDrawElementsInstancedBaseVertexBaseInstance = NULL;
PFNGLDRAWRANGEELEMENTSPROC                           glDrawRangeElements                           = NULL;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC                 glDrawRangeElementsBaseVertex                 = NULL;
PFNGLDRAWTRANSFORMFEEDBACKPROC                       glDrawTransformFeedback                       = NULL;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC              glDrawTransformFeedbackInstanced              = NULL;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC                 glDrawTransformFeedbackStream                 = NULL;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC        glDrawTransformFeedbackStreamInstanced        = NULL;
PFNGLENABLEPROC                                      glEnable                                      = NULL;
PFNGLENABLEVERTEXARRAYATTRIBPROC                     glEnableVertexArrayAttrib                     = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC                     glEnableVertexAttribArray                     = NULL;
PFNGLENABLEIPROC                                     glEnablei                                     = NULL;
PFNGLENDCONDITIONALRENDERPROC                        glEndConditionalRender                        = NULL;
PFNGLENDQUERYPROC                                    glEndQuery                                    = NULL;
PFNGLENDQUERYINDEXEDPROC                             glEndQueryIndexed                             = NULL;
PFNGLENDTRANSFORMFEEDBACKPROC                        glEndTransformFeedback                        = NULL;
PFNGLFENCESYNCPROC                                   glFenceSync                                   = NULL;
PFNGLFINISHPROC                                      glFinish                                      = NULL;
PFNGLFLUSHPROC                                       glFlush                                       = NULL;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC                      glFlushMappedBufferRange                      = NULL;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC                 glFlushMappedNamedBufferRange                 = NULL;
PFNGLFRAMEBUFFERPARAMETERIPROC                       glFramebufferParameteri                       = NULL;
PFNGLFRAMEBUFFERRENDERBUFFERPROC                     glFramebufferRenderbuffer                     = NULL;
PFNGLFRAMEBUFFERTEXTUREPROC                          glFramebufferTexture                          = NULL;
PFNGLFRAMEBUFFERTEXTURE1DPROC                        glFramebufferTexture1D                        = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC                        glFramebufferTexture2D                        = NULL;
PFNGLFRAMEBUFFERTEXTURE3DPROC                        glFramebufferTexture3D                        = NULL;
PFNGLFRAMEBUFFERTEXTURELAYERPROC                     glFramebufferTextureLayer                     = NULL;
PFNGLFRONTFACEPROC                                   glFrontFace                                   = NULL;
PFNGLGENBUFFERSPROC                                  glGenBuffers                                  = NULL;
PFNGLGENFRAMEBUFFERSPROC                             glGenFramebuffers                             = NULL;
PFNGLGENPROGRAMPIPELINESPROC                         glGenProgramPipelines                         = NULL;
PFNGLGENQUERIESPROC                                  glGenQueries                                  = NULL;
PFNGLGENRENDERBUFFERSPROC                            glGenRenderbuffers                            = NULL;
PFNGLGENSAMPLERSPROC                                 glGenSamplers                                 = NULL;
PFNGLGENTEXTURESPROC                                 glGenTextures                                 = NULL;
PFNGLGENTRANSFORMFEEDBACKSPROC                       glGenTransformFeedbacks                       = NULL;
PFNGLGENVERTEXARRAYSPROC                             glGenVertexArrays                             = NULL;
PFNGLGENERATEMIPMAPPROC                              glGenerateMipmap                              = NULL;
PFNGLGENERATETEXTUREMIPMAPPROC                       glGenerateTextureMipmap                       = NULL;
PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC              glGetActiveAtomicCounterBufferiv              = NULL;
PFNGLGETACTIVEATTRIBPROC                             glGetActiveAttrib                             = NULL;
PFNGLGETACTIVESUBROUTINENAMEPROC                     glGetActiveSubroutineName                     = NULL;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC              glGetActiveSubroutineUniformName              = NULL;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC                glGetActiveSubroutineUniformiv                = NULL;
PFNGLGETACTIVEUNIFORMPROC                            glGetActiveUniform                            = NULL;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC                   glGetActiveUniformBlockName                   = NULL;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC                     glGetActiveUniformBlockiv                     = NULL;
PFNGLGETACTIVEUNIFORMNAMEPROC                        glGetActiveUniformName                        = NULL;
PFNGLGETACTIVEUNIFORMSIVPROC                         glGetActiveUniformsiv                         = NULL;
PFNGLGETATTACHEDSHADERSPROC                          glGetAttachedShaders                          = NULL;
PFNGLGETATTRIBLOCATIONPROC                           glGetAttribLocation                           = NULL;
PFNGLGETBOOLEANI_VPROC                               glGetBooleani_v                               = NULL;
PFNGLGETBOOLEANVPROC                                 glGetBooleanv                                 = NULL;
PFNGLGETBUFFERPARAMETERI64VPROC                      glGetBufferParameteri64v                      = NULL;
PFNGLGETBUFFERPARAMETERIVPROC                        glGetBufferParameteriv                        = NULL;
PFNGLGETBUFFERPOINTERVPROC                           glGetBufferPointerv                           = NULL;
PFNGLGETBUFFERSUBDATAPROC                            glGetBufferSubData                            = NULL;
PFNGLGETCOMPRESSEDTEXIMAGEPROC                       glGetCompressedTexImage                       = NULL;
PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC                   glGetCompressedTextureImage                   = NULL;
PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC                glGetCompressedTextureSubImage                = NULL;
PFNGLGETDEBUGMESSAGELOGPROC                          glGetDebugMessageLog                          = NULL;
PFNGLGETDOUBLEI_VPROC                                glGetDoublei_v                                = NULL;
PFNGLGETDOUBLEVPROC                                  glGetDoublev                                  = NULL;
PFNGLGETERRORPROC                                    glGetError                                    = NULL;
PFNGLGETFLOATI_VPROC                                 glGetFloati_v                                 = NULL;
PFNGLGETFLOATVPROC                                   glGetFloatv                                   = NULL;
PFNGLGETFRAGDATAINDEXPROC                            glGetFragDataIndex                            = NULL;
PFNGLGETFRAGDATALOCATIONPROC                         glGetFragDataLocation                         = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC         glGetFramebufferAttachmentParameteriv         = NULL;
PFNGLGETFRAMEBUFFERPARAMETERIVPROC                   glGetFramebufferParameteriv                   = NULL;
PFNGLGETGRAPHICSRESETSTATUSPROC                      glGetGraphicsResetStatus                      = NULL;
PFNGLGETINTEGER64I_VPROC                             glGetInteger64i_v                             = NULL;
PFNGLGETINTEGER64VPROC                               glGetInteger64v                               = NULL;
PFNGLGETINTEGERI_VPROC                               glGetIntegeri_v                               = NULL;
PFNGLGETINTEGERVPROC                                 glGetIntegerv                                 = NULL;
PFNGLGETINTERNALFORMATI64VPROC                       glGetInternalformati64v                       = NULL;
PFNGLGETINTERNALFORMATIVPROC                         glGetInternalformativ                         = NULL;
PFNGLGETMULTISAMPLEFVPROC                            glGetMultisamplefv                            = NULL;
PFNGLGETNAMEDBUFFERPARAMETERI64VPROC                 glGetNamedBufferParameteri64v                 = NULL;
PFNGLGETNAMEDBUFFERPARAMETERIVPROC                   glGetNamedBufferParameteriv                   = NULL;
PFNGLGETNAMEDBUFFERPOINTERVPROC                      glGetNamedBufferPointerv                      = NULL;
PFNGLGETNAMEDBUFFERSUBDATAPROC                       glGetNamedBufferSubData                       = NULL;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC    glGetNamedFramebufferAttachmentParameteriv    = NULL;
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC              glGetNamedFramebufferParameteriv              = NULL;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC             glGetNamedRenderbufferParameteriv             = NULL;
PFNGLGETOBJECTLABELPROC                              glGetObjectLabel                              = NULL;
PFNGLGETOBJECTPTRLABELPROC                           glGetObjectPtrLabel                           = NULL;
PFNGLGETPOINTERVPROC                                 glGetPointerv                                 = NULL;
PFNGLGETPROGRAMBINARYPROC                            glGetProgramBinary                            = NULL;
PFNGLGETPROGRAMINFOLOGPROC                           glGetProgramInfoLog                           = NULL;
PFNGLGETPROGRAMINTERFACEIVPROC                       glGetProgramInterfaceiv                       = NULL;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC                   glGetProgramPipelineInfoLog                   = NULL;
PFNGLGETPROGRAMPIPELINEIVPROC                        glGetProgramPipelineiv                        = NULL;
PFNGLGETPROGRAMRESOURCEINDEXPROC                     glGetProgramResourceIndex                     = NULL;
PFNGLGETPROGRAMRESOURCELOCATIONPROC                  glGetProgramResourceLocation                  = NULL;
PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC             glGetProgramResourceLocationIndex             = NULL;
PFNGLGETPROGRAMRESOURCENAMEPROC                      glGetProgramResourceName                      = NULL;
PFNGLGETPROGRAMRESOURCEIVPROC                        glGetProgramResourceiv                        = NULL;
PFNGLGETPROGRAMSTAGEIVPROC                           glGetProgramStageiv                           = NULL;
PFNGLGETPROGRAMIVPROC                                glGetProgramiv                                = NULL;
PFNGLGETQUERYBUFFEROBJECTI64VPROC                    glGetQueryBufferObjecti64v                    = NULL;
PFNGLGETQUERYBUFFEROBJECTIVPROC                      glGetQueryBufferObjectiv                      = NULL;
PFNGLGETQUERYBUFFEROBJECTUI64VPROC                   glGetQueryBufferObjectui64v                   = NULL;
PFNGLGETQUERYBUFFEROBJECTUIVPROC                     glGetQueryBufferObjectuiv                     = NULL;
PFNGLGETQUERYINDEXEDIVPROC                           glGetQueryIndexediv                           = NULL;
PFNGLGETQUERYOBJECTI64VPROC                          glGetQueryObjecti64v                          = NULL;
PFNGLGETQUERYOBJECTIVPROC                            glGetQueryObjectiv                            = NULL;
PFNGLGETQUERYOBJECTUI64VPROC                         glGetQueryObjectui64v                         = NULL;
PFNGLGETQUERYOBJECTUIVPROC                           glGetQueryObjectuiv                           = NULL;
PFNGLGETQUERYIVPROC                                  glGetQueryiv                                  = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVPROC                  glGetRenderbufferParameteriv                  = NULL;
PFNGLGETSAMPLERPARAMETERIIVPROC                      glGetSamplerParameterIiv                      = NULL;
PFNGLGETSAMPLERPARAMETERIUIVPROC                     glGetSamplerParameterIuiv                     = NULL;
PFNGLGETSAMPLERPARAMETERFVPROC                       glGetSamplerParameterfv                       = NULL;
PFNGLGETSAMPLERPARAMETERIVPROC                       glGetSamplerParameteriv                       = NULL;
PFNGLGETSHADERINFOLOGPROC                            glGetShaderInfoLog                            = NULL;
PFNGLGETSHADERPRECISIONFORMATPROC                    glGetShaderPrecisionFormat                    = NULL;
PFNGLGETSHADERSOURCEPROC                             glGetShaderSource                             = NULL;
PFNGLGETSHADERIVPROC                                 glGetShaderiv                                 = NULL;
PFNGLGETSTRINGPROC                                   glGetString                                   = NULL;
PFNGLGETSTRINGIPROC                                  glGetStringi                                  = NULL;
PFNGLGETSUBROUTINEINDEXPROC                          glGetSubroutineIndex                          = NULL;
PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC                glGetSubroutineUniformLocation                = NULL;
PFNGLGETSYNCIVPROC                                   glGetSynciv                                   = NULL;
PFNGLGETTEXIMAGEPROC                                 glGetTexImage                                 = NULL;
PFNGLGETTEXLEVELPARAMETERFVPROC                      glGetTexLevelParameterfv                      = NULL;
PFNGLGETTEXLEVELPARAMETERIVPROC                      glGetTexLevelParameteriv                      = NULL;
PFNGLGETTEXPARAMETERIIVPROC                          glGetTexParameterIiv                          = NULL;
PFNGLGETTEXPARAMETERIUIVPROC                         glGetTexParameterIuiv                         = NULL;
PFNGLGETTEXPARAMETERFVPROC                           glGetTexParameterfv                           = NULL;
PFNGLGETTEXPARAMETERIVPROC                           glGetTexParameteriv                           = NULL;
PFNGLGETTEXTUREIMAGEPROC                             glGetTextureImage                             = NULL;
PFNGLGETTEXTURELEVELPARAMETERFVPROC                  glGetTextureLevelParameterfv                  = NULL;
PFNGLGETTEXTURELEVELPARAMETERIVPROC                  glGetTextureLevelParameteriv                  = NULL;
PFNGLGETTEXTUREPARAMETERIIVPROC                      glGetTextureParameterIiv                      = NULL;
PFNGLGETTEXTUREPARAMETERIUIVPROC                     glGetTextureParameterIuiv                     = NULL;
PFNGLGETTEXTUREPARAMETERFVPROC                       glGetTextureParameterfv                       = NULL;
PFNGLGETTEXTUREPARAMETERIVPROC                       glGetTextureParameteriv                       = NULL;
PFNGLGETTEXTURESUBIMAGEPROC                          glGetTextureSubImage                          = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC                 glGetTransformFeedbackVarying                 = NULL;
PFNGLGETTRANSFORMFEEDBACKI64_VPROC                   glGetTransformFeedbacki64_v                   = NULL;
PFNGLGETTRANSFORMFEEDBACKI_VPROC                     glGetTransformFeedbacki_v                     = NULL;
PFNGLGETTRANSFORMFEEDBACKIVPROC                      glGetTransformFeedbackiv                      = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC                        glGetUniformBlockIndex                        = NULL;
PFNGLGETUNIFORMINDICESPROC                           glGetUniformIndices                           = NULL;
PFNGLGETUNIFORMLOCATIONPROC                          glGetUniformLocation                          = NULL;
PFNGLGETUNIFORMSUBROUTINEUIVPROC                     glGetUniformSubroutineuiv                     = NULL;
PFNGLGETUNIFORMDVPROC                                glGetUniformdv                                = NULL;
PFNGLGETUNIFORMFVPROC                                glGetUniformfv                                = NULL;
PFNGLGETUNIFORMIVPROC                                glGetUniformiv                                = NULL;
PFNGLGETUNIFORMUIVPROC                               glGetUniformuiv                               = NULL;
PFNGLGETVERTEXARRAYINDEXED64IVPROC                   glGetVertexArrayIndexed64iv                   = NULL;
PFNGLGETVERTEXARRAYINDEXEDIVPROC                     glGetVertexArrayIndexediv                     = NULL;
PFNGLGETVERTEXARRAYIVPROC                            glGetVertexArrayiv                            = NULL;
PFNGLGETVERTEXATTRIBIIVPROC                          glGetVertexAttribIiv                          = NULL;
PFNGLGETVERTEXATTRIBIUIVPROC                         glGetVertexAttribIuiv                         = NULL;
PFNGLGETVERTEXATTRIBLDVPROC                          glGetVertexAttribLdv                          = NULL;
PFNGLGETVERTEXATTRIBPOINTERVPROC                     glGetVertexAttribPointerv                     = NULL;
PFNGLGETVERTEXATTRIBDVPROC                           glGetVertexAttribdv                           = NULL;
PFNGLGETVERTEXATTRIBFVPROC                           glGetVertexAttribfv                           = NULL;
PFNGLGETVERTEXATTRIBIVPROC                           glGetVertexAttribiv                           = NULL;
PFNGLGETNCOLORTABLEPROC                              glGetnColorTable                              = NULL;
PFNGLGETNCOMPRESSEDTEXIMAGEPROC                      glGetnCompressedTexImage                      = NULL;
PFNGLGETNCONVOLUTIONFILTERPROC                       glGetnConvolutionFilter                       = NULL;
PFNGLGETNHISTOGRAMPROC                               glGetnHistogram                               = NULL;
PFNGLGETNMAPDVPROC                                   glGetnMapdv                                   = NULL;
PFNGLGETNMAPFVPROC                                   glGetnMapfv                                   = NULL;
PFNGLGETNMAPIVPROC                                   glGetnMapiv                                   = NULL;
PFNGLGETNMINMAXPROC                                  glGetnMinmax                                  = NULL;
PFNGLGETNPIXELMAPFVPROC                              glGetnPixelMapfv                              = NULL;
PFNGLGETNPIXELMAPUIVPROC                             glGetnPixelMapuiv                             = NULL;
PFNGLGETNPIXELMAPUSVPROC                             glGetnPixelMapusv                             = NULL;
PFNGLGETNPOLYGONSTIPPLEPROC                          glGetnPolygonStipple                          = NULL;
PFNGLGETNSEPARABLEFILTERPROC                         glGetnSeparableFilter                         = NULL;
PFNGLGETNTEXIMAGEPROC                                glGetnTexImage                                = NULL;
PFNGLGETNUNIFORMDVPROC                               glGetnUniformdv                               = NULL;
PFNGLGETNUNIFORMFVPROC                               glGetnUniformfv                               = NULL;
PFNGLGETNUNIFORMIVPROC                               glGetnUniformiv                               = NULL;
PFNGLGETNUNIFORMUIVPROC                              glGetnUniformuiv                              = NULL;
PFNGLHINTPROC                                        glHint                                        = NULL;
PFNGLINVALIDATEBUFFERDATAPROC                        glInvalidateBufferData                        = NULL;
PFNGLINVALIDATEBUFFERSUBDATAPROC                     glInvalidateBufferSubData                     = NULL;
PFNGLINVALIDATEFRAMEBUFFERPROC                       glInvalidateFramebuffer                       = NULL;
PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC              glInvalidateNamedFramebufferData              = NULL;
PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC           glInvalidateNamedFramebufferSubData           = NULL;
PFNGLINVALIDATESUBFRAMEBUFFERPROC                    glInvalidateSubFramebuffer                    = NULL;
PFNGLINVALIDATETEXIMAGEPROC                          glInvalidateTexImage                          = NULL;
PFNGLINVALIDATETEXSUBIMAGEPROC                       glInvalidateTexSubImage                       = NULL;
PFNGLISBUFFERPROC                                    glIsBuffer                                    = NULL;
PFNGLISENABLEDPROC                                   glIsEnabled                                   = NULL;
PFNGLISENABLEDIPROC                                  glIsEnabledi                                  = NULL;
PFNGLISFRAMEBUFFERPROC                               glIsFramebuffer                               = NULL;
PFNGLISPROGRAMPROC                                   glIsProgram                                   = NULL;
PFNGLISPROGRAMPIPELINEPROC                           glIsProgramPipeline                           = NULL;
PFNGLISQUERYPROC                                     glIsQuery                                     = NULL;
PFNGLISRENDERBUFFERPROC                              glIsRenderbuffer                              = NULL;
PFNGLISSAMPLERPROC                                   glIsSampler                                   = NULL;
PFNGLISSHADERPROC                                    glIsShader                                    = NULL;
PFNGLISSYNCPROC                                      glIsSync                                      = NULL;
PFNGLISTEXTUREPROC                                   glIsTexture                                   = NULL;
PFNGLISTRANSFORMFEEDBACKPROC                         glIsTransformFeedback                         = NULL;
PFNGLISVERTEXARRAYPROC                               glIsVertexArray                               = NULL;
PFNGLLINEWIDTHPROC                                   glLineWidth                                   = NULL;
PFNGLLINKPROGRAMPROC                                 glLinkProgram                                 = NULL;
PFNGLLOGICOPPROC                                     glLogicOp                                     = NULL;
PFNGLMAPBUFFERPROC                                   glMapBuffer                                   = NULL;
PFNGLMAPBUFFERRANGEPROC                              glMapBufferRange                              = NULL;
PFNGLMAPNAMEDBUFFERPROC                              glMapNamedBuffer                              = NULL;
PFNGLMAPNAMEDBUFFERRANGEPROC                         glMapNamedBufferRange                         = NULL;
PFNGLMEMORYBARRIERPROC                               glMemoryBarrier                               = NULL;
PFNGLMEMORYBARRIERBYREGIONPROC                       glMemoryBarrierByRegion                       = NULL;
PFNGLMINSAMPLESHADINGPROC                            glMinSampleShading                            = NULL;
PFNGLMULTIDRAWARRAYSPROC                             glMultiDrawArrays                             = NULL;
PFNGLMULTIDRAWARRAYSINDIRECTPROC                     glMultiDrawArraysIndirect                     = NULL;
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC                glMultiDrawArraysIndirectCount                = NULL;
PFNGLMULTIDRAWELEMENTSPROC                           glMultiDrawElements                           = NULL;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC                 glMultiDrawElementsBaseVertex                 = NULL;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC                   glMultiDrawElementsIndirect                   = NULL;
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC              glMultiDrawElementsIndirectCount              = NULL;
PFNGLMULTITEXCOORDP1UIPROC                           glMultiTexCoordP1ui                           = NULL;
PFNGLMULTITEXCOORDP1UIVPROC                          glMultiTexCoordP1uiv                          = NULL;
PFNGLMULTITEXCOORDP2UIPROC                           glMultiTexCoordP2ui                           = NULL;
PFNGLMULTITEXCOORDP2UIVPROC                          glMultiTexCoordP2uiv                          = NULL;
PFNGLMULTITEXCOORDP3UIPROC                           glMultiTexCoordP3ui                           = NULL;
PFNGLMULTITEXCOORDP3UIVPROC                          glMultiTexCoordP3uiv                          = NULL;
PFNGLMULTITEXCOORDP4UIPROC                           glMultiTexCoordP4ui                           = NULL;
PFNGLMULTITEXCOORDP4UIVPROC                          glMultiTexCoordP4uiv                          = NULL;
PFNGLNAMEDBUFFERDATAPROC                             glNamedBufferData                             = NULL;
PFNGLNAMEDBUFFERSTORAGEPROC                          glNamedBufferStorage                          = NULL;
PFNGLNAMEDBUFFERSUBDATAPROC                          glNamedBufferSubData                          = NULL;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC                  glNamedFramebufferDrawBuffer                  = NULL;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC                 glNamedFramebufferDrawBuffers                 = NULL;
PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC                  glNamedFramebufferParameteri                  = NULL;
PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC                  glNamedFramebufferReadBuffer                  = NULL;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC                glNamedFramebufferRenderbuffer                = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC                     glNamedFramebufferTexture                     = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC                glNamedFramebufferTextureLayer                = NULL;
PFNGLNAMEDRENDERBUFFERSTORAGEPROC                    glNamedRenderbufferStorage                    = NULL;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC         glNamedRenderbufferStorageMultisample         = NULL;
PFNGLNORMALP3UIPROC                                  glNormalP3ui                                  = NULL;
PFNGLNORMALP3UIVPROC                                 glNormalP3uiv                                 = NULL;
PFNGLOBJECTLABELPROC                                 glObjectLabel                                 = NULL;
PFNGLOBJECTPTRLABELPROC                              glObjectPtrLabel                              = NULL;
PFNGLPATCHPARAMETERFVPROC                            glPatchParameterfv                            = NULL;
PFNGLPATCHPARAMETERIPROC                             glPatchParameteri                             = NULL;
PFNGLPAUSETRANSFORMFEEDBACKPROC                      glPauseTransformFeedback                      = NULL;
PFNGLPIXELSTOREFPROC                                 glPixelStoref                                 = NULL;
PFNGLPIXELSTOREIPROC                                 glPixelStorei                                 = NULL;
PFNGLPOINTPARAMETERFPROC                             glPointParameterf                             = NULL;
PFNGLPOINTPARAMETERFVPROC                            glPointParameterfv                            = NULL;
PFNGLPOINTPARAMETERIPROC                             glPointParameteri                             = NULL;
PFNGLPOINTPARAMETERIVPROC                            glPointParameteriv                            = NULL;
PFNGLPOINTSIZEPROC                                   glPointSize                                   = NULL;
PFNGLPOLYGONMODEPROC                                 glPolygonMode                                 = NULL;
PFNGLPOLYGONOFFSETPROC                               glPolygonOffset                               = NULL;
PFNGLPOLYGONOFFSETCLAMPPROC                          glPolygonOffsetClamp                          = NULL;
PFNGLPOPDEBUGGROUPPROC                               glPopDebugGroup                               = NULL;
PFNGLPRIMITIVERESTARTINDEXPROC                       glPrimitiveRestartIndex                       = NULL;
PFNGLPROGRAMBINARYPROC                               glProgramBinary                               = NULL;
PFNGLPROGRAMPARAMETERIPROC                           glProgramParameteri                           = NULL;
PFNGLPROGRAMUNIFORM1DPROC                            glProgramUniform1d                            = NULL;
PFNGLPROGRAMUNIFORM1DVPROC                           glProgramUniform1dv                           = NULL;
PFNGLPROGRAMUNIFORM1FPROC                            glProgramUniform1f                            = NULL;
PFNGLPROGRAMUNIFORM1FVPROC                           glProgramUniform1fv                           = NULL;
PFNGLPROGRAMUNIFORM1IPROC                            glProgramUniform1i                            = NULL;
PFNGLPROGRAMUNIFORM1IVPROC                           glProgramUniform1iv                           = NULL;
PFNGLPROGRAMUNIFORM1UIPROC                           glProgramUniform1ui                           = NULL;
PFNGLPROGRAMUNIFORM1UIVPROC                          glProgramUniform1uiv                          = NULL;
PFNGLPROGRAMUNIFORM2DPROC                            glProgramUniform2d                            = NULL;
PFNGLPROGRAMUNIFORM2DVPROC                           glProgramUniform2dv                           = NULL;
PFNGLPROGRAMUNIFORM2FPROC                            glProgramUniform2f                            = NULL;
PFNGLPROGRAMUNIFORM2FVPROC                           glProgramUniform2fv                           = NULL;
PFNGLPROGRAMUNIFORM2IPROC                            glProgramUniform2i                            = NULL;
PFNGLPROGRAMUNIFORM2IVPROC                           glProgramUniform2iv                           = NULL;
PFNGLPROGRAMUNIFORM2UIPROC                           glProgramUniform2ui                           = NULL;
PFNGLPROGRAMUNIFORM2UIVPROC                          glProgramUniform2uiv                          = NULL;
PFNGLPROGRAMUNIFORM3DPROC                            glProgramUniform3d                            = NULL;
PFNGLPROGRAMUNIFORM3DVPROC                           glProgramUniform3dv                           = NULL;
PFNGLPROGRAMUNIFORM3FPROC                            glProgramUniform3f                            = NULL;
PFNGLPROGRAMUNIFORM3FVPROC                           glProgramUniform3fv                           = NULL;
PFNGLPROGRAMUNIFORM3IPROC                            glProgramUniform3i                            = NULL;
PFNGLPROGRAMUNIFORM3IVPROC                           glProgramUniform3iv                           = NULL;
PFNGLPROGRAMUNIFORM3UIPROC                           glProgramUniform3ui                           = NULL;
PFNGLPROGRAMUNIFORM3UIVPROC                          glProgramUniform3uiv                          = NULL;
PFNGLPROGRAMUNIFORM4DPROC                            glProgramUniform4d                            = NULL;
PFNGLPROGRAMUNIFORM4DVPROC                           glProgramUniform4dv                           = NULL;
PFNGLPROGRAMUNIFORM4FPROC                            glProgramUniform4f                            = NULL;
PFNGLPROGRAMUNIFORM4FVPROC                           glProgramUniform4fv                           = NULL;
PFNGLPROGRAMUNIFORM4IPROC                            glProgramUniform4i                            = NULL;
PFNGLPROGRAMUNIFORM4IVPROC                           glProgramUniform4iv                           = NULL;
PFNGLPROGRAMUNIFORM4UIPROC                           glProgramUniform4ui                           = NULL;
PFNGLPROGRAMUNIFORM4UIVPROC                          glProgramUniform4uiv                          = NULL;
PFNGLPROGRAMUNIFORMMATRIX2DVPROC                     glProgramUniformMatrix2dv                     = NULL;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC                     glProgramUniformMatrix2fv                     = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC                   glProgramUniformMatrix2x3dv                   = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC                   glProgramUniformMatrix2x3fv                   = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC                   glProgramUniformMatrix2x4dv                   = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC                   glProgramUniformMatrix2x4fv                   = NULL;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC                     glProgramUniformMatrix3dv                     = NULL;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC                     glProgramUniformMatrix3fv                     = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC                   glProgramUniformMatrix3x2dv                   = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC                   glProgramUniformMatrix3x2fv                   = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC                   glProgramUniformMatrix3x4dv                   = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC                   glProgramUniformMatrix3x4fv                   = NULL;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC                     glProgramUniformMatrix4dv                     = NULL;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC                     glProgramUniformMatrix4fv                     = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC                   glProgramUniformMatrix4x2dv                   = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC                   glProgramUniformMatrix4x2fv                   = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC                   glProgramUniformMatrix4x3dv                   = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC                   glProgramUniformMatrix4x3fv                   = NULL;
PFNGLPROVOKINGVERTEXPROC                             glProvokingVertex                             = NULL;
PFNGLPUSHDEBUGGROUPPROC                              glPushDebugGroup                              = NULL;
PFNGLQUERYCOUNTERPROC                                glQueryCounter                                = NULL;
PFNGLREADBUFFERPROC                                  glReadBuffer                                  = NULL;
PFNGLREADPIXELSPROC                                  glReadPixels                                  = NULL;
PFNGLREADNPIXELSPROC                                 glReadnPixels                                 = NULL;
PFNGLRELEASESHADERCOMPILERPROC                       glReleaseShaderCompiler                       = NULL;
PFNGLRENDERBUFFERSTORAGEPROC                         glRenderbufferStorage                         = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC              glRenderbufferStorageMultisample              = NULL;
PFNGLRESUMETRANSFORMFEEDBACKPROC                     glResumeTransformFeedback                     = NULL;
PFNGLSAMPLECOVERAGEPROC                              glSampleCoverage                              = NULL;
PFNGLSAMPLEMASKIPROC                                 glSampleMaski                                 = NULL;
PFNGLSAMPLERPARAMETERIIVPROC                         glSamplerParameterIiv                         = NULL;
PFNGLSAMPLERPARAMETERIUIVPROC                        glSamplerParameterIuiv                        = NULL;
PFNGLSAMPLERPARAMETERFPROC                           glSamplerParameterf                           = NULL;
PFNGLSAMPLERPARAMETERFVPROC                          glSamplerParameterfv                          = NULL;
PFNGLSAMPLERPARAMETERIPROC                           glSamplerParameteri                           = NULL;
PFNGLSAMPLERPARAMETERIVPROC                          glSamplerParameteriv                          = NULL;
PFNGLSCISSORPROC                                     glScissor                                     = NULL;
PFNGLSCISSORARRAYVPROC                               glScissorArrayv                               = NULL;
PFNGLSCISSORINDEXEDPROC                              glScissorIndexed                              = NULL;
PFNGLSCISSORINDEXEDVPROC                             glScissorIndexedv                             = NULL;
PFNGLSECONDARYCOLORP3UIPROC                          glSecondaryColorP3ui                          = NULL;
PFNGLSECONDARYCOLORP3UIVPROC                         glSecondaryColorP3uiv                         = NULL;
PFNGLSHADERBINARYPROC                                glShaderBinary                                = NULL;
PFNGLSHADERSOURCEPROC                                glShaderSource                                = NULL;
PFNGLSHADERSTORAGEBLOCKBINDINGPROC                   glShaderStorageBlockBinding                   = NULL;
PFNGLSPECIALIZESHADERPROC                            glSpecializeShader                            = NULL;
PFNGLSTENCILFUNCPROC                                 glStencilFunc                                 = NULL;
PFNGLSTENCILFUNCSEPARATEPROC                         glStencilFuncSeparate                         = NULL;
PFNGLSTENCILMASKPROC                                 glStencilMask                                 = NULL;
PFNGLSTENCILMASKSEPARATEPROC                         glStencilMaskSeparate                         = NULL;
PFNGLSTENCILOPPROC                                   glStencilOp                                   = NULL;
PFNGLSTENCILOPSEPARATEPROC                           glStencilOpSeparate                           = NULL;
PFNGLTEXBUFFERPROC                                   glTexBuffer                                   = NULL;
PFNGLTEXBUFFERRANGEPROC                              glTexBufferRange                              = NULL;
PFNGLTEXCOORDP1UIPROC                                glTexCoordP1ui                                = NULL;
PFNGLTEXCOORDP1UIVPROC                               glTexCoordP1uiv                               = NULL;
PFNGLTEXCOORDP2UIPROC                                glTexCoordP2ui                                = NULL;
PFNGLTEXCOORDP2UIVPROC                               glTexCoordP2uiv                               = NULL;
PFNGLTEXCOORDP3UIPROC                                glTexCoordP3ui                                = NULL;
PFNGLTEXCOORDP3UIVPROC                               glTexCoordP3uiv                               = NULL;
PFNGLTEXCOORDP4UIPROC                                glTexCoordP4ui                                = NULL;
PFNGLTEXCOORDP4UIVPROC                               glTexCoordP4uiv                               = NULL;
PFNGLTEXIMAGE1DPROC                                  glTexImage1D                                  = NULL;
PFNGLTEXIMAGE2DPROC                                  glTexImage2D                                  = NULL;
PFNGLTEXIMAGE2DMULTISAMPLEPROC                       glTexImage2DMultisample                       = NULL;
PFNGLTEXIMAGE3DPROC                                  glTexImage3D                                  = NULL;
PFNGLTEXIMAGE3DMULTISAMPLEPROC                       glTexImage3DMultisample                       = NULL;
PFNGLTEXPARAMETERIIVPROC                             glTexParameterIiv                             = NULL;
PFNGLTEXPARAMETERIUIVPROC                            glTexParameterIuiv                            = NULL;
PFNGLTEXPARAMETERFPROC                               glTexParameterf                               = NULL;
PFNGLTEXPARAMETERFVPROC                              glTexParameterfv                              = NULL;
PFNGLTEXPARAMETERIPROC                               glTexParameteri                               = NULL;
PFNGLTEXPARAMETERIVPROC                              glTexParameteriv                              = NULL;
PFNGLTEXSTORAGE1DPROC                                glTexStorage1D                                = NULL;
PFNGLTEXSTORAGE2DPROC                                glTexStorage2D                                = NULL;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC                     glTexStorage2DMultisample                     = NULL;
PFNGLTEXSTORAGE3DPROC                                glTexStorage3D                                = NULL;
PFNGLTEXSTORAGE3DMULTISAMPLEPROC                     glTexStorage3DMultisample                     = NULL;
PFNGLTEXSUBIMAGE1DPROC                               glTexSubImage1D                               = NULL;
PFNGLTEXSUBIMAGE2DPROC                               glTexSubImage2D                               = NULL;
PFNGLTEXSUBIMAGE3DPROC                               glTexSubImage3D                               = NULL;
PFNGLTEXTUREBARRIERPROC                              glTextureBarrier                              = NULL;
PFNGLTEXTUREBUFFERPROC                               glTextureBuffer                               = NULL;
PFNGLTEXTUREBUFFERRANGEPROC                          glTextureBufferRange                          = NULL;
PFNGLTEXTUREPARAMETERIIVPROC                         glTextureParameterIiv                         = NULL;
PFNGLTEXTUREPARAMETERIUIVPROC                        glTextureParameterIuiv                        = NULL;
PFNGLTEXTUREPARAMETERFPROC                           glTextureParameterf                           = NULL;
PFNGLTEXTUREPARAMETERFVPROC                          glTextureParameterfv                          = NULL;
PFNGLTEXTUREPARAMETERIPROC                           glTextureParameteri                           = NULL;
PFNGLTEXTUREPARAMETERIVPROC                          glTextureParameteriv                          = NULL;
PFNGLTEXTURESTORAGE1DPROC                            glTextureStorage1D                            = NULL;
PFNGLTEXTURESTORAGE2DPROC                            glTextureStorage2D                            = NULL;
PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC                 glTextureStorage2DMultisample                 = NULL;
PFNGLTEXTURESTORAGE3DPROC                            glTextureStorage3D                            = NULL;
PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC                 glTextureStorage3DMultisample                 = NULL;
PFNGLTEXTURESUBIMAGE1DPROC                           glTextureSubImage1D                           = NULL;
PFNGLTEXTURESUBIMAGE2DPROC                           glTextureSubImage2D                           = NULL;
PFNGLTEXTURESUBIMAGE3DPROC                           glTextureSubImage3D                           = NULL;
PFNGLTEXTUREVIEWPROC                                 glTextureView                                 = NULL;
PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC                 glTransformFeedbackBufferBase                 = NULL;
PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC                glTransformFeedbackBufferRange                = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC                   glTransformFeedbackVaryings                   = NULL;
PFNGLUNIFORM1DPROC                                   glUniform1d                                   = NULL;
PFNGLUNIFORM1DVPROC                                  glUniform1dv                                  = NULL;
PFNGLUNIFORM1FPROC                                   glUniform1f                                   = NULL;
PFNGLUNIFORM1FVPROC                                  glUniform1fv                                  = NULL;
PFNGLUNIFORM1IPROC                                   glUniform1i                                   = NULL;
PFNGLUNIFORM1IVPROC                                  glUniform1iv                                  = NULL;
PFNGLUNIFORM1UIPROC                                  glUniform1ui                                  = NULL;
PFNGLUNIFORM1UIVPROC                                 glUniform1uiv                                 = NULL;
PFNGLUNIFORM2DPROC                                   glUniform2d                                   = NULL;
PFNGLUNIFORM2DVPROC                                  glUniform2dv                                  = NULL;
PFNGLUNIFORM2FPROC                                   glUniform2f                                   = NULL;
PFNGLUNIFORM2FVPROC                                  glUniform2fv                                  = NULL;
PFNGLUNIFORM2IPROC                                   glUniform2i                                   = NULL;
PFNGLUNIFORM2IVPROC                                  glUniform2iv                                  = NULL;
PFNGLUNIFORM2UIPROC                                  glUniform2ui                                  = NULL;
PFNGLUNIFORM2UIVPROC                                 glUniform2uiv                                 = NULL;
PFNGLUNIFORM3DPROC                                   glUniform3d                                   = NULL;
PFNGLUNIFORM3DVPROC                                  glUniform3dv                                  = NULL;
PFNGLUNIFORM3FPROC                                   glUniform3f                                   = NULL;
PFNGLUNIFORM3FVPROC                                  glUniform3fv                                  = NULL;
PFNGLUNIFORM3IPROC                                   glUniform3i                                   = NULL;
PFNGLUNIFORM3IVPROC                                  glUniform3iv                                  = NULL;
PFNGLUNIFORM3UIPROC                                  glUniform3ui                                  = NULL;
PFNGLUNIFORM3UIVPROC                                 glUniform3uiv                                 = NULL;
PFNGLUNIFORM4DPROC                                   glUniform4d                                   = NULL;
PFNGLUNIFORM4DVPROC                                  glUniform4dv                                  = NULL;
PFNGLUNIFORM4FPROC                                   glUniform4f                                   = NULL;
PFNGLUNIFORM4FVPROC                                  glUniform4fv                                  = NULL;
PFNGLUNIFORM4IPROC                                   glUniform4i                                   = NULL;
PFNGLUNIFORM4IVPROC                                  glUniform4iv                                  = NULL;
PFNGLUNIFORM4UIPROC                                  glUniform4ui                                  = NULL;
PFNGLUNIFORM4UIVPROC                                 glUniform4uiv                                 = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC                         glUniformBlockBinding                         = NULL;
PFNGLUNIFORMMATRIX2DVPROC                            glUniformMatrix2dv                            = NULL;
PFNGLUNIFORMMATRIX2FVPROC                            glUniformMatrix2fv                            = NULL;
PFNGLUNIFORMMATRIX2X3DVPROC                          glUniformMatrix2x3dv                          = NULL;
PFNGLUNIFORMMATRIX2X3FVPROC                          glUniformMatrix2x3fv                          = NULL;
PFNGLUNIFORMMATRIX2X4DVPROC                          glUniformMatrix2x4dv                          = NULL;
PFNGLUNIFORMMATRIX2X4FVPROC                          glUniformMatrix2x4fv                          = NULL;
PFNGLUNIFORMMATRIX3DVPROC                            glUniformMatrix3dv                            = NULL;
PFNGLUNIFORMMATRIX3FVPROC                            glUniformMatrix3fv                            = NULL;
PFNGLUNIFORMMATRIX3X2DVPROC                          glUniformMatrix3x2dv                          = NULL;
PFNGLUNIFORMMATRIX3X2FVPROC                          glUniformMatrix3x2fv                          = NULL;
PFNGLUNIFORMMATRIX3X4DVPROC                          glUniformMatrix3x4dv                          = NULL;
PFNGLUNIFORMMATRIX3X4FVPROC                          glUniformMatrix3x4fv                          = NULL;
PFNGLUNIFORMMATRIX4DVPROC                            glUniformMatrix4dv                            = NULL;
PFNGLUNIFORMMATRIX4FVPROC                            glUniformMatrix4fv                            = NULL;
PFNGLUNIFORMMATRIX4X2DVPROC                          glUniformMatrix4x2dv                          = NULL;
PFNGLUNIFORMMATRIX4X2FVPROC                          glUniformMatrix4x2fv                          = NULL;
PFNGLUNIFORMMATRIX4X3DVPROC                          glUniformMatrix4x3dv                          = NULL;
PFNGLUNIFORMMATRIX4X3FVPROC                          glUniformMatrix4x3fv                          = NULL;
PFNGLUNIFORMSUBROUTINESUIVPROC                       glUniformSubroutinesuiv                       = NULL;
PFNGLUNMAPBUFFERPROC                                 glUnmapBuffer                                 = NULL;
PFNGLUNMAPNAMEDBUFFERPROC                            glUnmapNamedBuffer                            = NULL;
PFNGLUSEPROGRAMPROC                                  glUseProgram                                  = NULL;
PFNGLUSEPROGRAMSTAGESPROC                            glUseProgramStages                            = NULL;
PFNGLVALIDATEPROGRAMPROC                             glValidateProgram                             = NULL;
PFNGLVALIDATEPROGRAMPIPELINEPROC                     glValidateProgramPipeline                     = NULL;
PFNGLVERTEXARRAYATTRIBBINDINGPROC                    glVertexArrayAttribBinding                    = NULL;
PFNGLVERTEXARRAYATTRIBFORMATPROC                     glVertexArrayAttribFormat                     = NULL;
PFNGLVERTEXARRAYATTRIBIFORMATPROC                    glVertexArrayAttribIFormat                    = NULL;
PFNGLVERTEXARRAYATTRIBLFORMATPROC                    glVertexArrayAttribLFormat                    = NULL;
PFNGLVERTEXARRAYBINDINGDIVISORPROC                   glVertexArrayBindingDivisor                   = NULL;
PFNGLVERTEXARRAYELEMENTBUFFERPROC                    glVertexArrayElementBuffer                    = NULL;
PFNGLVERTEXARRAYVERTEXBUFFERPROC                     glVertexArrayVertexBuffer                     = NULL;
PFNGLVERTEXARRAYVERTEXBUFFERSPROC                    glVertexArrayVertexBuffers                    = NULL;
PFNGLVERTEXATTRIB1DPROC                              glVertexAttrib1d                              = NULL;
PFNGLVERTEXATTRIB1DVPROC                             glVertexAttrib1dv                             = NULL;
PFNGLVERTEXATTRIB1FPROC                              glVertexAttrib1f                              = NULL;
PFNGLVERTEXATTRIB1FVPROC                             glVertexAttrib1fv                             = NULL;
PFNGLVERTEXATTRIB1SPROC                              glVertexAttrib1s                              = NULL;
PFNGLVERTEXATTRIB1SVPROC                             glVertexAttrib1sv                             = NULL;
PFNGLVERTEXATTRIB2DPROC                              glVertexAttrib2d                              = NULL;
PFNGLVERTEXATTRIB2DVPROC                             glVertexAttrib2dv                             = NULL;
PFNGLVERTEXATTRIB2FPROC                              glVertexAttrib2f                              = NULL;
PFNGLVERTEXATTRIB2FVPROC                             glVertexAttrib2fv                             = NULL;
PFNGLVERTEXATTRIB2SPROC                              glVertexAttrib2s                              = NULL;
PFNGLVERTEXATTRIB2SVPROC                             glVertexAttrib2sv                             = NULL;
PFNGLVERTEXATTRIB3DPROC                              glVertexAttrib3d                              = NULL;
PFNGLVERTEXATTRIB3DVPROC                             glVertexAttrib3dv                             = NULL;
PFNGLVERTEXATTRIB3FPROC                              glVertexAttrib3f                              = NULL;
PFNGLVERTEXATTRIB3FVPROC                             glVertexAttrib3fv                             = NULL;
PFNGLVERTEXATTRIB3SPROC                              glVertexAttrib3s                              = NULL;
PFNGLVERTEXATTRIB3SVPROC                             glVertexAttrib3sv                             = NULL;
PFNGLVERTEXATTRIB4NBVPROC                            glVertexAttrib4Nbv                            = NULL;
PFNGLVERTEXATTRIB4NIVPROC                            glVertexAttrib4Niv                            = NULL;
PFNGLVERTEXATTRIB4NSVPROC                            glVertexAttrib4Nsv                            = NULL;
PFNGLVERTEXATTRIB4NUBPROC                            glVertexAttrib4Nub                            = NULL;
PFNGLVERTEXATTRIB4NUBVPROC                           glVertexAttrib4Nubv                           = NULL;
PFNGLVERTEXATTRIB4NUIVPROC                           glVertexAttrib4Nuiv                           = NULL;
PFNGLVERTEXATTRIB4NUSVPROC                           glVertexAttrib4Nusv                           = NULL;
PFNGLVERTEXATTRIB4BVPROC                             glVertexAttrib4bv                             = NULL;
PFNGLVERTEXATTRIB4DPROC                              glVertexAttrib4d                              = NULL;
PFNGLVERTEXATTRIB4DVPROC                             glVertexAttrib4dv                             = NULL;
PFNGLVERTEXATTRIB4FPROC                              glVertexAttrib4f                              = NULL;
PFNGLVERTEXATTRIB4FVPROC                             glVertexAttrib4fv                             = NULL;
PFNGLVERTEXATTRIB4IVPROC                             glVertexAttrib4iv                             = NULL;
PFNGLVERTEXATTRIB4SPROC                              glVertexAttrib4s                              = NULL;
PFNGLVERTEXATTRIB4SVPROC                             glVertexAttrib4sv                             = NULL;
PFNGLVERTEXATTRIB4UBVPROC                            glVertexAttrib4ubv                            = NULL;
PFNGLVERTEXATTRIB4UIVPROC                            glVertexAttrib4uiv                            = NULL;
PFNGLVERTEXATTRIB4USVPROC                            glVertexAttrib4usv                            = NULL;
PFNGLVERTEXATTRIBBINDINGPROC                         glVertexAttribBinding                         = NULL;
PFNGLVERTEXATTRIBDIVISORPROC                         glVertexAttribDivisor                         = NULL;
PFNGLVERTEXATTRIBFORMATPROC                          glVertexAttribFormat                          = NULL;
PFNGLVERTEXATTRIBI1IPROC                             glVertexAttribI1i                             = NULL;
PFNGLVERTEXATTRIBI1IVPROC                            glVertexAttribI1iv                            = NULL;
PFNGLVERTEXATTRIBI1UIPROC                            glVertexAttribI1ui                            = NULL;
PFNGLVERTEXATTRIBI1UIVPROC                           glVertexAttribI1uiv                           = NULL;
PFNGLVERTEXATTRIBI2IPROC                             glVertexAttribI2i                             = NULL;
PFNGLVERTEXATTRIBI2IVPROC                            glVertexAttribI2iv                            = NULL;
PFNGLVERTEXATTRIBI2UIPROC                            glVertexAttribI2ui                            = NULL;
PFNGLVERTEXATTRIBI2UIVPROC                           glVertexAttribI2uiv                           = NULL;
PFNGLVERTEXATTRIBI3IPROC                             glVertexAttribI3i                             = NULL;
PFNGLVERTEXATTRIBI3IVPROC                            glVertexAttribI3iv                            = NULL;
PFNGLVERTEXATTRIBI3UIPROC                            glVertexAttribI3ui                            = NULL;
PFNGLVERTEXATTRIBI3UIVPROC                           glVertexAttribI3uiv                           = NULL;
PFNGLVERTEXATTRIBI4BVPROC                            glVertexAttribI4bv                            = NULL;
PFNGLVERTEXATTRIBI4IPROC                             glVertexAttribI4i                             = NULL;
PFNGLVERTEXATTRIBI4IVPROC                            glVertexAttribI4iv                            = NULL;
PFNGLVERTEXATTRIBI4SVPROC                            glVertexAttribI4sv                            = NULL;
PFNGLVERTEXATTRIBI4UBVPROC                           glVertexAttribI4ubv                           = NULL;
PFNGLVERTEXATTRIBI4UIPROC                            glVertexAttribI4ui                            = NULL;
PFNGLVERTEXATTRIBI4UIVPROC                           glVertexAttribI4uiv                           = NULL;
PFNGLVERTEXATTRIBI4USVPROC                           glVertexAttribI4usv                           = NULL;
PFNGLVERTEXATTRIBIFORMATPROC                         glVertexAttribIFormat                         = NULL;
PFNGLVERTEXATTRIBIPOINTERPROC                        glVertexAttribIPointer                        = NULL;
PFNGLVERTEXATTRIBL1DPROC                             glVertexAttribL1d                             = NULL;
PFNGLVERTEXATTRIBL1DVPROC                            glVertexAttribL1dv                            = NULL;
PFNGLVERTEXATTRIBL2DPROC                             glVertexAttribL2d                             = NULL;
PFNGLVERTEXATTRIBL2DVPROC                            glVertexAttribL2dv                            = NULL;
PFNGLVERTEXATTRIBL3DPROC                             glVertexAttribL3d                             = NULL;
PFNGLVERTEXATTRIBL3DVPROC                            glVertexAttribL3dv                            = NULL;
PFNGLVERTEXATTRIBL4DPROC                             glVertexAttribL4d                             = NULL;
PFNGLVERTEXATTRIBL4DVPROC                            glVertexAttribL4dv                            = NULL;
PFNGLVERTEXATTRIBLFORMATPROC                         glVertexAttribLFormat                         = NULL;
PFNGLVERTEXATTRIBLPOINTERPROC                        glVertexAttribLPointer                        = NULL;
PFNGLVERTEXATTRIBP1UIPROC                            glVertexAttribP1ui                            = NULL;
PFNGLVERTEXATTRIBP1UIVPROC                           glVertexAttribP1uiv                           = NULL;
PFNGLVERTEXATTRIBP2UIPROC                            glVertexAttribP2ui                            = NULL;
PFNGLVERTEXATTRIBP2UIVPROC                           glVertexAttribP2uiv                           = NULL;
PFNGLVERTEXATTRIBP3UIPROC                            glVertexAttribP3ui                            = NULL;
PFNGLVERTEXATTRIBP3UIVPROC                           glVertexAttribP3uiv                           = NULL;
PFNGLVERTEXATTRIBP4UIPROC                            glVertexAttribP4ui                            = NULL;
PFNGLVERTEXATTRIBP4UIVPROC                           glVertexAttribP4uiv                           = NULL;
PFNGLVERTEXATTRIBPOINTERPROC                         glVertexAttribPointer                         = NULL;
PFNGLVERTEXBINDINGDIVISORPROC                        glVertexBindingDivisor                        = NULL;
PFNGLVERTEXP2UIPROC                                  glVertexP2ui                                  = NULL;
PFNGLVERTEXP2UIVPROC                                 glVertexP2uiv                                 = NULL;
PFNGLVERTEXP3UIPROC                                  glVertexP3ui                                  = NULL;
PFNGLVERTEXP3UIVPROC                                 glVertexP3uiv                                 = NULL;
PFNGLVERTEXP4UIPROC                                  glVertexP4ui                                  = NULL;
PFNGLVERTEXP4UIVPROC                                 glVertexP4uiv                                 = NULL;
PFNGLVIEWPORTPROC                                    glViewport                                    = NULL;
PFNGLVIEWPORTARRAYVPROC                              glViewportArrayv                              = NULL;
PFNGLVIEWPORTINDEXEDFPROC                            glViewportIndexedf                            = NULL;
PFNGLVIEWPORTINDEXEDFVPROC                           glViewportIndexedfv                           = NULL;
PFNGLWAITSYNCPROC                                    glWaitSync                                    = NULL;

int OGL_VERSION_MAJOR = 0;
int OGL_VERSION_MINOR = 0;
int OGL_VERSION_1_0   = 0;
int OGL_VERSION_1_1   = 0;
int OGL_VERSION_1_2   = 0;
int OGL_VERSION_1_3   = 0;
int OGL_VERSION_1_4   = 0;
int OGL_VERSION_1_5   = 0;
int OGL_VERSION_2_0   = 0;
int OGL_VERSION_2_1   = 0;
int OGL_VERSION_3_0   = 0;
int OGL_VERSION_3_1   = 0;
int OGL_VERSION_3_2   = 0;
int OGL_VERSION_3_3   = 0;
int OGL_VERSION_4_0   = 0;
int OGL_VERSION_4_1   = 0;
int OGL_VERSION_4_2   = 0;
int OGL_VERSION_4_3   = 0;
int OGL_VERSION_4_4   = 0;
int OGL_VERSION_4_5   = 0;
int OGL_VERSION_4_6   = 0;

bool OGL_LOADED_CORE = false;

#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>

static bool load_base() {
  if (OGL_LOADED_CORE) return true;
  // load core functions
  glGetString = reinterpret_cast<PFNGLGETSTRINGPROC>(::glGetProcAddress("glGetString"));
  if (!glGetString) return false;
  glGetIntegerv = reinterpret_cast<PFNGLGETINTEGERVPROC>(::glGetProcAddress("glGetIntegerv"));
  if (!glGetIntegerv) return false;
  glGetStringi = reinterpret_cast<PFNGLGETSTRINGIPROC>(::glGetProcAddress("glGetStringi"));
  if (!glGetStringi) return false;
  // done
  return (OGL_LOADED_CORE = true);
}

static bool load_v_1_0() {
  if (!OGL_VERSION_1_0) return false;
  glLoadIdentity           = (PFNGLLOADIDENTITYPROC) ::glGetProcAddress("glLoadIdentity");
  glOrtho                  = (PFNGLORTHOPROC) ::glGetProcAddress("glOrtho");
  glMatrixMode             = (PFNGLMATRIXMODEPROC) ::glGetProcAddress("glMatrixMode");
  glBegin                  = (PFNGLBEGINPROC) ::glGetProcAddress("glBegin");
  glEnd                    = (PFNGLENDPROC) ::glGetProcAddress("glEnd");
  glColor3f                = (PFNGLCOLOR3FPROC) ::glGetProcAddress("glColor3f");
  glVertex3f               = (PFNGLVERTEX3FPROC) ::glGetProcAddress("glVertex3f");
  glCullFace               = (PFNGLCULLFACEPROC) ::glGetProcAddress("glCullFace");
  glFrontFace              = (PFNGLFRONTFACEPROC) ::glGetProcAddress("glFrontFace");
  glHint                   = (PFNGLHINTPROC) ::glGetProcAddress("glHint");
  glLineWidth              = (PFNGLLINEWIDTHPROC) ::glGetProcAddress("glLineWidth");
  glPointSize              = (PFNGLPOINTSIZEPROC) ::glGetProcAddress("glPointSize");
  glPolygonMode            = (PFNGLPOLYGONMODEPROC) ::glGetProcAddress("glPolygonMode");
  glScissor                = (PFNGLSCISSORPROC) ::glGetProcAddress("glScissor");
  glTexParameterf          = (PFNGLTEXPARAMETERFPROC) ::glGetProcAddress("glTexParameterf");
  glTexParameterfv         = (PFNGLTEXPARAMETERFVPROC) ::glGetProcAddress("glTexParameterfv");
  glTexParameteri          = (PFNGLTEXPARAMETERIPROC) ::glGetProcAddress("glTexParameteri");
  glTexParameteriv         = (PFNGLTEXPARAMETERIVPROC) ::glGetProcAddress("glTexParameteriv");
  glTexImage1D             = (PFNGLTEXIMAGE1DPROC) ::glGetProcAddress("glTexImage1D");
  glTexImage2D             = (PFNGLTEXIMAGE2DPROC) ::glGetProcAddress("glTexImage2D");
  glDrawBuffer             = (PFNGLDRAWBUFFERPROC) ::glGetProcAddress("glDrawBuffer");
  glClear                  = (PFNGLCLEARPROC) ::glGetProcAddress("glClear");
  glClearColor             = (PFNGLCLEARCOLORPROC) ::glGetProcAddress("glClearColor");
  glClearStencil           = (PFNGLCLEARSTENCILPROC) ::glGetProcAddress("glClearStencil");
  glClearDepth             = (PFNGLCLEARDEPTHPROC) ::glGetProcAddress("glClearDepth");
  glStencilMask            = (PFNGLSTENCILMASKPROC) ::glGetProcAddress("glStencilMask");
  glColorMask              = (PFNGLCOLORMASKPROC) ::glGetProcAddress("glColorMask");
  glDepthMask              = (PFNGLDEPTHMASKPROC) ::glGetProcAddress("glDepthMask");
  glDisable                = (PFNGLDISABLEPROC) ::glGetProcAddress("glDisable");
  glEnable                 = (PFNGLENABLEPROC) ::glGetProcAddress("glEnable");
  glFinish                 = (PFNGLFINISHPROC) ::glGetProcAddress("glFinish");
  glFlush                  = (PFNGLFLUSHPROC) ::glGetProcAddress("glFlush");
  glBlendFunc              = (PFNGLBLENDFUNCPROC) ::glGetProcAddress("glBlendFunc");
  glLogicOp                = (PFNGLLOGICOPPROC) ::glGetProcAddress("glLogicOp");
  glStencilFunc            = (PFNGLSTENCILFUNCPROC) ::glGetProcAddress("glStencilFunc");
  glStencilOp              = (PFNGLSTENCILOPPROC) ::glGetProcAddress("glStencilOp");
  glDepthFunc              = (PFNGLDEPTHFUNCPROC) ::glGetProcAddress("glDepthFunc");
  glPixelStoref            = (PFNGLPIXELSTOREFPROC) ::glGetProcAddress("glPixelStoref");
  glPixelStorei            = (PFNGLPIXELSTOREIPROC) ::glGetProcAddress("glPixelStorei");
  glReadBuffer             = (PFNGLREADBUFFERPROC) ::glGetProcAddress("glReadBuffer");
  glReadPixels             = (PFNGLREADPIXELSPROC) ::glGetProcAddress("glReadPixels");
  glGetBooleanv            = (PFNGLGETBOOLEANVPROC) ::glGetProcAddress("glGetBooleanv");
  glGetDoublev             = (PFNGLGETDOUBLEVPROC) ::glGetProcAddress("glGetDoublev");
  glGetError               = (PFNGLGETERRORPROC) ::glGetProcAddress("glGetError");
  glGetFloatv              = (PFNGLGETFLOATVPROC) ::glGetProcAddress("glGetFloatv");
  glGetIntegerv            = (PFNGLGETINTEGERVPROC) ::glGetProcAddress("glGetIntegerv");
  glGetString              = (PFNGLGETSTRINGPROC) ::glGetProcAddress("glGetString");
  glGetTexImage            = (PFNGLGETTEXIMAGEPROC) ::glGetProcAddress("glGetTexImage");
  glGetTexParameterfv      = (PFNGLGETTEXPARAMETERFVPROC) ::glGetProcAddress("glGetTexParameterfv");
  glGetTexParameteriv      = (PFNGLGETTEXPARAMETERIVPROC) ::glGetProcAddress("glGetTexParameteriv");
  glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC) ::glGetProcAddress("glGetTexLevelParameterfv");
  glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC) ::glGetProcAddress("glGetTexLevelParameteriv");
  glIsEnabled              = (PFNGLISENABLEDPROC) ::glGetProcAddress("glIsEnabled");
  glDepthRange             = (PFNGLDEPTHRANGEPROC) ::glGetProcAddress("glDepthRange");
  glViewport               = (PFNGLVIEWPORTPROC) ::glGetProcAddress("glViewport");
  return true;
}

static bool load_v_1_1() {
  if (!OGL_VERSION_1_1) return false;
  glDrawArrays        = (PFNGLDRAWARRAYSPROC) ::glGetProcAddress("glDrawArrays");
  glDrawElements      = (PFNGLDRAWELEMENTSPROC) ::glGetProcAddress("glDrawElements");
  glPolygonOffset     = (PFNGLPOLYGONOFFSETPROC) ::glGetProcAddress("glPolygonOffset");
  glCopyTexImage1D    = (PFNGLCOPYTEXIMAGE1DPROC) ::glGetProcAddress("glCopyTexImage1D");
  glCopyTexImage2D    = (PFNGLCOPYTEXIMAGE2DPROC) ::glGetProcAddress("glCopyTexImage2D");
  glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC) ::glGetProcAddress("glCopyTexSubImage1D");
  glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) ::glGetProcAddress("glCopyTexSubImage2D");
  glTexSubImage1D     = (PFNGLTEXSUBIMAGE1DPROC) ::glGetProcAddress("glTexSubImage1D");
  glTexSubImage2D     = (PFNGLTEXSUBIMAGE2DPROC) ::glGetProcAddress("glTexSubImage2D");
  glBindTexture       = (PFNGLBINDTEXTUREPROC) ::glGetProcAddress("glBindTexture");
  glDeleteTextures    = (PFNGLDELETETEXTURESPROC) ::glGetProcAddress("glDeleteTextures");
  glGenTextures       = (PFNGLGENTEXTURESPROC) ::glGetProcAddress("glGenTextures");
  glIsTexture         = (PFNGLISTEXTUREPROC) ::glGetProcAddress("glIsTexture");
  return true;
}

static bool load_v_1_2() {
  if (!OGL_VERSION_1_2) return false;
  glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) ::glGetProcAddress("glDrawRangeElements");
  glTexImage3D        = (PFNGLTEXIMAGE3DPROC) ::glGetProcAddress("glTexImage3D");
  glTexSubImage3D     = (PFNGLTEXSUBIMAGE3DPROC) ::glGetProcAddress("glTexSubImage3D");
  glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC) ::glGetProcAddress("glCopyTexSubImage3D");
  return true;
}

static bool load_v_1_3() {
  if (!OGL_VERSION_1_3) return false;
  glActiveTexture           = (PFNGLACTIVETEXTUREPROC) ::glGetProcAddress("glActiveTexture");
  glSampleCoverage          = (PFNGLSAMPLECOVERAGEPROC) ::glGetProcAddress("glSampleCoverage");
  glCompressedTexImage3D    = (PFNGLCOMPRESSEDTEXIMAGE3DPROC) ::glGetProcAddress("glCompressedTexImage3D");
  glCompressedTexImage2D    = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) ::glGetProcAddress("glCompressedTexImage2D");
  glCompressedTexImage1D    = (PFNGLCOMPRESSEDTEXIMAGE1DPROC) ::glGetProcAddress("glCompressedTexImage1D");
  glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) ::glGetProcAddress("glCompressedTexSubImage3D");
  glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) ::glGetProcAddress("glCompressedTexSubImage2D");
  glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) ::glGetProcAddress("glCompressedTexSubImage1D");
  glGetCompressedTexImage   = (PFNGLGETCOMPRESSEDTEXIMAGEPROC) ::glGetProcAddress("glGetCompressedTexImage");
  return true;
}

static bool load_v_1_4() {
  if (!OGL_VERSION_1_4) return false;
  glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC) ::glGetProcAddress("glBlendFuncSeparate");
  glMultiDrawArrays   = (PFNGLMULTIDRAWARRAYSPROC) ::glGetProcAddress("glMultiDrawArrays");
  glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC) ::glGetProcAddress("glMultiDrawElements");
  glPointParameterf   = (PFNGLPOINTPARAMETERFPROC) ::glGetProcAddress("glPointParameterf");
  glPointParameterfv  = (PFNGLPOINTPARAMETERFVPROC) ::glGetProcAddress("glPointParameterfv");
  glPointParameteri   = (PFNGLPOINTPARAMETERIPROC) ::glGetProcAddress("glPointParameteri");
  glPointParameteriv  = (PFNGLPOINTPARAMETERIVPROC) ::glGetProcAddress("glPointParameteriv");
  glBlendColor        = (PFNGLBLENDCOLORPROC) ::glGetProcAddress("glBlendColor");
  glBlendEquation     = (PFNGLBLENDEQUATIONPROC) ::glGetProcAddress("glBlendEquation");
  return true;
}

static bool load_v_1_5() {
  if (!OGL_VERSION_1_5) return false;
  glGenQueries           = (PFNGLGENQUERIESPROC) ::glGetProcAddress("glGenQueries");
  glDeleteQueries        = (PFNGLDELETEQUERIESPROC) ::glGetProcAddress("glDeleteQueries");
  glIsQuery              = (PFNGLISQUERYPROC) ::glGetProcAddress("glIsQuery");
  glBeginQuery           = (PFNGLBEGINQUERYPROC) ::glGetProcAddress("glBeginQuery");
  glEndQuery             = (PFNGLENDQUERYPROC) ::glGetProcAddress("glEndQuery");
  glGetQueryiv           = (PFNGLGETQUERYIVPROC) ::glGetProcAddress("glGetQueryiv");
  glGetQueryObjectiv     = (PFNGLGETQUERYOBJECTIVPROC) ::glGetProcAddress("glGetQueryObjectiv");
  glGetQueryObjectuiv    = (PFNGLGETQUERYOBJECTUIVPROC) ::glGetProcAddress("glGetQueryObjectuiv");
  glBindBuffer           = (PFNGLBINDBUFFERPROC) ::glGetProcAddress("glBindBuffer");
  glDeleteBuffers        = (PFNGLDELETEBUFFERSPROC) ::glGetProcAddress("glDeleteBuffers");
  glGenBuffers           = (PFNGLGENBUFFERSPROC) ::glGetProcAddress("glGenBuffers");
  glIsBuffer             = (PFNGLISBUFFERPROC) ::glGetProcAddress("glIsBuffer");
  glBufferData           = (PFNGLBUFFERDATAPROC) ::glGetProcAddress("glBufferData");
  glBufferSubData        = (PFNGLBUFFERSUBDATAPROC) ::glGetProcAddress("glBufferSubData");
  glGetBufferSubData     = (PFNGLGETBUFFERSUBDATAPROC) ::glGetProcAddress("glGetBufferSubData");
  glMapBuffer            = (PFNGLMAPBUFFERPROC) ::glGetProcAddress("glMapBuffer");
  glUnmapBuffer          = (PFNGLUNMAPBUFFERPROC) ::glGetProcAddress("glUnmapBuffer");
  glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) ::glGetProcAddress("glGetBufferParameteriv");
  glGetBufferPointerv    = (PFNGLGETBUFFERPOINTERVPROC) ::glGetProcAddress("glGetBufferPointerv");
  return true;
}

static bool load_v_2_0() {
  if (!OGL_VERSION_2_0) return false;
  glBlendEquationSeparate    = (PFNGLBLENDEQUATIONSEPARATEPROC) ::glGetProcAddress("glBlendEquationSeparate");
  glDrawBuffers              = (PFNGLDRAWBUFFERSPROC) ::glGetProcAddress("glDrawBuffers");
  glStencilOpSeparate        = (PFNGLSTENCILOPSEPARATEPROC) ::glGetProcAddress("glStencilOpSeparate");
  glStencilFuncSeparate      = (PFNGLSTENCILFUNCSEPARATEPROC) ::glGetProcAddress("glStencilFuncSeparate");
  glStencilMaskSeparate      = (PFNGLSTENCILMASKSEPARATEPROC) ::glGetProcAddress("glStencilMaskSeparate");
  glAttachShader             = (PFNGLATTACHSHADERPROC) ::glGetProcAddress("glAttachShader");
  glBindAttribLocation       = (PFNGLBINDATTRIBLOCATIONPROC) ::glGetProcAddress("glBindAttribLocation");
  glCompileShader            = (PFNGLCOMPILESHADERPROC) ::glGetProcAddress("glCompileShader");
  glCreateProgram            = (PFNGLCREATEPROGRAMPROC) ::glGetProcAddress("glCreateProgram");
  glCreateShader             = (PFNGLCREATESHADERPROC) ::glGetProcAddress("glCreateShader");
  glDeleteProgram            = (PFNGLDELETEPROGRAMPROC) ::glGetProcAddress("glDeleteProgram");
  glDeleteShader             = (PFNGLDELETESHADERPROC) ::glGetProcAddress("glDeleteShader");
  glDetachShader             = (PFNGLDETACHSHADERPROC) ::glGetProcAddress("glDetachShader");
  glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) ::glGetProcAddress("glDisableVertexAttribArray");
  glEnableVertexAttribArray  = (PFNGLENABLEVERTEXATTRIBARRAYPROC) ::glGetProcAddress("glEnableVertexAttribArray");
  glGetActiveAttrib          = (PFNGLGETACTIVEATTRIBPROC) ::glGetProcAddress("glGetActiveAttrib");
  glGetActiveUniform         = (PFNGLGETACTIVEUNIFORMPROC) ::glGetProcAddress("glGetActiveUniform");
  glGetAttachedShaders       = (PFNGLGETATTACHEDSHADERSPROC) ::glGetProcAddress("glGetAttachedShaders");
  glGetAttribLocation        = (PFNGLGETATTRIBLOCATIONPROC) ::glGetProcAddress("glGetAttribLocation");
  glGetProgramiv             = (PFNGLGETPROGRAMIVPROC) ::glGetProcAddress("glGetProgramiv");
  glGetProgramInfoLog        = (PFNGLGETPROGRAMINFOLOGPROC) ::glGetProcAddress("glGetProgramInfoLog");
  glGetShaderiv              = (PFNGLGETSHADERIVPROC) ::glGetProcAddress("glGetShaderiv");
  glGetShaderInfoLog         = (PFNGLGETSHADERINFOLOGPROC) ::glGetProcAddress("glGetShaderInfoLog");
  glGetShaderSource          = (PFNGLGETSHADERSOURCEPROC) ::glGetProcAddress("glGetShaderSource");
  glGetUniformLocation       = (PFNGLGETUNIFORMLOCATIONPROC) ::glGetProcAddress("glGetUniformLocation");
  glGetUniformfv             = (PFNGLGETUNIFORMFVPROC) ::glGetProcAddress("glGetUniformfv");
  glGetUniformiv             = (PFNGLGETUNIFORMIVPROC) ::glGetProcAddress("glGetUniformiv");
  glGetVertexAttribdv        = (PFNGLGETVERTEXATTRIBDVPROC) ::glGetProcAddress("glGetVertexAttribdv");
  glGetVertexAttribfv        = (PFNGLGETVERTEXATTRIBFVPROC) ::glGetProcAddress("glGetVertexAttribfv");
  glGetVertexAttribiv        = (PFNGLGETVERTEXATTRIBIVPROC) ::glGetProcAddress("glGetVertexAttribiv");
  glGetVertexAttribPointerv  = (PFNGLGETVERTEXATTRIBPOINTERVPROC) ::glGetProcAddress("glGetVertexAttribPointerv");
  glIsProgram                = (PFNGLISPROGRAMPROC) ::glGetProcAddress("glIsProgram");
  glIsShader                 = (PFNGLISSHADERPROC) ::glGetProcAddress("glIsShader");
  glLinkProgram              = (PFNGLLINKPROGRAMPROC) ::glGetProcAddress("glLinkProgram");
  glShaderSource             = (PFNGLSHADERSOURCEPROC) ::glGetProcAddress("glShaderSource");
  glUseProgram               = (PFNGLUSEPROGRAMPROC) ::glGetProcAddress("glUseProgram");
  glUniform1f                = (PFNGLUNIFORM1FPROC) ::glGetProcAddress("glUniform1f");
  glUniform2f                = (PFNGLUNIFORM2FPROC) ::glGetProcAddress("glUniform2f");
  glUniform3f                = (PFNGLUNIFORM3FPROC) ::glGetProcAddress("glUniform3f");
  glUniform4f                = (PFNGLUNIFORM4FPROC) ::glGetProcAddress("glUniform4f");
  glUniform1i                = (PFNGLUNIFORM1IPROC) ::glGetProcAddress("glUniform1i");
  glUniform2i                = (PFNGLUNIFORM2IPROC) ::glGetProcAddress("glUniform2i");
  glUniform3i                = (PFNGLUNIFORM3IPROC) ::glGetProcAddress("glUniform3i");
  glUniform4i                = (PFNGLUNIFORM4IPROC) ::glGetProcAddress("glUniform4i");
  glUniform1fv               = (PFNGLUNIFORM1FVPROC) ::glGetProcAddress("glUniform1fv");
  glUniform2fv               = (PFNGLUNIFORM2FVPROC) ::glGetProcAddress("glUniform2fv");
  glUniform3fv               = (PFNGLUNIFORM3FVPROC) ::glGetProcAddress("glUniform3fv");
  glUniform4fv               = (PFNGLUNIFORM4FVPROC) ::glGetProcAddress("glUniform4fv");
  glUniform1iv               = (PFNGLUNIFORM1IVPROC) ::glGetProcAddress("glUniform1iv");
  glUniform2iv               = (PFNGLUNIFORM2IVPROC) ::glGetProcAddress("glUniform2iv");
  glUniform3iv               = (PFNGLUNIFORM3IVPROC) ::glGetProcAddress("glUniform3iv");
  glUniform4iv               = (PFNGLUNIFORM4IVPROC) ::glGetProcAddress("glUniform4iv");
  glUniformMatrix2fv         = (PFNGLUNIFORMMATRIX2FVPROC) ::glGetProcAddress("glUniformMatrix2fv");
  glUniformMatrix3fv         = (PFNGLUNIFORMMATRIX3FVPROC) ::glGetProcAddress("glUniformMatrix3fv");
  glUniformMatrix4fv         = (PFNGLUNIFORMMATRIX4FVPROC) ::glGetProcAddress("glUniformMatrix4fv");
  glValidateProgram          = (PFNGLVALIDATEPROGRAMPROC) ::glGetProcAddress("glValidateProgram");
  glVertexAttrib1d           = (PFNGLVERTEXATTRIB1DPROC) ::glGetProcAddress("glVertexAttrib1d");
  glVertexAttrib1dv          = (PFNGLVERTEXATTRIB1DVPROC) ::glGetProcAddress("glVertexAttrib1dv");
  glVertexAttrib1f           = (PFNGLVERTEXATTRIB1FPROC) ::glGetProcAddress("glVertexAttrib1f");
  glVertexAttrib1fv          = (PFNGLVERTEXATTRIB1FVPROC) ::glGetProcAddress("glVertexAttrib1fv");
  glVertexAttrib1s           = (PFNGLVERTEXATTRIB1SPROC) ::glGetProcAddress("glVertexAttrib1s");
  glVertexAttrib1sv          = (PFNGLVERTEXATTRIB1SVPROC) ::glGetProcAddress("glVertexAttrib1sv");
  glVertexAttrib2d           = (PFNGLVERTEXATTRIB2DPROC) ::glGetProcAddress("glVertexAttrib2d");
  glVertexAttrib2dv          = (PFNGLVERTEXATTRIB2DVPROC) ::glGetProcAddress("glVertexAttrib2dv");
  glVertexAttrib2f           = (PFNGLVERTEXATTRIB2FPROC) ::glGetProcAddress("glVertexAttrib2f");
  glVertexAttrib2fv          = (PFNGLVERTEXATTRIB2FVPROC) ::glGetProcAddress("glVertexAttrib2fv");
  glVertexAttrib2s           = (PFNGLVERTEXATTRIB2SPROC) ::glGetProcAddress("glVertexAttrib2s");
  glVertexAttrib2sv          = (PFNGLVERTEXATTRIB2SVPROC) ::glGetProcAddress("glVertexAttrib2sv");
  glVertexAttrib3d           = (PFNGLVERTEXATTRIB3DPROC) ::glGetProcAddress("glVertexAttrib3d");
  glVertexAttrib3dv          = (PFNGLVERTEXATTRIB3DVPROC) ::glGetProcAddress("glVertexAttrib3dv");
  glVertexAttrib3f           = (PFNGLVERTEXATTRIB3FPROC) ::glGetProcAddress("glVertexAttrib3f");
  glVertexAttrib3fv          = (PFNGLVERTEXATTRIB3FVPROC) ::glGetProcAddress("glVertexAttrib3fv");
  glVertexAttrib3s           = (PFNGLVERTEXATTRIB3SPROC) ::glGetProcAddress("glVertexAttrib3s");
  glVertexAttrib3sv          = (PFNGLVERTEXATTRIB3SVPROC) ::glGetProcAddress("glVertexAttrib3sv");
  glVertexAttrib4Nbv         = (PFNGLVERTEXATTRIB4NBVPROC) ::glGetProcAddress("glVertexAttrib4Nbv");
  glVertexAttrib4Niv         = (PFNGLVERTEXATTRIB4NIVPROC) ::glGetProcAddress("glVertexAttrib4Niv");
  glVertexAttrib4Nsv         = (PFNGLVERTEXATTRIB4NSVPROC) ::glGetProcAddress("glVertexAttrib4Nsv");
  glVertexAttrib4Nub         = (PFNGLVERTEXATTRIB4NUBPROC) ::glGetProcAddress("glVertexAttrib4Nub");
  glVertexAttrib4Nubv        = (PFNGLVERTEXATTRIB4NUBVPROC) ::glGetProcAddress("glVertexAttrib4Nubv");
  glVertexAttrib4Nuiv        = (PFNGLVERTEXATTRIB4NUIVPROC) ::glGetProcAddress("glVertexAttrib4Nuiv");
  glVertexAttrib4Nusv        = (PFNGLVERTEXATTRIB4NUSVPROC) ::glGetProcAddress("glVertexAttrib4Nusv");
  glVertexAttrib4bv          = (PFNGLVERTEXATTRIB4BVPROC) ::glGetProcAddress("glVertexAttrib4bv");
  glVertexAttrib4d           = (PFNGLVERTEXATTRIB4DPROC) ::glGetProcAddress("glVertexAttrib4d");
  glVertexAttrib4dv          = (PFNGLVERTEXATTRIB4DVPROC) ::glGetProcAddress("glVertexAttrib4dv");
  glVertexAttrib4f           = (PFNGLVERTEXATTRIB4FPROC) ::glGetProcAddress("glVertexAttrib4f");
  glVertexAttrib4fv          = (PFNGLVERTEXATTRIB4FVPROC) ::glGetProcAddress("glVertexAttrib4fv");
  glVertexAttrib4iv          = (PFNGLVERTEXATTRIB4IVPROC) ::glGetProcAddress("glVertexAttrib4iv");
  glVertexAttrib4s           = (PFNGLVERTEXATTRIB4SPROC) ::glGetProcAddress("glVertexAttrib4s");
  glVertexAttrib4sv          = (PFNGLVERTEXATTRIB4SVPROC) ::glGetProcAddress("glVertexAttrib4sv");
  glVertexAttrib4ubv         = (PFNGLVERTEXATTRIB4UBVPROC) ::glGetProcAddress("glVertexAttrib4ubv");
  glVertexAttrib4uiv         = (PFNGLVERTEXATTRIB4UIVPROC) ::glGetProcAddress("glVertexAttrib4uiv");
  glVertexAttrib4usv         = (PFNGLVERTEXATTRIB4USVPROC) ::glGetProcAddress("glVertexAttrib4usv");
  glVertexAttribPointer      = (PFNGLVERTEXATTRIBPOINTERPROC) ::glGetProcAddress("glVertexAttribPointer");
  return true;
}

static bool load_v_2_1() {
  if (!OGL_VERSION_2_1) return false;
  glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC) ::glGetProcAddress("glUniformMatrix2x3fv");
  glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC) ::glGetProcAddress("glUniformMatrix3x2fv");
  glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC) ::glGetProcAddress("glUniformMatrix2x4fv");
  glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC) ::glGetProcAddress("glUniformMatrix4x2fv");
  glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC) ::glGetProcAddress("glUniformMatrix3x4fv");
  glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC) ::glGetProcAddress("glUniformMatrix4x3fv");
  return true;
}

static bool load_v_3_0() {
  if (!OGL_VERSION_3_0) return false;
  glColorMaski                          = (PFNGLCOLORMASKIPROC) ::glGetProcAddress("glColorMaski");
  glGetBooleani_v                       = (PFNGLGETBOOLEANI_VPROC) ::glGetProcAddress("glGetBooleani_v");
  glGetIntegeri_v                       = (PFNGLGETINTEGERI_VPROC) ::glGetProcAddress("glGetIntegeri_v");
  glEnablei                             = (PFNGLENABLEIPROC) ::glGetProcAddress("glEnablei");
  glDisablei                            = (PFNGLDISABLEIPROC) ::glGetProcAddress("glDisablei");
  glIsEnabledi                          = (PFNGLISENABLEDIPROC) ::glGetProcAddress("glIsEnabledi");
  glBeginTransformFeedback              = (PFNGLBEGINTRANSFORMFEEDBACKPROC) ::glGetProcAddress("glBeginTransformFeedback");
  glEndTransformFeedback                = (PFNGLENDTRANSFORMFEEDBACKPROC) ::glGetProcAddress("glEndTransformFeedback");
  glBindBufferRange                     = (PFNGLBINDBUFFERRANGEPROC) ::glGetProcAddress("glBindBufferRange");
  glBindBufferBase                      = (PFNGLBINDBUFFERBASEPROC) ::glGetProcAddress("glBindBufferBase");
  glTransformFeedbackVaryings           = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC) ::glGetProcAddress("glTransformFeedbackVaryings");
  glGetTransformFeedbackVarying         = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) ::glGetProcAddress("glGetTransformFeedbackVarying");
  glClampColor                          = (PFNGLCLAMPCOLORPROC) ::glGetProcAddress("glClampColor");
  glBeginConditionalRender              = (PFNGLBEGINCONDITIONALRENDERPROC) ::glGetProcAddress("glBeginConditionalRender");
  glEndConditionalRender                = (PFNGLENDCONDITIONALRENDERPROC) ::glGetProcAddress("glEndConditionalRender");
  glVertexAttribIPointer                = (PFNGLVERTEXATTRIBIPOINTERPROC) ::glGetProcAddress("glVertexAttribIPointer");
  glGetVertexAttribIiv                  = (PFNGLGETVERTEXATTRIBIIVPROC) ::glGetProcAddress("glGetVertexAttribIiv");
  glGetVertexAttribIuiv                 = (PFNGLGETVERTEXATTRIBIUIVPROC) ::glGetProcAddress("glGetVertexAttribIuiv");
  glVertexAttribI1i                     = (PFNGLVERTEXATTRIBI1IPROC) ::glGetProcAddress("glVertexAttribI1i");
  glVertexAttribI2i                     = (PFNGLVERTEXATTRIBI2IPROC) ::glGetProcAddress("glVertexAttribI2i");
  glVertexAttribI3i                     = (PFNGLVERTEXATTRIBI3IPROC) ::glGetProcAddress("glVertexAttribI3i");
  glVertexAttribI4i                     = (PFNGLVERTEXATTRIBI4IPROC) ::glGetProcAddress("glVertexAttribI4i");
  glVertexAttribI1ui                    = (PFNGLVERTEXATTRIBI1UIPROC) ::glGetProcAddress("glVertexAttribI1ui");
  glVertexAttribI2ui                    = (PFNGLVERTEXATTRIBI2UIPROC) ::glGetProcAddress("glVertexAttribI2ui");
  glVertexAttribI3ui                    = (PFNGLVERTEXATTRIBI3UIPROC) ::glGetProcAddress("glVertexAttribI3ui");
  glVertexAttribI4ui                    = (PFNGLVERTEXATTRIBI4UIPROC) ::glGetProcAddress("glVertexAttribI4ui");
  glVertexAttribI1iv                    = (PFNGLVERTEXATTRIBI1IVPROC) ::glGetProcAddress("glVertexAttribI1iv");
  glVertexAttribI2iv                    = (PFNGLVERTEXATTRIBI2IVPROC) ::glGetProcAddress("glVertexAttribI2iv");
  glVertexAttribI3iv                    = (PFNGLVERTEXATTRIBI3IVPROC) ::glGetProcAddress("glVertexAttribI3iv");
  glVertexAttribI4iv                    = (PFNGLVERTEXATTRIBI4IVPROC) ::glGetProcAddress("glVertexAttribI4iv");
  glVertexAttribI1uiv                   = (PFNGLVERTEXATTRIBI1UIVPROC) ::glGetProcAddress("glVertexAttribI1uiv");
  glVertexAttribI2uiv                   = (PFNGLVERTEXATTRIBI2UIVPROC) ::glGetProcAddress("glVertexAttribI2uiv");
  glVertexAttribI3uiv                   = (PFNGLVERTEXATTRIBI3UIVPROC) ::glGetProcAddress("glVertexAttribI3uiv");
  glVertexAttribI4uiv                   = (PFNGLVERTEXATTRIBI4UIVPROC) ::glGetProcAddress("glVertexAttribI4uiv");
  glVertexAttribI4bv                    = (PFNGLVERTEXATTRIBI4BVPROC) ::glGetProcAddress("glVertexAttribI4bv");
  glVertexAttribI4sv                    = (PFNGLVERTEXATTRIBI4SVPROC) ::glGetProcAddress("glVertexAttribI4sv");
  glVertexAttribI4ubv                   = (PFNGLVERTEXATTRIBI4UBVPROC) ::glGetProcAddress("glVertexAttribI4ubv");
  glVertexAttribI4usv                   = (PFNGLVERTEXATTRIBI4USVPROC) ::glGetProcAddress("glVertexAttribI4usv");
  glGetUniformuiv                       = (PFNGLGETUNIFORMUIVPROC) ::glGetProcAddress("glGetUniformuiv");
  glBindFragDataLocation                = (PFNGLBINDFRAGDATALOCATIONPROC) ::glGetProcAddress("glBindFragDataLocation");
  glGetFragDataLocation                 = (PFNGLGETFRAGDATALOCATIONPROC) ::glGetProcAddress("glGetFragDataLocation");
  glUniform1ui                          = (PFNGLUNIFORM1UIPROC) ::glGetProcAddress("glUniform1ui");
  glUniform2ui                          = (PFNGLUNIFORM2UIPROC) ::glGetProcAddress("glUniform2ui");
  glUniform3ui                          = (PFNGLUNIFORM3UIPROC) ::glGetProcAddress("glUniform3ui");
  glUniform4ui                          = (PFNGLUNIFORM4UIPROC) ::glGetProcAddress("glUniform4ui");
  glUniform1uiv                         = (PFNGLUNIFORM1UIVPROC) ::glGetProcAddress("glUniform1uiv");
  glUniform2uiv                         = (PFNGLUNIFORM2UIVPROC) ::glGetProcAddress("glUniform2uiv");
  glUniform3uiv                         = (PFNGLUNIFORM3UIVPROC) ::glGetProcAddress("glUniform3uiv");
  glUniform4uiv                         = (PFNGLUNIFORM4UIVPROC) ::glGetProcAddress("glUniform4uiv");
  glTexParameterIiv                     = (PFNGLTEXPARAMETERIIVPROC) ::glGetProcAddress("glTexParameterIiv");
  glTexParameterIuiv                    = (PFNGLTEXPARAMETERIUIVPROC) ::glGetProcAddress("glTexParameterIuiv");
  glGetTexParameterIiv                  = (PFNGLGETTEXPARAMETERIIVPROC) ::glGetProcAddress("glGetTexParameterIiv");
  glGetTexParameterIuiv                 = (PFNGLGETTEXPARAMETERIUIVPROC) ::glGetProcAddress("glGetTexParameterIuiv");
  glClearBufferiv                       = (PFNGLCLEARBUFFERIVPROC) ::glGetProcAddress("glClearBufferiv");
  glClearBufferuiv                      = (PFNGLCLEARBUFFERUIVPROC) ::glGetProcAddress("glClearBufferuiv");
  glClearBufferfv                       = (PFNGLCLEARBUFFERFVPROC) ::glGetProcAddress("glClearBufferfv");
  glClearBufferfi                       = (PFNGLCLEARBUFFERFIPROC) ::glGetProcAddress("glClearBufferfi");
  glGetStringi                          = (PFNGLGETSTRINGIPROC) ::glGetProcAddress("glGetStringi");
  glIsRenderbuffer                      = (PFNGLISRENDERBUFFERPROC) ::glGetProcAddress("glIsRenderbuffer");
  glBindRenderbuffer                    = (PFNGLBINDRENDERBUFFERPROC) ::glGetProcAddress("glBindRenderbuffer");
  glDeleteRenderbuffers                 = (PFNGLDELETERENDERBUFFERSPROC) ::glGetProcAddress("glDeleteRenderbuffers");
  glGenRenderbuffers                    = (PFNGLGENRENDERBUFFERSPROC) ::glGetProcAddress("glGenRenderbuffers");
  glRenderbufferStorage                 = (PFNGLRENDERBUFFERSTORAGEPROC) ::glGetProcAddress("glRenderbufferStorage");
  glGetRenderbufferParameteriv          = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) ::glGetProcAddress("glGetRenderbufferParameteriv");
  glIsFramebuffer                       = (PFNGLISFRAMEBUFFERPROC) ::glGetProcAddress("glIsFramebuffer");
  glBindFramebuffer                     = (PFNGLBINDFRAMEBUFFERPROC) ::glGetProcAddress("glBindFramebuffer");
  glDeleteFramebuffers                  = (PFNGLDELETEFRAMEBUFFERSPROC) ::glGetProcAddress("glDeleteFramebuffers");
  glGenFramebuffers                     = (PFNGLGENFRAMEBUFFERSPROC) ::glGetProcAddress("glGenFramebuffers");
  glCheckFramebufferStatus              = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) ::glGetProcAddress("glCheckFramebufferStatus");
  glFramebufferTexture1D                = (PFNGLFRAMEBUFFERTEXTURE1DPROC) ::glGetProcAddress("glFramebufferTexture1D");
  glFramebufferTexture2D                = (PFNGLFRAMEBUFFERTEXTURE2DPROC) ::glGetProcAddress("glFramebufferTexture2D");
  glFramebufferTexture3D                = (PFNGLFRAMEBUFFERTEXTURE3DPROC) ::glGetProcAddress("glFramebufferTexture3D");
  glFramebufferRenderbuffer             = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) ::glGetProcAddress("glFramebufferRenderbuffer");
  glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) ::glGetProcAddress("glGetFramebufferAttachmentParameteriv");
  glGenerateMipmap                      = (PFNGLGENERATEMIPMAPPROC) ::glGetProcAddress("glGenerateMipmap");
  glBlitFramebuffer                     = (PFNGLBLITFRAMEBUFFERPROC) ::glGetProcAddress("glBlitFramebuffer");
  glRenderbufferStorageMultisample      = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) ::glGetProcAddress("glRenderbufferStorageMultisample");
  glFramebufferTextureLayer             = (PFNGLFRAMEBUFFERTEXTURELAYERPROC) ::glGetProcAddress("glFramebufferTextureLayer");
  glMapBufferRange                      = (PFNGLMAPBUFFERRANGEPROC) ::glGetProcAddress("glMapBufferRange");
  glFlushMappedBufferRange              = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC) ::glGetProcAddress("glFlushMappedBufferRange");
  glBindVertexArray                     = (PFNGLBINDVERTEXARRAYPROC) ::glGetProcAddress("glBindVertexArray");
  glDeleteVertexArrays                  = (PFNGLDELETEVERTEXARRAYSPROC) ::glGetProcAddress("glDeleteVertexArrays");
  glGenVertexArrays                     = (PFNGLGENVERTEXARRAYSPROC) ::glGetProcAddress("glGenVertexArrays");
  glIsVertexArray                       = (PFNGLISVERTEXARRAYPROC) ::glGetProcAddress("glIsVertexArray");
  return true;
}

static bool load_v_3_1() {
  if (!OGL_VERSION_3_1) return false;
  glDrawArraysInstanced       = (PFNGLDRAWARRAYSINSTANCEDPROC) ::glGetProcAddress("glDrawArraysInstanced");
  glDrawElementsInstanced     = (PFNGLDRAWELEMENTSINSTANCEDPROC) ::glGetProcAddress("glDrawElementsInstanced");
  glTexBuffer                 = (PFNGLTEXBUFFERPROC) ::glGetProcAddress("glTexBuffer");
  glPrimitiveRestartIndex     = (PFNGLPRIMITIVERESTARTINDEXPROC) ::glGetProcAddress("glPrimitiveRestartIndex");
  glCopyBufferSubData         = (PFNGLCOPYBUFFERSUBDATAPROC) ::glGetProcAddress("glCopyBufferSubData");
  glGetUniformIndices         = (PFNGLGETUNIFORMINDICESPROC) ::glGetProcAddress("glGetUniformIndices");
  glGetActiveUniformsiv       = (PFNGLGETACTIVEUNIFORMSIVPROC) ::glGetProcAddress("glGetActiveUniformsiv");
  glGetActiveUniformName      = (PFNGLGETACTIVEUNIFORMNAMEPROC) ::glGetProcAddress("glGetActiveUniformName");
  glGetUniformBlockIndex      = (PFNGLGETUNIFORMBLOCKINDEXPROC) ::glGetProcAddress("glGetUniformBlockIndex");
  glGetActiveUniformBlockiv   = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC) ::glGetProcAddress("glGetActiveUniformBlockiv");
  glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) ::glGetProcAddress("glGetActiveUniformBlockName");
  glUniformBlockBinding       = (PFNGLUNIFORMBLOCKBINDINGPROC) ::glGetProcAddress("glUniformBlockBinding");
  glBindBufferRange           = (PFNGLBINDBUFFERRANGEPROC) ::glGetProcAddress("glBindBufferRange");
  glBindBufferBase            = (PFNGLBINDBUFFERBASEPROC) ::glGetProcAddress("glBindBufferBase");
  glGetIntegeri_v             = (PFNGLGETINTEGERI_VPROC) ::glGetProcAddress("glGetIntegeri_v");
  return true;
}

static bool load_v_3_2() {
  if (!OGL_VERSION_3_2) return false;
  glDrawElementsBaseVertex          = (PFNGLDRAWELEMENTSBASEVERTEXPROC) ::glGetProcAddress("glDrawElementsBaseVertex");
  glDrawRangeElementsBaseVertex     = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) ::glGetProcAddress("glDrawRangeElementsBaseVertex");
  glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) ::glGetProcAddress("glDrawElementsInstancedBaseVertex");
  glMultiDrawElementsBaseVertex     = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) ::glGetProcAddress("glMultiDrawElementsBaseVertex");
  glProvokingVertex                 = (PFNGLPROVOKINGVERTEXPROC) ::glGetProcAddress("glProvokingVertex");
  glFenceSync                       = (PFNGLFENCESYNCPROC) ::glGetProcAddress("glFenceSync");
  glIsSync                          = (PFNGLISSYNCPROC) ::glGetProcAddress("glIsSync");
  glDeleteSync                      = (PFNGLDELETESYNCPROC) ::glGetProcAddress("glDeleteSync");
  glClientWaitSync                  = (PFNGLCLIENTWAITSYNCPROC) ::glGetProcAddress("glClientWaitSync");
  glWaitSync                        = (PFNGLWAITSYNCPROC) ::glGetProcAddress("glWaitSync");
  glGetInteger64v                   = (PFNGLGETINTEGER64VPROC) ::glGetProcAddress("glGetInteger64v");
  glGetSynciv                       = (PFNGLGETSYNCIVPROC) ::glGetProcAddress("glGetSynciv");
  glGetInteger64i_v                 = (PFNGLGETINTEGER64I_VPROC) ::glGetProcAddress("glGetInteger64i_v");
  glGetBufferParameteri64v          = (PFNGLGETBUFFERPARAMETERI64VPROC) ::glGetProcAddress("glGetBufferParameteri64v");
  glFramebufferTexture              = (PFNGLFRAMEBUFFERTEXTUREPROC) ::glGetProcAddress("glFramebufferTexture");
  glTexImage2DMultisample           = (PFNGLTEXIMAGE2DMULTISAMPLEPROC) ::glGetProcAddress("glTexImage2DMultisample");
  glTexImage3DMultisample           = (PFNGLTEXIMAGE3DMULTISAMPLEPROC) ::glGetProcAddress("glTexImage3DMultisample");
  glGetMultisamplefv                = (PFNGLGETMULTISAMPLEFVPROC) ::glGetProcAddress("glGetMultisamplefv");
  glSampleMaski                     = (PFNGLSAMPLEMASKIPROC) ::glGetProcAddress("glSampleMaski");
  return true;
}

static bool load_v_3_3() {
  if (!OGL_VERSION_3_3) return false;
  glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) ::glGetProcAddress("glBindFragDataLocationIndexed");
  glGetFragDataIndex            = (PFNGLGETFRAGDATAINDEXPROC) ::glGetProcAddress("glGetFragDataIndex");
  glGenSamplers                 = (PFNGLGENSAMPLERSPROC) ::glGetProcAddress("glGenSamplers");
  glDeleteSamplers              = (PFNGLDELETESAMPLERSPROC) ::glGetProcAddress("glDeleteSamplers");
  glIsSampler                   = (PFNGLISSAMPLERPROC) ::glGetProcAddress("glIsSampler");
  glBindSampler                 = (PFNGLBINDSAMPLERPROC) ::glGetProcAddress("glBindSampler");
  glSamplerParameteri           = (PFNGLSAMPLERPARAMETERIPROC) ::glGetProcAddress("glSamplerParameteri");
  glSamplerParameteriv          = (PFNGLSAMPLERPARAMETERIVPROC) ::glGetProcAddress("glSamplerParameteriv");
  glSamplerParameterf           = (PFNGLSAMPLERPARAMETERFPROC) ::glGetProcAddress("glSamplerParameterf");
  glSamplerParameterfv          = (PFNGLSAMPLERPARAMETERFVPROC) ::glGetProcAddress("glSamplerParameterfv");
  glSamplerParameterIiv         = (PFNGLSAMPLERPARAMETERIIVPROC) ::glGetProcAddress("glSamplerParameterIiv");
  glSamplerParameterIuiv        = (PFNGLSAMPLERPARAMETERIUIVPROC) ::glGetProcAddress("glSamplerParameterIuiv");
  glGetSamplerParameteriv       = (PFNGLGETSAMPLERPARAMETERIVPROC) ::glGetProcAddress("glGetSamplerParameteriv");
  glGetSamplerParameterIiv      = (PFNGLGETSAMPLERPARAMETERIIVPROC) ::glGetProcAddress("glGetSamplerParameterIiv");
  glGetSamplerParameterfv       = (PFNGLGETSAMPLERPARAMETERFVPROC) ::glGetProcAddress("glGetSamplerParameterfv");
  glGetSamplerParameterIuiv     = (PFNGLGETSAMPLERPARAMETERIUIVPROC) ::glGetProcAddress("glGetSamplerParameterIuiv");
  glQueryCounter                = (PFNGLQUERYCOUNTERPROC) ::glGetProcAddress("glQueryCounter");
  glGetQueryObjecti64v          = (PFNGLGETQUERYOBJECTI64VPROC) ::glGetProcAddress("glGetQueryObjecti64v");
  glGetQueryObjectui64v         = (PFNGLGETQUERYOBJECTUI64VPROC) ::glGetProcAddress("glGetQueryObjectui64v");
  glVertexAttribDivisor         = (PFNGLVERTEXATTRIBDIVISORPROC) ::glGetProcAddress("glVertexAttribDivisor");
  glVertexAttribP1ui            = (PFNGLVERTEXATTRIBP1UIPROC) ::glGetProcAddress("glVertexAttribP1ui");
  glVertexAttribP1uiv           = (PFNGLVERTEXATTRIBP1UIVPROC) ::glGetProcAddress("glVertexAttribP1uiv");
  glVertexAttribP2ui            = (PFNGLVERTEXATTRIBP2UIPROC) ::glGetProcAddress("glVertexAttribP2ui");
  glVertexAttribP2uiv           = (PFNGLVERTEXATTRIBP2UIVPROC) ::glGetProcAddress("glVertexAttribP2uiv");
  glVertexAttribP3ui            = (PFNGLVERTEXATTRIBP3UIPROC) ::glGetProcAddress("glVertexAttribP3ui");
  glVertexAttribP3uiv           = (PFNGLVERTEXATTRIBP3UIVPROC) ::glGetProcAddress("glVertexAttribP3uiv");
  glVertexAttribP4ui            = (PFNGLVERTEXATTRIBP4UIPROC) ::glGetProcAddress("glVertexAttribP4ui");
  glVertexAttribP4uiv           = (PFNGLVERTEXATTRIBP4UIVPROC) ::glGetProcAddress("glVertexAttribP4uiv");
  glVertexP2ui                  = (PFNGLVERTEXP2UIPROC) ::glGetProcAddress("glVertexP2ui");
  glVertexP2uiv                 = (PFNGLVERTEXP2UIVPROC) ::glGetProcAddress("glVertexP2uiv");
  glVertexP3ui                  = (PFNGLVERTEXP3UIPROC) ::glGetProcAddress("glVertexP3ui");
  glVertexP3uiv                 = (PFNGLVERTEXP3UIVPROC) ::glGetProcAddress("glVertexP3uiv");
  glVertexP4ui                  = (PFNGLVERTEXP4UIPROC) ::glGetProcAddress("glVertexP4ui");
  glVertexP4uiv                 = (PFNGLVERTEXP4UIVPROC) ::glGetProcAddress("glVertexP4uiv");
  glTexCoordP1ui                = (PFNGLTEXCOORDP1UIPROC) ::glGetProcAddress("glTexCoordP1ui");
  glTexCoordP1uiv               = (PFNGLTEXCOORDP1UIVPROC) ::glGetProcAddress("glTexCoordP1uiv");
  glTexCoordP2ui                = (PFNGLTEXCOORDP2UIPROC) ::glGetProcAddress("glTexCoordP2ui");
  glTexCoordP2uiv               = (PFNGLTEXCOORDP2UIVPROC) ::glGetProcAddress("glTexCoordP2uiv");
  glTexCoordP3ui                = (PFNGLTEXCOORDP3UIPROC) ::glGetProcAddress("glTexCoordP3ui");
  glTexCoordP3uiv               = (PFNGLTEXCOORDP3UIVPROC) ::glGetProcAddress("glTexCoordP3uiv");
  glTexCoordP4ui                = (PFNGLTEXCOORDP4UIPROC) ::glGetProcAddress("glTexCoordP4ui");
  glTexCoordP4uiv               = (PFNGLTEXCOORDP4UIVPROC) ::glGetProcAddress("glTexCoordP4uiv");
  glMultiTexCoordP1ui           = (PFNGLMULTITEXCOORDP1UIPROC) ::glGetProcAddress("glMultiTexCoordP1ui");
  glMultiTexCoordP1uiv          = (PFNGLMULTITEXCOORDP1UIVPROC) ::glGetProcAddress("glMultiTexCoordP1uiv");
  glMultiTexCoordP2ui           = (PFNGLMULTITEXCOORDP2UIPROC) ::glGetProcAddress("glMultiTexCoordP2ui");
  glMultiTexCoordP2uiv          = (PFNGLMULTITEXCOORDP2UIVPROC) ::glGetProcAddress("glMultiTexCoordP2uiv");
  glMultiTexCoordP3ui           = (PFNGLMULTITEXCOORDP3UIPROC) ::glGetProcAddress("glMultiTexCoordP3ui");
  glMultiTexCoordP3uiv          = (PFNGLMULTITEXCOORDP3UIVPROC) ::glGetProcAddress("glMultiTexCoordP3uiv");
  glMultiTexCoordP4ui           = (PFNGLMULTITEXCOORDP4UIPROC) ::glGetProcAddress("glMultiTexCoordP4ui");
  glMultiTexCoordP4uiv          = (PFNGLMULTITEXCOORDP4UIVPROC) ::glGetProcAddress("glMultiTexCoordP4uiv");
  glNormalP3ui                  = (PFNGLNORMALP3UIPROC) ::glGetProcAddress("glNormalP3ui");
  glNormalP3uiv                 = (PFNGLNORMALP3UIVPROC) ::glGetProcAddress("glNormalP3uiv");
  glColorP3ui                   = (PFNGLCOLORP3UIPROC) ::glGetProcAddress("glColorP3ui");
  glColorP3uiv                  = (PFNGLCOLORP3UIVPROC) ::glGetProcAddress("glColorP3uiv");
  glColorP4ui                   = (PFNGLCOLORP4UIPROC) ::glGetProcAddress("glColorP4ui");
  glColorP4uiv                  = (PFNGLCOLORP4UIVPROC) ::glGetProcAddress("glColorP4uiv");
  glSecondaryColorP3ui          = (PFNGLSECONDARYCOLORP3UIPROC) ::glGetProcAddress("glSecondaryColorP3ui");
  glSecondaryColorP3uiv         = (PFNGLSECONDARYCOLORP3UIVPROC) ::glGetProcAddress("glSecondaryColorP3uiv");
  return true;
}

static bool load_v_4_0() {
  if (!OGL_VERSION_4_0) return false;
  glMinSampleShading               = (PFNGLMINSAMPLESHADINGPROC) ::glGetProcAddress("glMinSampleShading");
  glBlendEquationi                 = (PFNGLBLENDEQUATIONIPROC) ::glGetProcAddress("glBlendEquationi");
  glBlendEquationSeparatei         = (PFNGLBLENDEQUATIONSEPARATEIPROC) ::glGetProcAddress("glBlendEquationSeparatei");
  glBlendFunci                     = (PFNGLBLENDFUNCIPROC) ::glGetProcAddress("glBlendFunci");
  glBlendFuncSeparatei             = (PFNGLBLENDFUNCSEPARATEIPROC) ::glGetProcAddress("glBlendFuncSeparatei");
  glDrawArraysIndirect             = (PFNGLDRAWARRAYSINDIRECTPROC) ::glGetProcAddress("glDrawArraysIndirect");
  glDrawElementsIndirect           = (PFNGLDRAWELEMENTSINDIRECTPROC) ::glGetProcAddress("glDrawElementsIndirect");
  glUniform1d                      = (PFNGLUNIFORM1DPROC) ::glGetProcAddress("glUniform1d");
  glUniform2d                      = (PFNGLUNIFORM2DPROC) ::glGetProcAddress("glUniform2d");
  glUniform3d                      = (PFNGLUNIFORM3DPROC) ::glGetProcAddress("glUniform3d");
  glUniform4d                      = (PFNGLUNIFORM4DPROC) ::glGetProcAddress("glUniform4d");
  glUniform1dv                     = (PFNGLUNIFORM1DVPROC) ::glGetProcAddress("glUniform1dv");
  glUniform2dv                     = (PFNGLUNIFORM2DVPROC) ::glGetProcAddress("glUniform2dv");
  glUniform3dv                     = (PFNGLUNIFORM3DVPROC) ::glGetProcAddress("glUniform3dv");
  glUniform4dv                     = (PFNGLUNIFORM4DVPROC) ::glGetProcAddress("glUniform4dv");
  glUniformMatrix2dv               = (PFNGLUNIFORMMATRIX2DVPROC) ::glGetProcAddress("glUniformMatrix2dv");
  glUniformMatrix3dv               = (PFNGLUNIFORMMATRIX3DVPROC) ::glGetProcAddress("glUniformMatrix3dv");
  glUniformMatrix4dv               = (PFNGLUNIFORMMATRIX4DVPROC) ::glGetProcAddress("glUniformMatrix4dv");
  glUniformMatrix2x3dv             = (PFNGLUNIFORMMATRIX2X3DVPROC) ::glGetProcAddress("glUniformMatrix2x3dv");
  glUniformMatrix2x4dv             = (PFNGLUNIFORMMATRIX2X4DVPROC) ::glGetProcAddress("glUniformMatrix2x4dv");
  glUniformMatrix3x2dv             = (PFNGLUNIFORMMATRIX3X2DVPROC) ::glGetProcAddress("glUniformMatrix3x2dv");
  glUniformMatrix3x4dv             = (PFNGLUNIFORMMATRIX3X4DVPROC) ::glGetProcAddress("glUniformMatrix3x4dv");
  glUniformMatrix4x2dv             = (PFNGLUNIFORMMATRIX4X2DVPROC) ::glGetProcAddress("glUniformMatrix4x2dv");
  glUniformMatrix4x3dv             = (PFNGLUNIFORMMATRIX4X3DVPROC) ::glGetProcAddress("glUniformMatrix4x3dv");
  glGetUniformdv                   = (PFNGLGETUNIFORMDVPROC) ::glGetProcAddress("glGetUniformdv");
  glGetSubroutineUniformLocation   = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC) ::glGetProcAddress("glGetSubroutineUniformLocation");
  glGetSubroutineIndex             = (PFNGLGETSUBROUTINEINDEXPROC) ::glGetProcAddress("glGetSubroutineIndex");
  glGetActiveSubroutineUniformiv   = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC) ::glGetProcAddress("glGetActiveSubroutineUniformiv");
  glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC) ::glGetProcAddress("glGetActiveSubroutineUniformName");
  glGetActiveSubroutineName        = (PFNGLGETACTIVESUBROUTINENAMEPROC) ::glGetProcAddress("glGetActiveSubroutineName");
  glUniformSubroutinesuiv          = (PFNGLUNIFORMSUBROUTINESUIVPROC) ::glGetProcAddress("glUniformSubroutinesuiv");
  glGetUniformSubroutineuiv        = (PFNGLGETUNIFORMSUBROUTINEUIVPROC) ::glGetProcAddress("glGetUniformSubroutineuiv");
  glGetProgramStageiv              = (PFNGLGETPROGRAMSTAGEIVPROC) ::glGetProcAddress("glGetProgramStageiv");
  glPatchParameteri                = (PFNGLPATCHPARAMETERIPROC) ::glGetProcAddress("glPatchParameteri");
  glPatchParameterfv               = (PFNGLPATCHPARAMETERFVPROC) ::glGetProcAddress("glPatchParameterfv");
  glBindTransformFeedback          = (PFNGLBINDTRANSFORMFEEDBACKPROC) ::glGetProcAddress("glBindTransformFeedback");
  glDeleteTransformFeedbacks       = (PFNGLDELETETRANSFORMFEEDBACKSPROC) ::glGetProcAddress("glDeleteTransformFeedbacks");
  glGenTransformFeedbacks          = (PFNGLGENTRANSFORMFEEDBACKSPROC) ::glGetProcAddress("glGenTransformFeedbacks");
  glIsTransformFeedback            = (PFNGLISTRANSFORMFEEDBACKPROC) ::glGetProcAddress("glIsTransformFeedback");
  glPauseTransformFeedback         = (PFNGLPAUSETRANSFORMFEEDBACKPROC) ::glGetProcAddress("glPauseTransformFeedback");
  glResumeTransformFeedback        = (PFNGLRESUMETRANSFORMFEEDBACKPROC) ::glGetProcAddress("glResumeTransformFeedback");
  glDrawTransformFeedback          = (PFNGLDRAWTRANSFORMFEEDBACKPROC) ::glGetProcAddress("glDrawTransformFeedback");
  glDrawTransformFeedbackStream    = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC) ::glGetProcAddress("glDrawTransformFeedbackStream");
  glBeginQueryIndexed              = (PFNGLBEGINQUERYINDEXEDPROC) ::glGetProcAddress("glBeginQueryIndexed");
  glEndQueryIndexed                = (PFNGLENDQUERYINDEXEDPROC) ::glGetProcAddress("glEndQueryIndexed");
  glGetQueryIndexediv              = (PFNGLGETQUERYINDEXEDIVPROC) ::glGetProcAddress("glGetQueryIndexediv");
  return true;
}

static bool load_v_4_1() {
  if (!OGL_VERSION_4_1) return false;
  glReleaseShaderCompiler     = (PFNGLRELEASESHADERCOMPILERPROC) ::glGetProcAddress("glReleaseShaderCompiler");
  glShaderBinary              = (PFNGLSHADERBINARYPROC) ::glGetProcAddress("glShaderBinary");
  glGetShaderPrecisionFormat  = (PFNGLGETSHADERPRECISIONFORMATPROC) ::glGetProcAddress("glGetShaderPrecisionFormat");
  glDepthRangef               = (PFNGLDEPTHRANGEFPROC) ::glGetProcAddress("glDepthRangef");
  glClearDepthf               = (PFNGLCLEARDEPTHFPROC) ::glGetProcAddress("glClearDepthf");
  glGetProgramBinary          = (PFNGLGETPROGRAMBINARYPROC) ::glGetProcAddress("glGetProgramBinary");
  glProgramBinary             = (PFNGLPROGRAMBINARYPROC) ::glGetProcAddress("glProgramBinary");
  glProgramParameteri         = (PFNGLPROGRAMPARAMETERIPROC) ::glGetProcAddress("glProgramParameteri");
  glUseProgramStages          = (PFNGLUSEPROGRAMSTAGESPROC) ::glGetProcAddress("glUseProgramStages");
  glActiveShaderProgram       = (PFNGLACTIVESHADERPROGRAMPROC) ::glGetProcAddress("glActiveShaderProgram");
  glCreateShaderProgramv      = (PFNGLCREATESHADERPROGRAMVPROC) ::glGetProcAddress("glCreateShaderProgramv");
  glBindProgramPipeline       = (PFNGLBINDPROGRAMPIPELINEPROC) ::glGetProcAddress("glBindProgramPipeline");
  glDeleteProgramPipelines    = (PFNGLDELETEPROGRAMPIPELINESPROC) ::glGetProcAddress("glDeleteProgramPipelines");
  glGenProgramPipelines       = (PFNGLGENPROGRAMPIPELINESPROC) ::glGetProcAddress("glGenProgramPipelines");
  glIsProgramPipeline         = (PFNGLISPROGRAMPIPELINEPROC) ::glGetProcAddress("glIsProgramPipeline");
  glGetProgramPipelineiv      = (PFNGLGETPROGRAMPIPELINEIVPROC) ::glGetProcAddress("glGetProgramPipelineiv");
  glProgramParameteri         = (PFNGLPROGRAMPARAMETERIPROC) ::glGetProcAddress("glProgramParameteri");
  glProgramUniform1i          = (PFNGLPROGRAMUNIFORM1IPROC) ::glGetProcAddress("glProgramUniform1i");
  glProgramUniform1iv         = (PFNGLPROGRAMUNIFORM1IVPROC) ::glGetProcAddress("glProgramUniform1iv");
  glProgramUniform1f          = (PFNGLPROGRAMUNIFORM1FPROC) ::glGetProcAddress("glProgramUniform1f");
  glProgramUniform1fv         = (PFNGLPROGRAMUNIFORM1FVPROC) ::glGetProcAddress("glProgramUniform1fv");
  glProgramUniform1d          = (PFNGLPROGRAMUNIFORM1DPROC) ::glGetProcAddress("glProgramUniform1d");
  glProgramUniform1dv         = (PFNGLPROGRAMUNIFORM1DVPROC) ::glGetProcAddress("glProgramUniform1dv");
  glProgramUniform1ui         = (PFNGLPROGRAMUNIFORM1UIPROC) ::glGetProcAddress("glProgramUniform1ui");
  glProgramUniform1uiv        = (PFNGLPROGRAMUNIFORM1UIVPROC) ::glGetProcAddress("glProgramUniform1uiv");
  glProgramUniform2i          = (PFNGLPROGRAMUNIFORM2IPROC) ::glGetProcAddress("glProgramUniform2i");
  glProgramUniform2iv         = (PFNGLPROGRAMUNIFORM2IVPROC) ::glGetProcAddress("glProgramUniform2iv");
  glProgramUniform2f          = (PFNGLPROGRAMUNIFORM2FPROC) ::glGetProcAddress("glProgramUniform2f");
  glProgramUniform2fv         = (PFNGLPROGRAMUNIFORM2FVPROC) ::glGetProcAddress("glProgramUniform2fv");
  glProgramUniform2d          = (PFNGLPROGRAMUNIFORM2DPROC) ::glGetProcAddress("glProgramUniform2d");
  glProgramUniform2dv         = (PFNGLPROGRAMUNIFORM2DVPROC) ::glGetProcAddress("glProgramUniform2dv");
  glProgramUniform2ui         = (PFNGLPROGRAMUNIFORM2UIPROC) ::glGetProcAddress("glProgramUniform2ui");
  glProgramUniform2uiv        = (PFNGLPROGRAMUNIFORM2UIVPROC) ::glGetProcAddress("glProgramUniform2uiv");
  glProgramUniform3i          = (PFNGLPROGRAMUNIFORM3IPROC) ::glGetProcAddress("glProgramUniform3i");
  glProgramUniform3iv         = (PFNGLPROGRAMUNIFORM3IVPROC) ::glGetProcAddress("glProgramUniform3iv");
  glProgramUniform3f          = (PFNGLPROGRAMUNIFORM3FPROC) ::glGetProcAddress("glProgramUniform3f");
  glProgramUniform3fv         = (PFNGLPROGRAMUNIFORM3FVPROC) ::glGetProcAddress("glProgramUniform3fv");
  glProgramUniform3d          = (PFNGLPROGRAMUNIFORM3DPROC) ::glGetProcAddress("glProgramUniform3d");
  glProgramUniform3dv         = (PFNGLPROGRAMUNIFORM3DVPROC) ::glGetProcAddress("glProgramUniform3dv");
  glProgramUniform3ui         = (PFNGLPROGRAMUNIFORM3UIPROC) ::glGetProcAddress("glProgramUniform3ui");
  glProgramUniform3uiv        = (PFNGLPROGRAMUNIFORM3UIVPROC) ::glGetProcAddress("glProgramUniform3uiv");
  glProgramUniform4i          = (PFNGLPROGRAMUNIFORM4IPROC) ::glGetProcAddress("glProgramUniform4i");
  glProgramUniform4iv         = (PFNGLPROGRAMUNIFORM4IVPROC) ::glGetProcAddress("glProgramUniform4iv");
  glProgramUniform4f          = (PFNGLPROGRAMUNIFORM4FPROC) ::glGetProcAddress("glProgramUniform4f");
  glProgramUniform4fv         = (PFNGLPROGRAMUNIFORM4FVPROC) ::glGetProcAddress("glProgramUniform4fv");
  glProgramUniform4d          = (PFNGLPROGRAMUNIFORM4DPROC) ::glGetProcAddress("glProgramUniform4d");
  glProgramUniform4dv         = (PFNGLPROGRAMUNIFORM4DVPROC) ::glGetProcAddress("glProgramUniform4dv");
  glProgramUniform4ui         = (PFNGLPROGRAMUNIFORM4UIPROC) ::glGetProcAddress("glProgramUniform4ui");
  glProgramUniform4uiv        = (PFNGLPROGRAMUNIFORM4UIVPROC) ::glGetProcAddress("glProgramUniform4uiv");
  glProgramUniformMatrix2fv   = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC) ::glGetProcAddress("glProgramUniformMatrix2fv");
  glProgramUniformMatrix3fv   = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC) ::glGetProcAddress("glProgramUniformMatrix3fv");
  glProgramUniformMatrix4fv   = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC) ::glGetProcAddress("glProgramUniformMatrix4fv");
  glProgramUniformMatrix2dv   = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC) ::glGetProcAddress("glProgramUniformMatrix2dv");
  glProgramUniformMatrix3dv   = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC) ::glGetProcAddress("glProgramUniformMatrix3dv");
  glProgramUniformMatrix4dv   = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC) ::glGetProcAddress("glProgramUniformMatrix4dv");
  glProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) ::glGetProcAddress("glProgramUniformMatrix2x3fv");
  glProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) ::glGetProcAddress("glProgramUniformMatrix3x2fv");
  glProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) ::glGetProcAddress("glProgramUniformMatrix2x4fv");
  glProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) ::glGetProcAddress("glProgramUniformMatrix4x2fv");
  glProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) ::glGetProcAddress("glProgramUniformMatrix3x4fv");
  glProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) ::glGetProcAddress("glProgramUniformMatrix4x3fv");
  glProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) ::glGetProcAddress("glProgramUniformMatrix2x3dv");
  glProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) ::glGetProcAddress("glProgramUniformMatrix3x2dv");
  glProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) ::glGetProcAddress("glProgramUniformMatrix2x4dv");
  glProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) ::glGetProcAddress("glProgramUniformMatrix4x2dv");
  glProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) ::glGetProcAddress("glProgramUniformMatrix3x4dv");
  glProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) ::glGetProcAddress("glProgramUniformMatrix4x3dv");
  glValidateProgramPipeline   = (PFNGLVALIDATEPROGRAMPIPELINEPROC) ::glGetProcAddress("glValidateProgramPipeline");
  glGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC) ::glGetProcAddress("glGetProgramPipelineInfoLog");
  glVertexAttribL1d           = (PFNGLVERTEXATTRIBL1DPROC) ::glGetProcAddress("glVertexAttribL1d");
  glVertexAttribL2d           = (PFNGLVERTEXATTRIBL2DPROC) ::glGetProcAddress("glVertexAttribL2d");
  glVertexAttribL3d           = (PFNGLVERTEXATTRIBL3DPROC) ::glGetProcAddress("glVertexAttribL3d");
  glVertexAttribL4d           = (PFNGLVERTEXATTRIBL4DPROC) ::glGetProcAddress("glVertexAttribL4d");
  glVertexAttribL1dv          = (PFNGLVERTEXATTRIBL1DVPROC) ::glGetProcAddress("glVertexAttribL1dv");
  glVertexAttribL2dv          = (PFNGLVERTEXATTRIBL2DVPROC) ::glGetProcAddress("glVertexAttribL2dv");
  glVertexAttribL3dv          = (PFNGLVERTEXATTRIBL3DVPROC) ::glGetProcAddress("glVertexAttribL3dv");
  glVertexAttribL4dv          = (PFNGLVERTEXATTRIBL4DVPROC) ::glGetProcAddress("glVertexAttribL4dv");
  glVertexAttribLPointer      = (PFNGLVERTEXATTRIBLPOINTERPROC) ::glGetProcAddress("glVertexAttribLPointer");
  glGetVertexAttribLdv        = (PFNGLGETVERTEXATTRIBLDVPROC) ::glGetProcAddress("glGetVertexAttribLdv");
  glViewportArrayv            = (PFNGLVIEWPORTARRAYVPROC) ::glGetProcAddress("glViewportArrayv");
  glViewportIndexedf          = (PFNGLVIEWPORTINDEXEDFPROC) ::glGetProcAddress("glViewportIndexedf");
  glViewportIndexedfv         = (PFNGLVIEWPORTINDEXEDFVPROC) ::glGetProcAddress("glViewportIndexedfv");
  glScissorArrayv             = (PFNGLSCISSORARRAYVPROC) ::glGetProcAddress("glScissorArrayv");
  glScissorIndexed            = (PFNGLSCISSORINDEXEDPROC) ::glGetProcAddress("glScissorIndexed");
  glScissorIndexedv           = (PFNGLSCISSORINDEXEDVPROC) ::glGetProcAddress("glScissorIndexedv");
  glDepthRangeArrayv          = (PFNGLDEPTHRANGEARRAYVPROC) ::glGetProcAddress("glDepthRangeArrayv");
  glDepthRangeIndexed         = (PFNGLDEPTHRANGEINDEXEDPROC) ::glGetProcAddress("glDepthRangeIndexed");
  glGetFloati_v               = (PFNGLGETFLOATI_VPROC) ::glGetProcAddress("glGetFloati_v");
  glGetDoublei_v              = (PFNGLGETDOUBLEI_VPROC) ::glGetProcAddress("glGetDoublei_v");
  return true;
}

static bool load_v_4_2() {
  if (!OGL_VERSION_4_2) return false;
  glDrawArraysInstancedBaseInstance             = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC) ::glGetProcAddress("glDrawArraysInstancedBaseInstance");
  glDrawElementsInstancedBaseInstance           = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC) ::glGetProcAddress("glDrawElementsInstancedBaseInstance");
  glDrawElementsInstancedBaseVertexBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC) ::glGetProcAddress("glDrawElementsInstancedBaseVertexBaseInstance");
  glGetInternalformativ                         = (PFNGLGETINTERNALFORMATIVPROC) ::glGetProcAddress("glGetInternalformativ");
  glGetActiveAtomicCounterBufferiv              = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC) ::glGetProcAddress("glGetActiveAtomicCounterBufferiv");
  glBindImageTexture                            = (PFNGLBINDIMAGETEXTUREPROC) ::glGetProcAddress("glBindImageTexture");
  glMemoryBarrier                               = (PFNGLMEMORYBARRIERPROC) ::glGetProcAddress("glMemoryBarrier");
  glTexStorage1D                                = (PFNGLTEXSTORAGE1DPROC) ::glGetProcAddress("glTexStorage1D");
  glTexStorage2D                                = (PFNGLTEXSTORAGE2DPROC) ::glGetProcAddress("glTexStorage2D");
  glTexStorage3D                                = (PFNGLTEXSTORAGE3DPROC) ::glGetProcAddress("glTexStorage3D");
  glDrawTransformFeedbackInstanced              = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC) ::glGetProcAddress("glDrawTransformFeedbackInstanced");
  glDrawTransformFeedbackStreamInstanced        = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC) ::glGetProcAddress("glDrawTransformFeedbackStreamInstanced");
  return true;
}

static bool load_v_4_3() {
  if (!OGL_VERSION_4_3) return false;
  glClearBufferData                 = (PFNGLCLEARBUFFERDATAPROC) ::glGetProcAddress("glClearBufferData");
  glClearBufferSubData              = (PFNGLCLEARBUFFERSUBDATAPROC) ::glGetProcAddress("glClearBufferSubData");
  glDispatchCompute                 = (PFNGLDISPATCHCOMPUTEPROC) ::glGetProcAddress("glDispatchCompute");
  glDispatchComputeIndirect         = (PFNGLDISPATCHCOMPUTEINDIRECTPROC) ::glGetProcAddress("glDispatchComputeIndirect");
  glCopyImageSubData                = (PFNGLCOPYIMAGESUBDATAPROC) ::glGetProcAddress("glCopyImageSubData");
  glFramebufferParameteri           = (PFNGLFRAMEBUFFERPARAMETERIPROC) ::glGetProcAddress("glFramebufferParameteri");
  glGetFramebufferParameteriv       = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC) ::glGetProcAddress("glGetFramebufferParameteriv");
  glGetInternalformati64v           = (PFNGLGETINTERNALFORMATI64VPROC) ::glGetProcAddress("glGetInternalformati64v");
  glInvalidateTexSubImage           = (PFNGLINVALIDATETEXSUBIMAGEPROC) ::glGetProcAddress("glInvalidateTexSubImage");
  glInvalidateTexImage              = (PFNGLINVALIDATETEXIMAGEPROC) ::glGetProcAddress("glInvalidateTexImage");
  glInvalidateBufferSubData         = (PFNGLINVALIDATEBUFFERSUBDATAPROC) ::glGetProcAddress("glInvalidateBufferSubData");
  glInvalidateBufferData            = (PFNGLINVALIDATEBUFFERDATAPROC) ::glGetProcAddress("glInvalidateBufferData");
  glInvalidateFramebuffer           = (PFNGLINVALIDATEFRAMEBUFFERPROC) ::glGetProcAddress("glInvalidateFramebuffer");
  glInvalidateSubFramebuffer        = (PFNGLINVALIDATESUBFRAMEBUFFERPROC) ::glGetProcAddress("glInvalidateSubFramebuffer");
  glMultiDrawArraysIndirect         = (PFNGLMULTIDRAWARRAYSINDIRECTPROC) ::glGetProcAddress("glMultiDrawArraysIndirect");
  glMultiDrawElementsIndirect       = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC) ::glGetProcAddress("glMultiDrawElementsIndirect");
  glGetProgramInterfaceiv           = (PFNGLGETPROGRAMINTERFACEIVPROC) ::glGetProcAddress("glGetProgramInterfaceiv");
  glGetProgramResourceIndex         = (PFNGLGETPROGRAMRESOURCEINDEXPROC) ::glGetProcAddress("glGetProgramResourceIndex");
  glGetProgramResourceName          = (PFNGLGETPROGRAMRESOURCENAMEPROC) ::glGetProcAddress("glGetProgramResourceName");
  glGetProgramResourceiv            = (PFNGLGETPROGRAMRESOURCEIVPROC) ::glGetProcAddress("glGetProgramResourceiv");
  glGetProgramResourceLocation      = (PFNGLGETPROGRAMRESOURCELOCATIONPROC) ::glGetProcAddress("glGetProgramResourceLocation");
  glGetProgramResourceLocationIndex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC) ::glGetProcAddress("glGetProgramResourceLocationIndex");
  glShaderStorageBlockBinding       = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC) ::glGetProcAddress("glShaderStorageBlockBinding");
  glTexBufferRange                  = (PFNGLTEXBUFFERRANGEPROC) ::glGetProcAddress("glTexBufferRange");
  glTexStorage2DMultisample         = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC) ::glGetProcAddress("glTexStorage2DMultisample");
  glTexStorage3DMultisample         = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC) ::glGetProcAddress("glTexStorage3DMultisample");
  glTextureView                     = (PFNGLTEXTUREVIEWPROC) ::glGetProcAddress("glTextureView");
  glBindVertexBuffer                = (PFNGLBINDVERTEXBUFFERPROC) ::glGetProcAddress("glBindVertexBuffer");
  glVertexAttribFormat              = (PFNGLVERTEXATTRIBFORMATPROC) ::glGetProcAddress("glVertexAttribFormat");
  glVertexAttribIFormat             = (PFNGLVERTEXATTRIBIFORMATPROC) ::glGetProcAddress("glVertexAttribIFormat");
  glVertexAttribLFormat             = (PFNGLVERTEXATTRIBLFORMATPROC) ::glGetProcAddress("glVertexAttribLFormat");
  glVertexAttribBinding             = (PFNGLVERTEXATTRIBBINDINGPROC) ::glGetProcAddress("glVertexAttribBinding");
  glVertexBindingDivisor            = (PFNGLVERTEXBINDINGDIVISORPROC) ::glGetProcAddress("glVertexBindingDivisor");
  glDebugMessageControl             = (PFNGLDEBUGMESSAGECONTROLPROC) ::glGetProcAddress("glDebugMessageControl");
  glDebugMessageInsert              = (PFNGLDEBUGMESSAGEINSERTPROC) ::glGetProcAddress("glDebugMessageInsert");
  glDebugMessageCallback            = (PFNGLDEBUGMESSAGECALLBACKPROC) ::glGetProcAddress("glDebugMessageCallback");
  glGetDebugMessageLog              = (PFNGLGETDEBUGMESSAGELOGPROC) ::glGetProcAddress("glGetDebugMessageLog");
  glPushDebugGroup                  = (PFNGLPUSHDEBUGGROUPPROC) ::glGetProcAddress("glPushDebugGroup");
  glPopDebugGroup                   = (PFNGLPOPDEBUGGROUPPROC) ::glGetProcAddress("glPopDebugGroup");
  glObjectLabel                     = (PFNGLOBJECTLABELPROC) ::glGetProcAddress("glObjectLabel");
  glGetObjectLabel                  = (PFNGLGETOBJECTLABELPROC) ::glGetProcAddress("glGetObjectLabel");
  glObjectPtrLabel                  = (PFNGLOBJECTPTRLABELPROC) ::glGetProcAddress("glObjectPtrLabel");
  glGetObjectPtrLabel               = (PFNGLGETOBJECTPTRLABELPROC) ::glGetProcAddress("glGetObjectPtrLabel");
  glGetPointerv                     = (PFNGLGETPOINTERVPROC) ::glGetProcAddress("glGetPointerv");
  return true;
}

static bool load_v_4_4() {
  if (!OGL_VERSION_4_4) return false;
  glBufferStorage     = (PFNGLBUFFERSTORAGEPROC) ::glGetProcAddress("glBufferStorage");
  glClearTexImage     = (PFNGLCLEARTEXIMAGEPROC) ::glGetProcAddress("glClearTexImage");
  glClearTexSubImage  = (PFNGLCLEARTEXSUBIMAGEPROC) ::glGetProcAddress("glClearTexSubImage");
  glBindBuffersBase   = (PFNGLBINDBUFFERSBASEPROC) ::glGetProcAddress("glBindBuffersBase");
  glBindBuffersRange  = (PFNGLBINDBUFFERSRANGEPROC) ::glGetProcAddress("glBindBuffersRange");
  glBindTextures      = (PFNGLBINDTEXTURESPROC) ::glGetProcAddress("glBindTextures");
  glBindSamplers      = (PFNGLBINDSAMPLERSPROC) ::glGetProcAddress("glBindSamplers");
  glBindImageTextures = (PFNGLBINDIMAGETEXTURESPROC) ::glGetProcAddress("glBindImageTextures");
  glBindVertexBuffers = (PFNGLBINDVERTEXBUFFERSPROC) ::glGetProcAddress("glBindVertexBuffers");
  return true;
}

static bool load_v_4_5() {
  if (!OGL_VERSION_4_5) return false;
  glClipControl                              = (PFNGLCLIPCONTROLPROC) ::glGetProcAddress("glClipControl");
  glCreateTransformFeedbacks                 = (PFNGLCREATETRANSFORMFEEDBACKSPROC) ::glGetProcAddress("glCreateTransformFeedbacks");
  glTransformFeedbackBufferBase              = (PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC) ::glGetProcAddress("glTransformFeedbackBufferBase");
  glTransformFeedbackBufferRange             = (PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC) ::glGetProcAddress("glTransformFeedbackBufferRange");
  glGetTransformFeedbackiv                   = (PFNGLGETTRANSFORMFEEDBACKIVPROC) ::glGetProcAddress("glGetTransformFeedbackiv");
  glGetTransformFeedbacki_v                  = (PFNGLGETTRANSFORMFEEDBACKI_VPROC) ::glGetProcAddress("glGetTransformFeedbacki_v");
  glGetTransformFeedbacki64_v                = (PFNGLGETTRANSFORMFEEDBACKI64_VPROC) ::glGetProcAddress("glGetTransformFeedbacki64_v");
  glCreateBuffers                            = (PFNGLCREATEBUFFERSPROC) ::glGetProcAddress("glCreateBuffers");
  glNamedBufferStorage                       = (PFNGLNAMEDBUFFERSTORAGEPROC) ::glGetProcAddress("glNamedBufferStorage");
  glNamedBufferData                          = (PFNGLNAMEDBUFFERDATAPROC) ::glGetProcAddress("glNamedBufferData");
  glNamedBufferSubData                       = (PFNGLNAMEDBUFFERSUBDATAPROC) ::glGetProcAddress("glNamedBufferSubData");
  glCopyNamedBufferSubData                   = (PFNGLCOPYNAMEDBUFFERSUBDATAPROC) ::glGetProcAddress("glCopyNamedBufferSubData");
  glClearNamedBufferData                     = (PFNGLCLEARNAMEDBUFFERDATAPROC) ::glGetProcAddress("glClearNamedBufferData");
  glClearNamedBufferSubData                  = (PFNGLCLEARNAMEDBUFFERSUBDATAPROC) ::glGetProcAddress("glClearNamedBufferSubData");
  glMapNamedBuffer                           = (PFNGLMAPNAMEDBUFFERPROC) ::glGetProcAddress("glMapNamedBuffer");
  glMapNamedBufferRange                      = (PFNGLMAPNAMEDBUFFERRANGEPROC) ::glGetProcAddress("glMapNamedBufferRange");
  glUnmapNamedBuffer                         = (PFNGLUNMAPNAMEDBUFFERPROC) ::glGetProcAddress("glUnmapNamedBuffer");
  glFlushMappedNamedBufferRange              = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC) ::glGetProcAddress("glFlushMappedNamedBufferRange");
  glGetNamedBufferParameteriv                = (PFNGLGETNAMEDBUFFERPARAMETERIVPROC) ::glGetProcAddress("glGetNamedBufferParameteriv");
  glGetNamedBufferParameteri64v              = (PFNGLGETNAMEDBUFFERPARAMETERI64VPROC) ::glGetProcAddress("glGetNamedBufferParameteri64v");
  glGetNamedBufferPointerv                   = (PFNGLGETNAMEDBUFFERPOINTERVPROC) ::glGetProcAddress("glGetNamedBufferPointerv");
  glGetNamedBufferSubData                    = (PFNGLGETNAMEDBUFFERSUBDATAPROC) ::glGetProcAddress("glGetNamedBufferSubData");
  glCreateFramebuffers                       = (PFNGLCREATEFRAMEBUFFERSPROC) ::glGetProcAddress("glCreateFramebuffers");
  glNamedFramebufferRenderbuffer             = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC) ::glGetProcAddress("glNamedFramebufferRenderbuffer");
  glNamedFramebufferParameteri               = (PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC) ::glGetProcAddress("glNamedFramebufferParameteri");
  glNamedFramebufferTexture                  = (PFNGLNAMEDFRAMEBUFFERTEXTUREPROC) ::glGetProcAddress("glNamedFramebufferTexture");
  glNamedFramebufferTextureLayer             = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC) ::glGetProcAddress("glNamedFramebufferTextureLayer");
  glNamedFramebufferDrawBuffer               = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC) ::glGetProcAddress("glNamedFramebufferDrawBuffer");
  glNamedFramebufferDrawBuffers              = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC) ::glGetProcAddress("glNamedFramebufferDrawBuffers");
  glNamedFramebufferReadBuffer               = (PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC) ::glGetProcAddress("glNamedFramebufferReadBuffer");
  glInvalidateNamedFramebufferData           = (PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC) ::glGetProcAddress("glInvalidateNamedFramebufferData");
  glInvalidateNamedFramebufferSubData        = (PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC) ::glGetProcAddress("glInvalidateNamedFramebufferSubData");
  glClearNamedFramebufferiv                  = (PFNGLCLEARNAMEDFRAMEBUFFERIVPROC) ::glGetProcAddress("glClearNamedFramebufferiv");
  glClearNamedFramebufferuiv                 = (PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC) ::glGetProcAddress("glClearNamedFramebufferuiv");
  glClearNamedFramebufferfv                  = (PFNGLCLEARNAMEDFRAMEBUFFERFVPROC) ::glGetProcAddress("glClearNamedFramebufferfv");
  glClearNamedFramebufferfi                  = (PFNGLCLEARNAMEDFRAMEBUFFERFIPROC) ::glGetProcAddress("glClearNamedFramebufferfi");
  glBlitNamedFramebuffer                     = (PFNGLBLITNAMEDFRAMEBUFFERPROC) ::glGetProcAddress("glBlitNamedFramebuffer");
  glCheckNamedFramebufferStatus              = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC) ::glGetProcAddress("glCheckNamedFramebufferStatus");
  glGetNamedFramebufferParameteriv           = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC) ::glGetProcAddress("glGetNamedFramebufferParameteriv");
  glGetNamedFramebufferAttachmentParameteriv = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC) ::glGetProcAddress("glGetNamedFramebufferAttachmentParameteriv");
  glCreateRenderbuffers                      = (PFNGLCREATERENDERBUFFERSPROC) ::glGetProcAddress("glCreateRenderbuffers");
  glNamedRenderbufferStorage                 = (PFNGLNAMEDRENDERBUFFERSTORAGEPROC) ::glGetProcAddress("glNamedRenderbufferStorage");
  glNamedRenderbufferStorageMultisample      = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC) ::glGetProcAddress("glNamedRenderbufferStorageMultisample");
  glGetNamedRenderbufferParameteriv          = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC) ::glGetProcAddress("glGetNamedRenderbufferParameteriv");
  glCreateTextures                           = (PFNGLCREATETEXTURESPROC) ::glGetProcAddress("glCreateTextures");
  glTextureBuffer                            = (PFNGLTEXTUREBUFFERPROC) ::glGetProcAddress("glTextureBuffer");
  glTextureBufferRange                       = (PFNGLTEXTUREBUFFERRANGEPROC) ::glGetProcAddress("glTextureBufferRange");
  glTextureStorage1D                         = (PFNGLTEXTURESTORAGE1DPROC) ::glGetProcAddress("glTextureStorage1D");
  glTextureStorage2D                         = (PFNGLTEXTURESTORAGE2DPROC) ::glGetProcAddress("glTextureStorage2D");
  glTextureStorage3D                         = (PFNGLTEXTURESTORAGE3DPROC) ::glGetProcAddress("glTextureStorage3D");
  glTextureStorage2DMultisample              = (PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC) ::glGetProcAddress("glTextureStorage2DMultisample");
  glTextureStorage3DMultisample              = (PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC) ::glGetProcAddress("glTextureStorage3DMultisample");
  glTextureSubImage1D                        = (PFNGLTEXTURESUBIMAGE1DPROC) ::glGetProcAddress("glTextureSubImage1D");
  glTextureSubImage2D                        = (PFNGLTEXTURESUBIMAGE2DPROC) ::glGetProcAddress("glTextureSubImage2D");
  glTextureSubImage3D                        = (PFNGLTEXTURESUBIMAGE3DPROC) ::glGetProcAddress("glTextureSubImage3D");
  glCompressedTextureSubImage1D              = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC) ::glGetProcAddress("glCompressedTextureSubImage1D");
  glCompressedTextureSubImage2D              = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC) ::glGetProcAddress("glCompressedTextureSubImage2D");
  glCompressedTextureSubImage3D              = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC) ::glGetProcAddress("glCompressedTextureSubImage3D");
  glCopyTextureSubImage1D                    = (PFNGLCOPYTEXTURESUBIMAGE1DPROC) ::glGetProcAddress("glCopyTextureSubImage1D");
  glCopyTextureSubImage2D                    = (PFNGLCOPYTEXTURESUBIMAGE2DPROC) ::glGetProcAddress("glCopyTextureSubImage2D");
  glCopyTextureSubImage3D                    = (PFNGLCOPYTEXTURESUBIMAGE3DPROC) ::glGetProcAddress("glCopyTextureSubImage3D");
  glTextureParameterf                        = (PFNGLTEXTUREPARAMETERFPROC) ::glGetProcAddress("glTextureParameterf");
  glTextureParameterfv                       = (PFNGLTEXTUREPARAMETERFVPROC) ::glGetProcAddress("glTextureParameterfv");
  glTextureParameteri                        = (PFNGLTEXTUREPARAMETERIPROC) ::glGetProcAddress("glTextureParameteri");
  glTextureParameterIiv                      = (PFNGLTEXTUREPARAMETERIIVPROC) ::glGetProcAddress("glTextureParameterIiv");
  glTextureParameterIuiv                     = (PFNGLTEXTUREPARAMETERIUIVPROC) ::glGetProcAddress("glTextureParameterIuiv");
  glTextureParameteriv                       = (PFNGLTEXTUREPARAMETERIVPROC) ::glGetProcAddress("glTextureParameteriv");
  glGenerateTextureMipmap                    = (PFNGLGENERATETEXTUREMIPMAPPROC) ::glGetProcAddress("glGenerateTextureMipmap");
  glBindTextureUnit                          = (PFNGLBINDTEXTUREUNITPROC) ::glGetProcAddress("glBindTextureUnit");
  glGetTextureImage                          = (PFNGLGETTEXTUREIMAGEPROC) ::glGetProcAddress("glGetTextureImage");
  glGetCompressedTextureImage                = (PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC) ::glGetProcAddress("glGetCompressedTextureImage");
  glGetTextureLevelParameterfv               = (PFNGLGETTEXTURELEVELPARAMETERFVPROC) ::glGetProcAddress("glGetTextureLevelParameterfv");
  glGetTextureLevelParameteriv               = (PFNGLGETTEXTURELEVELPARAMETERIVPROC) ::glGetProcAddress("glGetTextureLevelParameteriv");
  glGetTextureParameterfv                    = (PFNGLGETTEXTUREPARAMETERFVPROC) ::glGetProcAddress("glGetTextureParameterfv");
  glGetTextureParameterIiv                   = (PFNGLGETTEXTUREPARAMETERIIVPROC) ::glGetProcAddress("glGetTextureParameterIiv");
  glGetTextureParameterIuiv                  = (PFNGLGETTEXTUREPARAMETERIUIVPROC) ::glGetProcAddress("glGetTextureParameterIuiv");
  glGetTextureParameteriv                    = (PFNGLGETTEXTUREPARAMETERIVPROC) ::glGetProcAddress("glGetTextureParameteriv");
  glCreateVertexArrays                       = (PFNGLCREATEVERTEXARRAYSPROC) ::glGetProcAddress("glCreateVertexArrays");
  glDisableVertexArrayAttrib                 = (PFNGLDISABLEVERTEXARRAYATTRIBPROC) ::glGetProcAddress("glDisableVertexArrayAttrib");
  glEnableVertexArrayAttrib                  = (PFNGLENABLEVERTEXARRAYATTRIBPROC) ::glGetProcAddress("glEnableVertexArrayAttrib");
  glVertexArrayElementBuffer                 = (PFNGLVERTEXARRAYELEMENTBUFFERPROC) ::glGetProcAddress("glVertexArrayElementBuffer");
  glVertexArrayVertexBuffer                  = (PFNGLVERTEXARRAYVERTEXBUFFERPROC) ::glGetProcAddress("glVertexArrayVertexBuffer");
  glVertexArrayVertexBuffers                 = (PFNGLVERTEXARRAYVERTEXBUFFERSPROC) ::glGetProcAddress("glVertexArrayVertexBuffers");
  glVertexArrayAttribBinding                 = (PFNGLVERTEXARRAYATTRIBBINDINGPROC) ::glGetProcAddress("glVertexArrayAttribBinding");
  glVertexArrayAttribFormat                  = (PFNGLVERTEXARRAYATTRIBFORMATPROC) ::glGetProcAddress("glVertexArrayAttribFormat");
  glVertexArrayAttribIFormat                 = (PFNGLVERTEXARRAYATTRIBIFORMATPROC) ::glGetProcAddress("glVertexArrayAttribIFormat");
  glVertexArrayAttribLFormat                 = (PFNGLVERTEXARRAYATTRIBLFORMATPROC) ::glGetProcAddress("glVertexArrayAttribLFormat");
  glVertexArrayBindingDivisor                = (PFNGLVERTEXARRAYBINDINGDIVISORPROC) ::glGetProcAddress("glVertexArrayBindingDivisor");
  glGetVertexArrayiv                         = (PFNGLGETVERTEXARRAYIVPROC) ::glGetProcAddress("glGetVertexArrayiv");
  glGetVertexArrayIndexediv                  = (PFNGLGETVERTEXARRAYINDEXEDIVPROC) ::glGetProcAddress("glGetVertexArrayIndexediv");
  glGetVertexArrayIndexed64iv                = (PFNGLGETVERTEXARRAYINDEXED64IVPROC) ::glGetProcAddress("glGetVertexArrayIndexed64iv");
  glCreateSamplers                           = (PFNGLCREATESAMPLERSPROC) ::glGetProcAddress("glCreateSamplers");
  glCreateProgramPipelines                   = (PFNGLCREATEPROGRAMPIPELINESPROC) ::glGetProcAddress("glCreateProgramPipelines");
  glCreateQueries                            = (PFNGLCREATEQUERIESPROC) ::glGetProcAddress("glCreateQueries");
  glGetQueryBufferObjecti64v                 = (PFNGLGETQUERYBUFFEROBJECTI64VPROC) ::glGetProcAddress("glGetQueryBufferObjecti64v");
  glGetQueryBufferObjectiv                   = (PFNGLGETQUERYBUFFEROBJECTIVPROC) ::glGetProcAddress("glGetQueryBufferObjectiv");
  glGetQueryBufferObjectui64v                = (PFNGLGETQUERYBUFFEROBJECTUI64VPROC) ::glGetProcAddress("glGetQueryBufferObjectui64v");
  glGetQueryBufferObjectuiv                  = (PFNGLGETQUERYBUFFEROBJECTUIVPROC) ::glGetProcAddress("glGetQueryBufferObjectuiv");
  glMemoryBarrierByRegion                    = (PFNGLMEMORYBARRIERBYREGIONPROC) ::glGetProcAddress("glMemoryBarrierByRegion");
  glGetTextureSubImage                       = (PFNGLGETTEXTURESUBIMAGEPROC) ::glGetProcAddress("glGetTextureSubImage");
  glGetCompressedTextureSubImage             = (PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC) ::glGetProcAddress("glGetCompressedTextureSubImage");
  glGetGraphicsResetStatus                   = (PFNGLGETGRAPHICSRESETSTATUSPROC) ::glGetProcAddress("glGetGraphicsResetStatus");
  glGetnCompressedTexImage                   = (PFNGLGETNCOMPRESSEDTEXIMAGEPROC) ::glGetProcAddress("glGetnCompressedTexImage");
  glGetnTexImage                             = (PFNGLGETNTEXIMAGEPROC) ::glGetProcAddress("glGetnTexImage");
  glGetnUniformdv                            = (PFNGLGETNUNIFORMDVPROC) ::glGetProcAddress("glGetnUniformdv");
  glGetnUniformfv                            = (PFNGLGETNUNIFORMFVPROC) ::glGetProcAddress("glGetnUniformfv");
  glGetnUniformiv                            = (PFNGLGETNUNIFORMIVPROC) ::glGetProcAddress("glGetnUniformiv");
  glGetnUniformuiv                           = (PFNGLGETNUNIFORMUIVPROC) ::glGetProcAddress("glGetnUniformuiv");
  glReadnPixels                              = (PFNGLREADNPIXELSPROC) ::glGetProcAddress("glReadnPixels");
  glGetnMapdv                                = (PFNGLGETNMAPDVPROC) ::glGetProcAddress("glGetnMapdv");
  glGetnMapfv                                = (PFNGLGETNMAPFVPROC) ::glGetProcAddress("glGetnMapfv");
  glGetnMapiv                                = (PFNGLGETNMAPIVPROC) ::glGetProcAddress("glGetnMapiv");
  glGetnPixelMapfv                           = (PFNGLGETNPIXELMAPFVPROC) ::glGetProcAddress("glGetnPixelMapfv");
  glGetnPixelMapuiv                          = (PFNGLGETNPIXELMAPUIVPROC) ::glGetProcAddress("glGetnPixelMapuiv");
  glGetnPixelMapusv                          = (PFNGLGETNPIXELMAPUSVPROC) ::glGetProcAddress("glGetnPixelMapusv");
  glGetnPolygonStipple                       = (PFNGLGETNPOLYGONSTIPPLEPROC) ::glGetProcAddress("glGetnPolygonStipple");
  glGetnColorTable                           = (PFNGLGETNCOLORTABLEPROC) ::glGetProcAddress("glGetnColorTable");
  glGetnConvolutionFilter                    = (PFNGLGETNCONVOLUTIONFILTERPROC) ::glGetProcAddress("glGetnConvolutionFilter");
  glGetnSeparableFilter                      = (PFNGLGETNSEPARABLEFILTERPROC) ::glGetProcAddress("glGetnSeparableFilter");
  glGetnHistogram                            = (PFNGLGETNHISTOGRAMPROC) ::glGetProcAddress("glGetnHistogram");
  glGetnMinmax                               = (PFNGLGETNMINMAXPROC) ::glGetProcAddress("glGetnMinmax");
  glTextureBarrier                           = (PFNGLTEXTUREBARRIERPROC) ::glGetProcAddress("glTextureBarrier");
  return true;
}

static bool load_v_4_6() {
  if (!OGL_VERSION_4_6) return false;
  glSpecializeShader               = (PFNGLSPECIALIZESHADERPROC) ::glGetProcAddress("glSpecializeShader");
  glMultiDrawArraysIndirectCount   = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC) ::glGetProcAddress("glMultiDrawArraysIndirectCount");
  glMultiDrawElementsIndirectCount = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC) ::glGetProcAddress("glMultiDrawElementsIndirectCount");
  glPolygonOffsetClamp             = (PFNGLPOLYGONOFFSETCLAMPPROC) ::glGetProcAddress("glPolygonOffsetClamp");
  return true;
}

static int load_exts() {
  GLint nExts   = 0;
  GLint nLoaded = 0;
  ::glGetIntegerv(GL_EXTENSIONS, &nExts);
  for (GLint i = 0; i < nExts; i++) {
    const char* szExtName = (const char*) ::glGetStringi(GL_EXTENSIONS, i);
    
    // @todo: load ext by name...
  }
  
  return nLoaded;
}

static bool load_version(int major, int minor) {
  OGL_VERSION_MAJOR = major;
  OGL_VERSION_MINOR = minor;
  OGL_VERSION_1_0   = (major == 1 && minor >= 0) || major > 1;
  OGL_VERSION_1_1   = (major == 1 && minor >= 1) || major > 1;
  OGL_VERSION_1_2   = (major == 1 && minor >= 2) || major > 1;
  OGL_VERSION_1_3   = (major == 1 && minor >= 3) || major > 1;
  OGL_VERSION_1_4   = (major == 1 && minor >= 4) || major > 1;
  OGL_VERSION_1_5   = (major == 1 && minor >= 5) || major > 1;
  OGL_VERSION_2_0   = (major == 2 && minor >= 0) || major > 2;
  OGL_VERSION_2_1   = (major == 2 && minor >= 1) || major > 2;
  OGL_VERSION_3_0   = (major == 3 && minor >= 0) || major > 3;
  OGL_VERSION_3_1   = (major == 3 && minor >= 1) || major > 3;
  OGL_VERSION_3_2   = (major == 3 && minor >= 2) || major > 3;
  OGL_VERSION_3_3   = (major == 3 && minor >= 3) || major > 3;
  OGL_VERSION_4_0   = (major == 4 && minor >= 0) || major > 4;
  OGL_VERSION_4_1   = (major == 4 && minor >= 1) || major > 4;
  OGL_VERSION_4_2   = (major == 4 && minor >= 2) || major > 4;
  OGL_VERSION_4_3   = (major == 4 && minor >= 3) || major > 4;
  OGL_VERSION_4_4   = (major == 4 && minor >= 4) || major > 4;
  OGL_VERSION_4_5   = (major == 4 && minor >= 5) || major > 4;
  OGL_VERSION_4_6   = (major == 4 && minor >= 6) || major > 4;
  
  if (major > 4 || (major >= 4 && minor >= 6)) {
    major = OGL_VERSION_MAJOR = 4;
    minor = OGL_VERSION_MINOR = 6;
  }
  return true;
}

GLuint glTypeToSize(GLenum type) {
  switch (type) {
    case GL_FLOAT : return sizeof(GLfloat);
    case GL_UINT  :
    case GL_INT   : return sizeof(GLint);
    case GL_USHORT:
    case GL_SHORT : return sizeof(GLshort);
    case GL_UBYTE :
    case GL_BYTE  : return sizeof(GLbyte);
  }
  // @todo: static_assert(false);
  return 0;
}

bool glVersion(int& major, int& minor) {
  load_base();
  // skip the line
  if (OGL_VERSION_MAJOR && OGL_VERSION_MINOR) {
    major = OGL_VERSION_MAJOR;
    minor = OGL_VERSION_MINOR;
    return true;
  }
  
  const char* version;
  const char* prefixes[] = {"OpenGL ES-CM ", "OpenGL ES-CL ", "OpenGL ES ", NULL};
  version = (const char*) ::glGetString(GL_VERSION);
  if (!version) return false;
  
  for (int i = 0; prefixes[i]; i++) {
    const size_t length = strlen(prefixes[i]);
    if (strncmp(version, prefixes[i], length) == 0) {
      version += length;
      break;
    }
  }

/* PR #18 */
#ifdef _MSC_VER
  sscanf_s(glVersion, "%d.%d", &major, &minor);
#else
  sscanf(version, "%d.%d", &major, &minor);
#endif
  
  return true;
}

bool glLoad(int major/*=-1*/, int minor/*=-1*/) {
  // load base
  load_base();
  // check glVersion
  (major == -1 || minor == -1) && glVersion(major,minor);
  // load version
  load_version(major,minor);
  // load functions
  load_v_1_0();
  load_v_1_1();
  load_v_1_2();
  load_v_1_3();
  load_v_1_4();
  load_v_1_5();
  load_v_2_0();
  load_v_2_1();
  load_v_3_0();
  load_v_3_1();
  load_v_3_2();
  load_v_3_3();
  load_v_4_0();
  load_v_4_1();
  load_v_4_2();
  load_v_4_3();
  load_v_4_4();
  load_v_4_5();
  load_v_4_6();
  // load extensions
  load_exts();
  // return status
  return true;
}

GLushort glClearError() { GLushort nFound = 0; while (::glGetError() != GL_NO_ERROR) { nFound++; } return nFound; }

bool glCheckError(const GLchar* func, const GLchar* file, GLushort line) {
  GLshort cnt = 0;
  while (GLenum err = ::glGetError()) {
    cnt++;
    std::string enm;
    switch (err) {
      case GL_INVALID_ENUM     : enm = "GL_INVALID_ENUM";      break; 
      case GL_INVALID_VALUE    : enm = "GL_INVALID_VALUE";     break; 
      case GL_INVALID_OPERATION: enm = "GL_INVALID_OPERATION"; break; 
      case GL_OUT_OF_MEMORY    : enm = "GL_OUT_OF_MEMORY";     break; 
    } 
    std::cerr << enm << " on " << func << " in " << file << ":" << line << std::endl; 
  }
  return cnt == 0;
}

