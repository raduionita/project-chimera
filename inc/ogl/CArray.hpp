#ifndef __ogl_carray_hpp__
#define __ogl_carray_hpp__

#include "ogl.hpp"
#include "CObject.hpp"

namespace ogl {
  class CArray : public CObject { };
  
  class CVertexArray : public CArray {
    public:
      CVertexArray();
      virtual ~CVertexArray();
    public:
      void bind(bool = true) const override;
      void buffer(const CVertexBuffer&, const CVertexLayout&);
  };
}

#endif //__ogl_carray_hpp__
