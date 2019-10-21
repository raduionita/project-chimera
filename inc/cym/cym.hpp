#ifndef __cym_hpp__
#define __cym_hpp__

#include "sys/sys.hpp"

namespace cym {
  class CSystem;
    class CConsole;    // a system that outputs all posted messages, also sends messages (like commands)
    // cinematics      // a system that sends messages like rotate(object)+move(camera)
    // replay/recorder // a system that records messages to be played back
  class CMessage;
  class CMessenger;    // threading: should decide on which thread a CSystem should process a message
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // using CMemory = sys::CMemory;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  enum EPolymode {
    POINTS,
    WIREFRAME,
    SOLID,
  };
  
  enum ECulling {
    NONE,
    CLOCKWISE, CW = CLOCKWISE,
    COUNTERCLOCKWISE, CCW = COUNTERCLOCKWISE,
  };

}

#endif //__cym_hpp__
