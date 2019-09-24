#ifndef __cym_uix_cpen_hpp__
#define __cym_uix_cpen_hpp__

#include "CObject.hpp"

namespace cym { namespace uix {
  class CPen : public CObject {
    protected:
      HPEN mHandle {HPEN(NULL_PEN)};
    public: // ctor
      CPen();
    public: // cast
      explicit operator       HPEN();
      explicit operator const HPEN() const;
  };
}}

#endif //__cym_uix_cpen_hpp__
