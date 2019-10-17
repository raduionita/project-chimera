#ifndef __glo_cobject_hpp__
#define __glo_cobject_hpp__

#include "glo.hpp"

namespace glo {
  class CObject {
    protected:
      GLuint mID;
    public:
      CObject() = default;
      virtual ~CObject() = default;
    public:
      virtual void bind(bool = true) const = 0;
  };
}

#endif //__glo_cobject_hpp__
