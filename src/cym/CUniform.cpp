#include "cym/CUniform.hpp"
#include "cym/CShader.hpp"

namespace cym {
  CUniform::CUniform() { }
  
  CUniform::~CUniform() { }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CUniform& CUniform::operator = (const GLvoid* pValue) {
    log::nfo << "cym::CUniform::operator =(GLvoid*)" << log::end;
    switch(mType) {
      case GL_BOOL:       GLCALL(::glProgramUniform1i(mShader->mID, mLocation, *((GLint*)pValue)));              break;
      case GL_BOOL_VEC2:  GLCALL(::glProgramUniform2iv(mShader->mID, mLocation, mComponents, ((GLint*)pValue))); break;
      case GL_BOOL_VEC3:
      case GL_BOOL_VEC4:  
      
      case GL_INT:        GLCALL(::glProgramUniform1i(mShader->mID, mLocation, *((GLint*)pValue)));            break;
      case GL_INT_VEC2:   GLCALL(::glProgramUniform2iv(mShader->mID, mLocation, mComponents, (GLint*)pValue)); break;
      case GL_INT_VEC3:
      case GL_INT_VEC4:
      
      case GL_UNSIGNED_INT:      GLCALL(::glProgramUniform1ui(mShader->mID, mLocation, *((GLuint*)pValue)));              break;
      case GL_UNSIGNED_INT_VEC2: GLCALL(::glProgramUniform2uiv(mShader->mID, mLocation, mComponents, ((GLuint*)pValue))); break;
      case GL_UNSIGNED_INT_VEC3:
      case GL_UNSIGNED_INT_VEC4:
      
      case GL_FLOAT:             GLCALL(::glProgramUniform1f(mShader->mID, mLocation, *((GLfloat*)pValue)));              break;
      case GL_FLOAT_VEC2:        GLCALL(::glProgramUniform2fv(mShader->mID, mLocation, mComponents, ((GLfloat*)pValue))); break;
      case GL_FLOAT_VEC3:
      case GL_FLOAT_VEC4:
      case GL_FLOAT_MAT2:        GLCALL(::glProgramUniformMatrix2fv(mShader->mID, mLocation, mComponents, mTransposed, ((GLfloat*)pValue)));   break;
      case GL_FLOAT_MAT2x3:      GLCALL(::glProgramUniformMatrix2x3fv(mShader->mID, mLocation, mComponents, mTransposed, ((GLfloat*)pValue))); break;
      case GL_FLOAT_MAT2x4:
      case GL_FLOAT_MAT3:
      case GL_FLOAT_MAT3x2:
      case GL_FLOAT_MAT3x4:
      case GL_FLOAT_MAT4x2:
      case GL_FLOAT_MAT4x3:  
      
      case GL_DOUBLE:            GLCALL(::glProgramUniformMatrix2dv(mShader->mID, mLocation, mComponents, mTransposed, ((GLdouble*)pValue))); break;
      case GL_DOUBLE_VEC2:
      case GL_DOUBLE_VEC3:
      case GL_DOUBLE_VEC4:
      case GL_DOUBLE_MAT2:
      case GL_DOUBLE_MAT2x3:
      case GL_DOUBLE_MAT2x4:
      case GL_DOUBLE_MAT3:
      case GL_DOUBLE_MAT3x2:
      case GL_DOUBLE_MAT3x4:
      case GL_DOUBLE_MAT4x2:
      case GL_DOUBLE_MAT4x3:
      
      case GL_SAMPLER_1D:                     GLCALL(::glProgramUniform1i(mShader->mID, mLocation, *((GLint*)pValue))); break;
      case GL_SAMPLER_1D_SHADOW:
      case GL_SAMPLER_1D_ARRAY:
      case GL_SAMPLER_1D_ARRAY_SHADOW:
      case GL_SAMPLER_2D:                     GLCALL(::glProgramUniform1i(mShader->mID, mLocation, *((GLint*)pValue))); break;
      case GL_SAMPLER_2D_SHADOW:
      case GL_SAMPLER_2D_ARRAY:
      case GL_SAMPLER_2D_ARRAY_SHADOW:
      case GL_SAMPLER_2D_MULTISAMPLE:
      case GL_SAMPLER_2D_MULTISAMPLE_ARRAY:
      case GL_SAMPLER_2D_RECT:
      case GL_SAMPLER_2D_RECT_SHADOW:
      case GL_SAMPLER_3D:
      case GL_SAMPLER_CUBE:
      case GL_SAMPLER_CUBE_SHADOW:
      case GL_SAMPLER_CUBE_MAP_ARRAY:
      case GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW:
      case GL_SAMPLER_BUFFER:
      
      case GL_INT_SAMPLER_1D:
      case GL_INT_SAMPLER_1D_ARRAY:
      case GL_INT_SAMPLER_2D:
      case GL_INT_SAMPLER_2D_ARRAY:
      case GL_INT_SAMPLER_2D_MULTISAMPLE:
      case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
      case GL_INT_SAMPLER_2D_RECT:
      case GL_INT_SAMPLER_3D:
      case GL_INT_SAMPLER_CUBE:
      case GL_INT_SAMPLER_CUBE_MAP_ARRAY:
      case GL_INT_SAMPLER_BUFFER:
      
      case GL_UNSIGNED_INT_SAMPLER_1D:
      case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:
      case GL_UNSIGNED_INT_SAMPLER_2D:
      case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
      case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:
      case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
      case GL_UNSIGNED_INT_SAMPLER_2D_RECT:
      case GL_UNSIGNED_INT_SAMPLER_3D:
      case GL_UNSIGNED_INT_SAMPLER_CUBE:
      case GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY:
      case GL_UNSIGNED_INT_SAMPLER_BUFFER:
      
      case GL_IMAGE_1D:                      // FLOAT
      case GL_IMAGE_1D_ARRAY:
      case GL_IMAGE_2D:
      case GL_IMAGE_2D_ARRAY:
      case GL_IMAGE_2D_RECT:
      case GL_IMAGE_2D_MULTISAMPLE:
      case GL_IMAGE_2D_MULTISAMPLE_ARRAY:
      case GL_IMAGE_3D:
      case GL_IMAGE_CUBE:
      case GL_IMAGE_CUBE_MAP_ARRAY:  
      
      case GL_INT_IMAGE_1D:
      case GL_INT_IMAGE_1D_ARRAY:
      case GL_INT_IMAGE_2D:
      case GL_INT_IMAGE_2D_ARRAY:
      case GL_INT_IMAGE_2D_RECT:
      case GL_INT_IMAGE_2D_MULTISAMPLE:
      case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
      case GL_INT_IMAGE_3D:
      case GL_INT_IMAGE_CUBE:
      case GL_INT_IMAGE_CUBE_MAP_ARRAY:
      
      case GL_UNSIGNED_INT_IMAGE_1D:
      case GL_UNSIGNED_INT_IMAGE_1D_ARRAY:
      case GL_UNSIGNED_INT_IMAGE_2D:
      case GL_UNSIGNED_INT_IMAGE_2D_ARRAY:
      case GL_UNSIGNED_INT_IMAGE_2D_RECT:
      case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE:
      case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
      case GL_UNSIGNED_INT_IMAGE_3D:
      case GL_UNSIGNED_INT_IMAGE_CUBE:
      case GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY:
      
      default:
      case GL_NONE:
        log::wrn << "cym::CUniform::operator=(const GLvoid*) > Error: Uniform has no type!" << log::end;
      break;
    }
    
    return *this;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CUniform::name(const std::string& name) {
    mName = name;
  }
  
  std::string CUniform::name() const {
    return mName;
  }
  
  void CUniform::type(GLenum type) {
    mType = type;
  }
  
  GLenum CUniform::type() const {
    return mType;
  }
  
  void CUniform::shader(CShader* pShader) {
    mShader = pShader;
  }
  
  CShader* CUniform::shader() const {
    return mShader;
  }
  
  void CUniform::location(GLint loc) {
    mLocation = loc;
  }
  
  GLint CUniform::location() const {
    return mLocation;
  }
  
  void CUniform::transposed(GLboolean trans) {
    mTransposed = trans;
  }
  
  GLboolean CUniform::transposed() const {
    return mTransposed;
  }
  
  void CUniform::components(GLushort comps) {
    mComponents = comps;
  }
  
  GLushort CUniform::components() const {
    return mComponents;
  }
  
}
