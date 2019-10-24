#ifndef __glo_cshader_hpp__
#define __glo_cshader_hpp__

#include "glo.hpp"
#include "CObject.hpp"

#include <string>
#include <unordered_map>

namespace glo {
  class CShader : public CObject {
    protected:
      struct SSource {
        std::string       name;
        GLenum            type;
        GLuint            shader;
        std::string       code;
      };
    public:
      enum EType {
        NONE      = GL_NONE,
        VERTEX    = GL_VERTEX_SHADER,
        GEOMETRY  = GL_GEOMETRY_SHADER,
        TESSCTRL  = GL_TESS_CONTROL_SHADER,
        TESSEVAL  = GL_TESS_EVALUATION_SHADER,
        FRAGMENT  = GL_FRAGMENT_SHADER,
        COMPUTE   = GL_COMPUTE_SHADER,
      };
    protected:
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
  };
}

#endif //__glo_cshader_hpp__
