#ifndef __gll_hpp__
#define __gll_hpp__

#include <string>

namespace gll {
  struct resource {
    static resource load(const std::string&);
  };
  struct texture : public resource {
    static texture load(const std::string&);
  };
  struct material : public resource {};
  struct model : public resource {};
  struct mesh : public resource {};
  struct shader : public resource {};
  
  class loader;
  
  template <typename T> void load(const T&, const std::string&);
  
  resource load(const std::string&);
  
    // @todo: use ::glTexStorage2D // allocate
  // +
  // @todo: use ::glTexSubImage2D // put
  
  class CDdsLoader {
    // glBindTexture(GL_TEXTURE_2D, tid);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipMapCount-1); // opengl likes array length of mipmaps
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // don't forget to enable mipmaping
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // for (unsigned int i=0; i<mipMapCount; i++) {
      // glCompressedTexImage2D(GL_TEXTURE_2D, i, format, w, h, 0, size, buffer + offset)
    //
    
    // discard old mipmaps
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipMapCount-1);
  };
}

#endif //__gll_hpp__
