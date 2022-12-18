#ifndef __cym_capplication_hpp__
#define __cym_capplication_hpp__

#include "cym/cym.hpp"
#include "cym/CContext.hpp"
#include "win/CApplication.hpp"

namespace cym {
  class CApplication : public win::CApplication {
    public:
      CApplication();
      ~CApplication();
    public:
      virtual bool init() override;
      virtual bool tick(float fElapsed=0.f) override;
  };
} // namespace cym

#endif //__cym_capplication_hpp__