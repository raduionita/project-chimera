#include "ogl/CShader.hpp"
#include "ogl/CTexture.hpp"

#include "glm/CMatrix.hpp"

#include <fstream>
#include <cassert>
#include <vector>

namespace ogl {
  CShader::CShader(const std::string& filepath) : mFilepath{filepath} {
    log::nfo << "ogl::CShader::CShader(std::string&)::" << this << " FILE:" << filepath << log::end;
    // open file
    std::ifstream ifs(filepath);
    
    // @todo: replace w/ exception
    assert(ifs.good() && "cannot open shader file");
    
    std::string                                    line;
    std::unordered_map<GLenum, SSource>            sources;
    static std::unordered_map<GLenum, EType>       etypes {{GL_VERTEX_SHADER,EType::VERTEX},{GL_FRAGMENT_SHADER,EType::FRAGMENT},{GL_GEOMETRY_SHADER,EType::GEOMETRY},{GL_TESS_CONTROL_SHADER,EType::TESSCTRL},{GL_TESS_EVALUATION_SHADER,EType::TESSEVAL},{GL_COMPUTE_SHADER,EType::COMPUTE},};
    static std::unordered_map<GLenum, std::string> stypes {{GL_VERTEX_SHADER,"GL_VERTEX_SHADER"},{GL_FRAGMENT_SHADER,"GL_FRAGMENT_SHADER"},{GL_GEOMETRY_SHADER,"GL_GEOMETRY_SHADER"},{GL_TESS_CONTROL_SHADER,"GL_TESS_CONTROL_SHADER"},{GL_TESS_EVALUATION_SHADER,"GL_TESS_EVALUATION_SHADER"},{GL_COMPUTE_SHADER,"GL_COMPUTE_SHADER"}};
    GLenum                                         curr  {GL_NONE};
    
    while (std::getline(ifs, line)) {
      // custom tags
      if (line[0] == '@') {
        if (line.find("@shader") == 0) {
          for (auto& [type, name] : stypes) {
            auto s = sizeof("@shader");
            auto p = line.find(name);
            if (line.find(name) != std::string::npos) {
              curr = type;
              sources[type].name   = name;
              sources[type].type   = type;
              sources[type].shader = GL_ZERO;
              // found, no need to search for the other types
              break;
            } else {
              // @todo: insert warning here
            }
          }
        } else { // if (line.find("@include") == 0) {
          log::dbg << "[HLSL] " << line << log::end;
          // @todo: include shader fragment
        } 
      // regular glsl code
      } else {
        sources[curr].code += line + '\n';
      }
    }
    
    GLCALL(::gxCreateProgram(&mID));
    
    for (auto& [type, source] : sources) {
      GLuint&     shader = source.shader;
      const char* code   = source.code.c_str();
      GLCALL(::gxCreateShader(type, &shader));
      GLCALL(::glShaderSource(shader, 1, &code, NULL));
      GLCALL(::glCompileShader(shader));
      
      GLint status = GL_FALSE;
      GLCALL(::glGetShaderiv(shader, GL_COMPILE_STATUS, &status));
      if(status == GL_FALSE) {
        GLint loglen = 0;
        GLCALL(::glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglen));
        char* error = new char[loglen + 1];
        GLCALL(::glGetShaderInfoLog(shader, loglen, &loglen, error));
        error[loglen] = '\0';
        // cleanup
        GLCALL(::glDeleteProgram(mID));
        GLCALL(::glDeleteShader(shader));
        // @todo: replace w/ throw exception
        // @todo: this error reporting doesn't work well
        log::err << "ogl::CShader::CShader(std::string&)::" << this << " ERROR:" << error << log::end;
        assert(false);
      }
      
      mType |= etypes[source.type];
      
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
      GLCALL(::glGetProgramInfoLog(mID, loglen, &loglen, error));
      error[loglen] = '\0';
      // cleanup
      GLCALL(::glDeleteProgram(mID));
      // @todo: replace w/ throw exception
      log::err << "ogl::CShader::CShader(std::string&)::" << this << " ERROR:" << error << log::end;
      assert(false);
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
  
  // @todo: need better shader loading mechanisms
  
  CShader::~CShader() {
    GLCALL(::glDeleteProgram(mID));
  }
  
  void CShader::bind(bool state) const { 
    log::dbg << "ogl::CShader::bind(bool)::" << this << log::end;
    GLCALL(::glUseProgram(state ? mID : 0)); 
  }
  
  GLint CShader::uniform(const CString& name) {
    auto it = mUniforms.find(name);
    if (it != mUniforms.end()) {
      return it->second;
    }
    return GL_NOT_FOUND;
  }
  
  void CShader::uniform(const CString& name, float x) {
    GLint loc = uniform(name);
    if (loc != GL_NOT_FOUND) {
      GLCALL(::glUniform1f(loc, x));
    }
    // @todo: there should be a warn here if not found
  }
  
  void CShader::uniform(const CString& name, float x, float y, float z, float w) {
    GLint loc = uniform(name);
    if (loc != GL_NOT_FOUND) {
      GLCALL(::glUniform4f(loc, x,y,z,w));
    }
    // @todo: there should be a warn here if not found
  }
  
  void CShader::uniform(const ogl::CString& name, const PTexture& tex) {
    GLint loc = uniform(name);
    if (loc != GL_NOT_FOUND) {
      tex->bind();
      GLCALL(::glUniform1i(loc, tex->slot()));
    } else {
      log::wrn << "ogl::CShader::uniform(CString&,PTexture&)::" << this << " Uniform NOT found!" << log::end;
    }
    // @todo: there should be a warn here if not found
  }
  
  void CShader::uniform(const ogl::CString& name, const glm::mat4& M) {
    GLint loc = uniform(name);
    if (loc != GL_NOT_FOUND) {
      GLCALL(::glUniformMatrix4fv(loc, 1, false, (const float*)(M)));
    }
  }
  
  void CShader::sampler(const CString& name, GLuint i) {
    GLint loc = uniform(name);
    if (loc != GL_NOT_FOUND) {
      GLCALL(::glUniform1i(loc, i));
    }
    // @todo: there should be a warn here if not found
  }
  
  void CShader::sampler(const CString& name, const PTexture& tex) {
    GLint loc = uniform(name);
    if (loc != GL_NOT_FOUND) {
      tex->bind();
      GLCALL(::glUniform1i(loc, tex->slot()));
    } else {
      log::wrn << "ogl::CShader::sampler(CString&,PTexture&)::" << this << " Uniform NOT found!" << log::end;
    }
    // @todo: there should be a warn here if not found
  } 
}
