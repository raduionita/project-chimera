#ifndef __ogl_cmessenger_hpp__
#define __ogl_cmessenger_hpp__

#include "ogl/ogl.hpp"

namespace ogl {
  class CMessenger {
    protected:
      // @todo: std::queue<CMessage*> mQueue; // message queue/map
    public:
      void trigger(CMessage*, int priority = 10); // post message w/ priority | 0 = now | 10+ = lazy as fuck
  };
}

#endif //__ogl_cmessenger_hpp__
