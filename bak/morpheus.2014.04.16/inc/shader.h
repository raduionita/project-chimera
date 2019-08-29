#ifndef __shader_h_
#define __shader_h_

#include <map>

namespace dae
{
  namespace shader
  {
    GLuint createProgram(std::map<GLenum, const GLchar*> shaders)
    {
      GLuint count = 0;
      GLuint program = glCreateProgram();
      
      for(/*std::map<GLenum, const GLubyte*>::const_iterator*/ auto it = shaders.begin(); it != shaders.end(); ++it)
      {
        if(it->first == GL_NONE) continue;
        
        GLuint shader = glCreateShader(it->first);
        glShaderSource(shader, 1, &it->second, NULL);
        glCompileShader(shader);
        
        delete it->second;
        it->second = nullptr;
        
        GLint status = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if(status == GL_FALSE)
        { 
          GLint loglen;
          glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglen);
          GLchar* error = new GLchar[loglen + 1];
          glGetShaderInfoLog(shader, loglen, NULL, error);
          std::cerr << "Error creation shader: " << error << std::endl;
          delete error;
        }
        
        ++count;
        glAttachShader(program, shader);
        // glDeleteShader(shader);
      }
      
      glLinkProgram(program);
      
      GLint status = GL_FALSE;
      glGetProgramiv(program, GL_LINK_STATUS, &status);
      if(status == GL_FALSE)
      {
        GLint loglen;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &loglen);
        GLchar* error = new GLchar[loglen + 1];
        glGetProgramInfoLog(program, loglen, NULL, error);
        std::cerr << "Error creating program: " << error << std::endl;
      }
      
      return program;
    }
  }
}

#endif // __shader_h_
