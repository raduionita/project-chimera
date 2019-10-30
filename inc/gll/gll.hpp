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
}

#endif //__gll_hpp__
