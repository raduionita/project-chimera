#ifndef __ogl_cshader_hpp__
#define __ogl_cshader_hpp__

#include "ogl/ogl.hpp"
#include "ogl/CObject.hpp"
#include "ogl/CResource.hpp"

#include <string>
#include <unordered_map>

namespace ogl {
  class CShader : public CResource, public CObject {
      friend class CUniform;
    protected:
      struct SSource {
        std::string       name;
        GLenum            type;
        GLuint            shader;
        std::string       code;
      };
    public:
      enum EType {
      //NONE      = 0b0000'0000,
        VERTEX    = 0b00000010,
        GEOMETRY  = 0b00000100,
        TESSCTRL  = 0b00001000,
        TESSEVAL  = 0b00010000,
        FRAGMENT  = 0b00100000,
        COMPUTE   = 0b01000000,
      };
    protected:
      GLint                                  mType {0};
      std::string                            mFilepath;
      std::unordered_map<std::string, GLint> mUniforms;
    public:
      CShader(const std::string&);
      ~CShader();
    public:
      void bind(bool state = true) const override;
      // uniforms
      void  uniform(const CString& name, float x, float y, float z, float w);
      void  uniform(const CString& name, float x);
      GLint uniform(const CString& name);
      void  sampler(const CString& name, GLuint);
      void  sampler(const CString& name, const PTexture&);
  };
  
  class CShaderLoader : public CResourceStream {
    public:
  };
      
  class CShaderManager : public CResourceManager, public sys::CSingleton<CShaderManager> {
    public:
      CShader* load(const std::string& file);
      CShader* find(GLuint id);
  };  
}

#endif //__ogl_cshader_hpp__
