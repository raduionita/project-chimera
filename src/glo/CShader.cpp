#include "glo/CShader.hpp"

#include <fstream>
#include <cassert>
#include <vector>

namespace glo {
  CShader::CShader(const std::string& filepath) : mFilepath{filepath} {
    // open file
    std::ifstream ifs(filepath);
    // @todo: replace w/ exception
    assert(ifs.good() && "cannot open shader file");
    
    std::string                                    line;
    std::unordered_map<GLenum, SSource>            sources;
    static std::unordered_map<GLenum, std::string> types {{GL_VERTEX_SHADER,"GL_VERTEX_SHADER"}};
    GLenum curr = GL_NONE;
    
    while (std::getline(ifs, line)) {
      if (line.find("#shader") != std::string::npos) {
        for (auto& [type, name] : types) {
          if (line.find(name) != std::string::npos) {
            curr = type;
            sources[type] = {name, type, GL_ZERO, ""};
            break;
          }
        }
      } else if (line.find("#include") != std::string::npos) {
        // @todo: include shader fragment
      } else {
        sources[curr].code.append(line);
      }
    }
    
    GLCALL(::gxCreateProgram(&mID));
    
    for (auto& [type, source] : sources) {
      GLuint& shader = source.shader;
      const char* data = source.code.c_str();
      GLCALL(::gxCreateShader(type, &shader));
      GLCALL(::glShaderSource(shader, 1, &data, NULL));
      GLCALL(::glCompileShader(shader));
      
      GLint status = GL_FALSE;
      GLCALL(::glGetShaderiv(shader, GL_COMPILE_STATUS, &status));
      if(status == GL_FALSE) {
        GLint loglen = 0;
        GLCALL(::glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglen));
        char* error = new char[loglen + 1];
        GLCALL(::glGetShaderInfoLog(shader, loglen, NULL, error));
        error[loglen] = '\0';
        assert(false && "shader compile failed");
      }
    }
    
    GLCALL(::glLinkProgram(mID));
    
    GLint status = GL_FALSE;
    GLCALL(::glGetProgramiv(mID, GL_LINK_STATUS, &status));
    if(status == GL_FALSE) {
      GLint loglen;
      GLCALL(::glGetProgramiv(mID, GL_INFO_LOG_LENGTH, &loglen));
      GLchar* error = new GLchar[loglen + 1];
      GLCALL(::glGetProgramInfoLog(mID, loglen, NULL, error));
      error[loglen] = '\0';
      assert(false && "program compile failed");
    }
    
    for (auto& [type, source] : sources) {
      GLCALL(::glDetachShader(mID, source.shader));
    }
    
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
