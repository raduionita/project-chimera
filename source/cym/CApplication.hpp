#ifndef __cym_capplication_hpp__
#define __cym_capplication_hpp__

#include "cym/cym.hpp"
#include "win/CApplication.hpp"

namespace cym {
  class CApplication : public win::CApplication {
    public:
      CApplication();
    public:
      using win::CApplication::onInit;
      using win::CApplication::onFree;
      using win::CApplication::onTick;
  };
} // namespace cym

#endif //__cym_capplication_hpp__