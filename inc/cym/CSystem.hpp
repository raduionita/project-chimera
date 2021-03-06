#ifndef __cym_csystem_hpp__
#define __cym_csystem_hpp__

#include "cym/cym.hpp"
#include "cym/CMessenger.hpp"

namespace cym {
  class CSystem {
    private:
      CMessenger* mMessenger {nullptr};
    public:
      CSystem();
    public:
      void handle(CMessage*);
  };
}

#endif //__cym_csystem_hpp__
