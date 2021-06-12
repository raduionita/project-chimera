#ifndef __cym_carray_hpp__
#define __cym_carray_hpp__

#include "cym/cym.hpp"
#include "cym/CObject.hpp"

namespace cym {
  class CVertexArray : public CObject {
    public:
      CVertexArray();
      virtual ~CVertexArray();
    public:
      void bind(bool = true) const override;
      void load(CDataBuffer&, CVertexLayout&);
  };
}

#endif //__cym_carray_hpp__
