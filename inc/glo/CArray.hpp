#ifndef __glo_carray_hpp__
#define __glo_carray_hpp__

#include "glo.hpp"
#include "CObject.hpp"

namespace glo {
  class CArray : public CObject {
    public:
      CArray();
      virtual ~CArray();
    public:
      void bind(bool = true) const override;
      void buffer(const CBuffer&, const CLayout&);
  };
}

#endif //__glo_carray_hpp__
