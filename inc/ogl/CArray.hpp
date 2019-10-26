#ifndef __glo_carray_hpp__
#define __glo_carray_hpp__

#include "glo.hpp"
#include "CObject.hpp"

namespace glo {
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

#endif //__glo_carray_hpp__
