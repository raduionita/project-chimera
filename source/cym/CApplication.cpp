#include "cym/CApplication.hpp"

namespace cym {
  // ctor
  CApplication::CApplication() {
    LOGDBG("cym::CApplication::CApplication()");
  }
  // dtor
  CApplication::~CApplication() {
    LOGDBG("cym::CApplication::~CApplication()");
  }

  bool CApplication::init() {
    LOGDBG("cym::CApplication::init()");
    return cym::CControllerManager::bootup() &&
           uix::CApplication::init() && 
           cym::CScreenManager::bootup();
  }

  bool CApplication::tick(float fDelta/*=0.f*/) {
    return 
           uix::CApplication::tick(fDelta)
        && cym::CControllerManager::update(fDelta)
    // INPUTS
      // CREATE input map
      // HANDLE inputs
        // FOREACH input 
          // send message to controller
            // on "jump" send CJumpMessage
    
    // UDPATE

// && cym::CControllerManager::update(fDelta)

      // FOREACH controller
        // UPDATE controller
          // FOREACH process
            // apply modifier

// && cym::CIntersectResolver::update(fDelta)

      // FOREACH collision                                            +---------------+
        // send collision message                                     |        (force)|
          // to model:                                          +-----------+         |
            // apply force modifier (collision)                 |    (model)|         |
          // to force:                                          |           |---------+
            // apply force modifier (force field)               +-----------+
    
    // RENDER

// && cym::CScreenManager::update(fDelta)

      // FOREACH screen
        // FOREACH layer
          // RENDER layer
    ;
  }
} // namespace cym