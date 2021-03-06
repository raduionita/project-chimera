#ifndef __uix_cmodule_hpp__
#define __uix_cmodule_hpp__

#include "CObject.hpp"

namespace uix {
  class CModule : public CObject {
    protected:
      using CObject::CObject;
      using CObject::operator=;
    protected:
      bool      mInited {false};
      HINSTANCE mHandle {NULL};
    public: // ctor
      CModule(HINSTANCE = ::GetModuleHandle(NULL));
      CModule(const char*);
      ~CModule();
    public: // cast
      explicit operator       HINSTANCE();
      explicit operator const HINSTANCE() const;
    protected:
      virtual bool init();
      virtual bool free();
  };
}



#endif //CPP_CHIMERA_CMODULE_HPP
