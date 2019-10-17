#ifndef __glo_carray_hpp__
#define __glo_carray_hpp__

#include "glo.hpp"

namespace glo {
  class CArray {
    private:
      GLuint mID;
    public:
      CArray();
      virtual ~CArray();
    public:
      void bind(bool = true) const;
      void buffer(const CBuffer&, const CLayout&);
  };
}

#endif //__glo_carray_hpp__
