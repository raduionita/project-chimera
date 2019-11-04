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
        VERTEX    = 0b0000'0010,
        GEOMETRY  = 0b0000'0100,
        TESSCTRL  = 0b0000'1000,
        TESSEVAL  = 0b0001'0000,
        FRAGMENT  = 0b0010'0000,
        COMPUTE   = 0b0100'0000,
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
      void  uniform(const std::string& name, float x, float y, float z, float w);
      void  uniform(const std::string& name, float x);
      GLint uniform(const std::string& name);
      void  sampler(const std::string& name, GLuint);
      void  sampler(const std::string& name, const CTexture&);
  };
  
  class CShaderLoader : public CResourceLoader {
    public:
  };
      
  class CShaderManager : public CResourceManager, public sys::CSingleton<CShaderManager> {
    public:
      CShader* load(const std::string& file);
      CShader* find(GLuint id);
  };  
}

#endif //__ogl_cshader_hpp__
