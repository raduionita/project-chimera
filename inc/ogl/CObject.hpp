#ifndef __ogl_cobject_hpp__
#define __ogl_cobject_hpp__

#include "ogl.hpp"

namespace ogl {
  class CObject {
    protected:
      GLuint mID;
    public:
      CObject() = default;
      virtual ~CObject() = default;
    public:
      virtual void bind(bool = true) const = 0;
      inline virtual void link() const final { bind(true);  }
      inline virtual void free() const final { bind(false); }
  };
}

#endif //__ogl_cobject_hpp__
