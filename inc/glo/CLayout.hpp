#ifndef __glo_clayout_hpp__
#define __glo_clayout_hpp__

#include "glo.hpp"

#include <vector>

namespace glo {
  class CLayout { // @see [morpheus] CBufferRange
    public:
      struct SElement {
        GLenum  type  {GL_FLOAT};  // GL_FLOAT
        GLuint  count {0};
        GLubyte norm  {GL_FALSE};  // [0|1]
        inline  GLuint  size() const { return count * ::glTypeToSize(type); }
      };
    protected:
      GLuint                mStride {0};
      std::vector<SElement> mElements;
    public:
      CLayout();
    public:
      inline void push(SElement&& element)                                 { mElements.push_back(std::move(element));  mStride += element.count * ::glTypeToSize(element.type); }
      inline void push(GLenum type, GLuint count, GLubyte norm = GL_FALSE) { mElements.push_back({type, count, norm}); mStride += count         * ::glTypeToSize(type); }
      // stuff
      inline GLuint stride() const { return mStride; }
      inline const std::vector<SElement>& elements() const { return mElements; };
      
  };
}

#endif //__glo_clayout_hpp__
