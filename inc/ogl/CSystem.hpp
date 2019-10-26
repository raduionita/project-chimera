#ifndef __ogl_csystem_hpp__
#define __ogl_csystem_hpp__

#include "ogl/ogl.hpp"
#include "CMessenger.hpp"

namespace ogl {
  class CSystem {
    private:
      CMessenger* mMessenger {nullptr};
    public:
      CSystem();
    public:
      void handle(CMessage*);
  };
}

#endif //__ogl_csystem_hpp__
