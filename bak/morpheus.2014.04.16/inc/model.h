#ifndef __model_hpp_
#define __model_hpp_

#include "utils.h"

#include <iostream>
#include <memory>
#include <fstream>
#include <map>
#include <vector>
#include <string> 
#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace dae
{
  class model 
  {
    private: 
      typedef struct index_t {
        unsigned int v;
        unsigned int vt;
        unsigned int vn;
        index_t() { };
        index_t(unsigned int a) : v(a), vt(a), vn(a) { };
        index_t(unsigned int a, unsigned int b, unsigned int c) : v(a), vt(b), vn(c) { };
      } index_t;
      typedef struct color_t {
        float r;
        float g;
        float b;
        color_t(float val) : r(val), g(val), b(val) { }
      } color_t;
      typedef struct vertex2_t {
        float x;
        float y;
      } vertex2_t;
      typedef struct vertex3_t {
        float x;
        float y;
        float z;
      } vertex3_t;
      typedef struct mesh_t {
        std::vector<float>        positions;
        std::vector<float>        normals;
        std::vector<float>        texcoords;
        std::vector<unsigned int> indices;
      } mesh_t;
      typedef struct material_t {
        typedef struct colors_t {
          color_t ambient;         // rgb
          color_t diffuse;         // rgb
          color_t specular;        // rgb
          color_t transmission;    // rgb
          color_t emission;        // rgb
          colors_t(float a) : ambient(a), diffuse(a), specular(a), transmission(a), emission(a) { }
        } colors_t;
        typedef struct textures_t {   // textures
          std::string ambient;     
          std::string diffuse;
          std::string specular;
          std::string normal;
          textures_t() : ambient(""), diffuse(""), specular(""), normal("") { }
          textures_t(const char* a) : ambient(a), diffuse(a), specular(a), normal(a) { }
        } textures_t;
        typedef std::map<std::string, std::string> unknown_t;
        std::string name;  
        colors_t    colors;
        textures_t  textures;
        float       shininess;           // shininess
        float       ior;                 // index of refractions      
        unknown_t   unknown;     // unknown parameters
        material_t() : name(""), colors(0.0f), textures(""), shininess(1.0f), ior(1.0f), unknown() { }
      } material_t;
      typedef std::map<std::string, material_t> materials_t;
      typedef struct meta_t {
        std::string name;
      } meta_t;
      typedef struct shape_t {
        meta_t     meta;
        mesh_t     mesh;
        material_t meterial;
      } shape_t;
    public: 
      std::vector<shape_t> shapes;  
    public: 
      model() { }
      static std::shared_ptr<model> load(const char* filepath)
      {
        auto self = std::make_shared<model>();
        
        std::cout << "Starting..." << std::endl;
        
        std::fstream fs(filepath, std::ios::in | std::ios::binary);
        if(fs.is_open())
        {
          std::vector<vertex3_t>             v;   // positions
          std::vector<vertex2_t>            vt;   // texcoords
          std::vector<vertex3_t>            vn;   // normals
          std::vector<std::vector<index_t>>  f;   // faces
          
          materials_t                        m;   // materials
          std::shared_ptr<material_t> material;
          
          char* line = new char[1024];
          while(fs.peek() != -1)
          {
            fs.getline(line, 1024);
            
            line += strspn(line, " \t");                                             // ltrim whitespace | advance pointer
            if(line[0] =='\0' || line[0] =='#' || line[0] == '\n') continue;
            // assert(line);                                                          // line shouldn't be empty
            
            if(line[0] == 'v' && line[1] == ' ')
            {
              std::cout << line << std::endl;                                           // remove this
              line += 2;
              vertex3_t position;
              sscanf(line, "%f %f %f\n", &position.x, &position.y, &position.z);
              v.push_back(position);
              continue;
            }
            else if(line[0] == 'v' && line[1] == 't' && line[2] == ' ')                 // bool isSpace(const char);
            {
              std::cout << line << std::endl;                                           // remove this
              line += 3;
              vertex2_t texcoord;
              sscanf(line, "%f %f %f\n", &texcoord.x, &texcoord.y);
              vt.push_back(texcoord);
              continue;
            }
            else if(line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
            {
              std::cout << line << std::endl;                                           // remove this
              line += 3;
              vertex3_t normal;
              sscanf(line, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
              vn.push_back(normal);
              continue;
            }
            else if(line[0] == 'f' && line[1] == ' ')
            {
              std::cout << line << std::endl;                                           // remove this
              line += 2;
              line += strspn(line, " \t");
              std::vector<index_t> face;                                         // face
              
              auto vsize  = v.size();
              auto vtsize = vt.size();
              auto vnsize = vn.size();
              while(false == dae::utils::isNewLine(*line))
              {
                index_t i(-1);  
                // parse indicies
                
                i.v   = fixIndex(atoi(line), vsize);
                line += strcspn(line, "/ \t\r");
                if(*line == '/') 
                {                                                     
                  line++;                                                               // skip '/'
                  if(*line == '/')                                                      // i//k
                  {
                    line++;                                                             // skip '/'
                    i.vn  = fixIndex(atoi(line), vnsize);
                    line += strcspn(line, "/ \t\r");
                  }
                  else                                                                  // i/j
                  {
                    i.vt  = fixIndex(atoi(line), vtsize);
                    line += strcspn(line, "/ \t\r");
                    if(*line == '/')                                                    // i/j/k
                    {
                      line++;                                                           // skip '/'
                      i.vn = fixIndex(atoi(line), vnsize);
                      line += strcspn(line, "/ \t\r");
                    }
                  }
                }     
                face.push_back(i);
                line += strspn(line, " \t\r");                                          // got to the next group;
              }
              
              f.push_back(face);
              continue;
            }
            else if(strncmp(line, "mtllib", 6) && line[6] == ' ')                       // load mtl
            {
              std::cout << line << std::endl;                                           // remove this
              line += 7;
              
              char name[1024];                                                          // material name
              sscanf(line, "%s\n", name);
              
              bool bStatus = loadMtl(m, name);                                          // path to textures folder
              if(!bStatus)
                f.clear();              
              
              continue;
            }
            else if(strncmp(line, "usemtl", 6) && line[6] == ' ')                       // use mtl
            {
              std::cout << line << std::endl;                                           // remove this
              line += 7;
              
              char name[1024];                                                          // material name
              sscanf(line, "%s\n", name);
              
              if(m.find(name) != m.end()) 
                *material = m[name];
              else
                material = std::make_shared<material_t>();

              continue;
            }
            else if(line[0] == 'g' && line[1] == ' ')
            {
              std::cout << line << std::endl;                                           // remove this
              continue;
            }
            else if(line[0] == 'o' && line[1] == ' ')
            {
              std::cout << line << std::endl;                                           // remove this
              continue;
            }
          }
        }
        else
        {
          std::cerr << "Cannot open object file: " << filepath << std::endl;
        }
        
        return self;
      }
      friend bool operator<(const index_t&, const index_t&);
    private:
      static bool loadMtl(materials_t& m, const char* filepath)
      {
        bool bStatus = true;
        
        m.clear();
        
        std::ifstream fs(filepath, std::ios::in | std::ios::binary);
        if(fs.is_open())
        {
          std::shared_ptr<material_t> material;
          
          char* line = new char[2048];
          while(fs.peek() != -1)
          {
            fs.getline(line, 2048);
            
            line += strspn(line, " \t");
            if(line[0] =='\0' || line[0] =='#' || line[0] == '\n') continue;
            // asset(line);
            
            if(strncmp(line, "newmtl", 6) && line[6] == ' ')
            {
              line += 7;
              char name[1024];
              sscanf(line, "%s", name);
              material = std::make_shared<material_t>();
              material->name = name;
              continue;
            }
            else if(line[0] == 'K' && line[1] == 'a' && line[2] == ' ')
            {
              line += 2;
              sscanf(line, "%f %f %f\n", &material->colors.ambient.r, &material->colors.ambient.g, &material->colors.ambient.b);
              continue;
            }
            
            
          }
          
        }
        else
        {
          bStatus = false;
          std::cerr << "Cannot load material file: " << filepath << std::endl;
        }
        
        return bStatus;
      }
      static int  fixIndex(int idx, int n)
      {
        int i;
        if(idx > 0)                         // zero based
          i = idx - 1;
        else if(idx == 0)
          i = 0;
        else                                // nagative value = relative
          i = n + idx;
        return i;
      }
  };
  
  bool operator<(const model::index_t& lhs, const model::index_t& rhs)        // for map
  {
    if(lhs.v != rhs.v)        return lhs.v < rhs.v;
    else if(lhs.vn != rhs.vn) return lhs.vn < rhs.vn;
    else if(lhs.vt != rhs.vt) return lhs.vt < rhs.vt;
    return false;
  }
}

#endif // __model_hpp_
