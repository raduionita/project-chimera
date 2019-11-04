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
      inline explicit operator GLuint()             { return mID; }
      inline explicit operator const GLuint() const { return mID; }
    public:
      inline         GLuint id() const { return mID; }
             virtual GLvoid bind(bool = true) const = 0;
      inline virtual GLvoid link() const final { bind(true);  }
      inline virtual GLvoid free() const final { bind(false); }
  };
}

#endif //__ogl_cobject_hpp__
