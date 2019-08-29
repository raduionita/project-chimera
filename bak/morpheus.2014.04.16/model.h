#ifndef __model_h_
#define __model_h_

#include <fstream>
#include <cstring>

namespace dae
{
  class model
  {
    public:
      model() { }
      
      static model* loadObj(GLuint& vbo, const GLchar* data)
      {
        model* m = new model();
        
        const GLchar* beg = &data[0];                             // save beginning
        
        while(true)
        {
          data++;
          if(*data == '\0') break;
          
          if(*data == 'v')
          {
            data++;
            if(*data == ' ')      m->stats.vertices++;
            else if(*data == 't') m->stats.uvs++;
            else if(*data == 'n') m->stats.normals++;
          }
          else if(*data == 'f')
          {
            data++;
            if(*data == ' ') m->stats.faces++;
          }
          
          while(*data != '\n')
            data++;
        }
        
        struct {
          model::vertex* vertices;
          model::uv*     uvs;
          model::normal* normals;
        } temp;
        
        temp.vertices = new model::vertex[m->stats.vertices];
        temp.uvs      = new model::uv[m->stats.uvs];
        temp.normals  = new model::normal[m->stats.normals];        
        
        m->indices.vertices = new GLuint[3 * m->stats.faces];
        m->indices.uvs      = new GLuint[3 * m->stats.faces];
        m->indices.normals  = new GLuint[3 * m->stats.faces];
        
        data = beg;                                               // reset to beginning
        while(true)
        {
          data++;
          if(*data == '\0') break;
          
          if(*data == 'v')
          {
            data++;
            if(*data == ' ')
            {
              sscanf(data, "%f %f %f\n", &(*temp.vertices).x, &(*temp.vertices).y, &(*temp.vertices).z); 
              ++temp.vertices;
            }
            else if(*data == 't')
            {
              sscanf(data, "%f %f\n", &(*temp.uvs).x, &(*temp.uvs).y); 
              // &(*temp.uvs).y *= -1; // invert for dds
              ++temp.uvs;
            }
            else if(*data == 'n')
            {
              sscanf(data, "%f %f %f\n", &(*temp.normals).x, &(*temp.normals).y, &(*temp.normals).z); 
              ++temp.normals;
            }
          }
          else if(*data == 'f')
          {
            data++;
            if(*data == ' ')
            {              
              int matches = sscanf(data, "%d/%d/%d %d/%d/%d %d/%d/%d\n", m->indices.vertices, m->indices.vertices++, m->indices.vertices++, m->indices.uvs+0, m->indices.uvs+1, m->indices.uvs+2, m->indices.normals+0, m->indices.normals+1, m->indices.normals+2);
              m->indices.vertices ++;
              //m->indices.uvs      += 3;
              //m->indices.normals  += 3;
              if(matches != 9)
              {
                std::cerr << "File format error. Wrong number("<< matches <<") of face indices." << std::endl;
                break;
              }
            }
          }
        }
        
        for(GLuint i = 0; i < 3 * m->stats.faces; i+=3)
        {
          std::cout << m->indices.vertices[i] << "/" << m->indices.vertices[i+1] << "/" << m->indices.vertices[i+2] << std::endl;
          std::cout << m->indices.uvs[i]      << "/" << m->indices.vertices[i+1] << "/" << m->indices.vertices[i+2] << std::endl;
          std::cout << m->indices.normals[i]  << "/" << m->indices.normals[i+1]  << "/" << m->indices.normals[i+2] << std::endl;
          
          // m->data.vertices[i] = temp.vertices[m->indices.vertices[i] - 1];
          // m->data.uvs[i]      = temp.uvs[m->indices.uvs[i] - 1];
          // m->data.normals[i]  = temp.normals[m->indices.normals[i] - 1];
        }
        
        delete data;
        
        return m;
      }
    public:
      typedef struct { GLfloat x; GLfloat y; GLfloat z; } vertex;
      typedef struct { GLfloat x; GLfloat y; }            uv;
      typedef struct { GLfloat x; GLfloat y; GLfloat z; } normal;
      struct {
        model::vertex* vertices;
        model::uv*     uvs;
        model::normal* normals;
      } data;
      struct {
        GLuint* vertices;
        GLuint* uvs;
        GLuint* normals;
      } indices;
      struct {
        GLuint vertices  = 0;
        GLuint uvs       = 0;
        GLuint normals   = 0;
        GLuint faces     = 0;
      } stats;
      // textures
      // vertices
  };
}

#endif // __model_h_
