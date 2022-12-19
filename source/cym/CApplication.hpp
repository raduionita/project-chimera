#ifndef __cym_capplication_hpp__
#define __cym_capplication_hpp__

#include "cym/cym.hpp"
#include "cym/CContext.hpp"
#include "uix/CApplication.hpp"

namespace cym {
  class CApplication : public uix::CApplication {
    public:
      CApplication();
      ~CApplication();
    public:
      virtual bool init() override;
      virtual bool tick(float fElapsed=0.f) override;
  };
} // namespace cym

#endif //__cym_capplication_hpp__