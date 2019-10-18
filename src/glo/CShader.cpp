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
    static std::unordered_map<GLenum, std::string> types {{GL_VERTEX_SHADER,"GL_VERTEX_SHADER"},{GL_FRAGMENT_SHADER,"GL_FRAGMENT_SHADER"},{GL_GEOMETRY_SHADER,"GL_GEOMETRY_SHADER"},{GL_TESS_CONTROL_SHADER,"GL_TESS_CONTROL_SHADER"},{GL_TESS_EVALUATION_SHADER,"GL_TESS_EVALUATION_SHADER"}};
    GLenum curr = GL_NONE;
    
    while (std::getline(ifs, line)) {
      if (line.find("#shader") == 0) {
        for (auto& [type, name] : types) {
          if (line.find(name) > sizeof("#shader")) {
            curr = type;
            sources[type] = {name, type, GL_ZERO, ""};
            // found, no need to search for the other types
            break;
          } else {
            // @todo: insert warning here
          }
        }
      } else if (line.find("#include") == 0) {
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
        // cleanup
        GLCALL(::glDeleteProgram(mID));
        GLCALL(::glDeleteShader(shader));
        // @todo: replace w/ throw exception
        assert(false && error);
      }
      
      GLCALL(::glAttachShader(mID, shader));
    }
    
    GLCALL(::glLinkProgram(mID));
    GLCALL(::glValidateProgram(mID));
    
    for (auto& [type, source] : sources) {
      GLCALL(::glDetachShader(mID, source.shader));
      GLCALL(::glDeleteShader(source.shader));
    }
    
    GLint status = GL_FALSE;
    GLCALL(::glGetProgramiv(mID, GL_LINK_STATUS, &status));
    if(status == GL_FALSE) {
      GLint loglen;
      GLCALL(::glGetProgramiv(mID, GL_INFO_LOG_LENGTH, &loglen));
      GLchar* error = new GLchar[loglen + 1];
      GLCALL(::glGetProgramInfoLog(mID, loglen, NULL, error));
      error[loglen] = '\0';
      // cleanup
      GLCALL(::glDeleteProgram(mID));
      // @todo: replace w/ throw exception
      assert(false && error);
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
      GLint loc = GL_NOT_FOUND;
      GLCALL(::gxGetUniformLocation(mID, str, &loc));
      // add to cached uniforms
      mUniforms.insert(std::move(std::pair(std::string{str}, loc)));
    }
  }
  
  CShader::~CShader() {
    GLCALL(::glDeleteProgram(mID));
  }
  
  void CShader::uniform(const std::string& name, float x, float y, float z, float w) {
    GLint loc = uniform(name);
    if (loc != GL_NOT_FOUND) {
      GLCALL(::glUniform4f(loc, x,y,z,w));
    }
    // @todo: there should be a warn here if not found
  }
  
  void CShader::uniform(const std::string& name, float x) {
    GLint loc = uniform(name);
    if (loc != GL_NOT_FOUND) {
      GLCALL(::glUniform1f(loc, x));
    }
    // @todo: there should be a warn here if not found
}  
  
  GLint CShader::uniform(const std::string& name) {
    auto it = mUniforms.find(name);
    if (it != mUniforms.end()) {
      return it->second;
    }
    return GL_NOT_FOUND;
  }
}
