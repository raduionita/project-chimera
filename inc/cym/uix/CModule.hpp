#ifndef __cym_uix_cmodule_hpp__
#define __cym_uix_cmodule_hpp__

#include "CObject.hpp"

namespace cym { namespace uix {
  class CModule : public CObject {
    protected:
      using CObject::CObject;
      using CObject::operator=;
    protected:
      HINSTANCE            mHandle {NULL};
    public: // ctor
      CModule(HINSTANCE = ::GetModuleHandle(NULL));
      ~CModule();
    public: // cast
      explicit operator       HINSTANCE();
      explicit operator const HINSTANCE() const;
    protected:
      virtual bool init();
      virtual bool free();
  };
}}



#endif //CPP_CHIMERA_CMODULE_HPP
