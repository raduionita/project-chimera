#include "glo/CShader.hpp"

#include <fstream>
#include <cassert>

namespace glo {
  CShader::CShader(const std::string& filepath) : mFilepath{filepath} {
    // open file
    std::ifstream ifs(filepath);
    // @todo: replace w/ exception
    assert(ifs.good() && "cannot open shader file");
    
    // @todo: WHILE get line
      // @todo: FOR enum : [GL_VERTEX_SHADER, GL_FRAGMENT_SHADER]
        // @todo: IF does this line HAS "#define {enum}"
          // @todo: start new "enum" type shader
        // @todo: ELSE
          // @todo: add to current shader
      
    
    
    // @todo: for each ["GL_VERTEX_SHADER"]
      // @todo: split
      // @todo: create shader
      // @todo: attach
    // @todo: compile
    
    // find all uniforms
    int cnt = -1;
    GLCALL(::glGetProgramiv(mID, GL_ACTIVE_UNIFORMS, &cnt));
    for (int i = 0; i < cnt; i++) {
      GLint  len = -1, num = -1;
      GLenum typ = GL_ZERO;
      GLchar str[100];
      GLCALL(::glGetActiveUniform(mID, (GLuint)(i), sizeof(str)-1, &len, &num, &typ, str));
      str[len] = 0; // add null terminator '\0'
      GLuint loc = -1;
      GLCALL(::gxGetUniformLocation(mID, str, &loc));
      // add to cached uniforms
      mUniforms.insert(std::move(std::pair(std::string{str}, loc)));
    }
  }
  
  CShader::~CShader() {
    GLCALL(::glDeleteProgram(mID));
  }
  
  void CShader::uniform(const std::string& name, float x, float y, float z, float w) {
    
  }
  
  GLint CShader::uniform(const std::string& name) {
    return mUniforms[name];
  }
}
