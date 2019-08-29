#ifndef __fileio_h_
#define __fileio_h_

#include <fstream>

namespace dae
{
  namespace file
  {
    GLchar* read(const GLchar* filepath)
    {
      GLchar* data = nullptr;
      
      std::ifstream fs;
      fs.clear();
      fs.open(filepath, std::ios::in | std::ios::binary);
      
      if(fs.good())
      {       
        fs.seekg(0, std::ios::end);
        std::streamsize length = fs.tellg();
        fs.seekg(0, std::ios::beg);
        data = new GLchar[length + 1];
        fs.read(data, length);
        data[length] = '\0';
        fs.close();
      }
      else
      {
        std::cerr << "Can not read from file: " << filepath << std::endl;
      }
      
      delete filepath;
      return data;
    }
  }
}

#endif // __fileio_h_
